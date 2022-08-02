#include "head.h"

int initBufferManager(){
    SystemBufferMnager.bufferSize = 4;

    SystemBufferMnager.freeList.head = NULL;
    SystemBufferMnager.freeList.tail = NULL;
    pthread_mutex_init(&SystemBufferMnager.freeList.lock.lock, NULL);

    SystemBufferMnager.emptyList.head = NULL;
    SystemBufferMnager.emptyList.tail = NULL;
    pthread_mutex_init(&SystemBufferMnager.freeList.lock.lock, NULL);

    SystemBufferMnager.busyList.head = NULL;
    SystemBufferMnager.busyList.tail = NULL;
    pthread_mutex_init(&SystemBufferMnager.freeList.lock.lock, NULL);

    for(int i = 0; i < SystemBufferMnager.bufferSize; i++){
        blockListNode newNode;
        newNode.realBlockId = -1;
        appendToList(&SystemBufferMnager.emptyList, &newNode);
    }

    return SUCCESS;
}

blockListNodePointer fetchFromStorage(int appliedRealBlockId){
    acquireLWLock(&SystemBufferMnager.emptyList.lock);
    blockListNodePointer pointer = popFromList(&SystemBufferMnager.emptyList);
    releaseLWlock(&SystemBufferMnager.emptyList.lock);
    if(pointer == NULL){
        acquireLWLock(&SystemBufferMnager.freeList.lock);
        pointer = popFromList(&SystemBufferMnager.freeList);
        releaseLWlock(&SystemBufferMnager.freeList.lock);
        if(pointer == NULL){
            printf("NO AVAILABLE SPACE IN BUFFER\n");
            return NULL;
        }
    }

    pointer->realBlockId = appliedRealBlockId;

    acquireLWLock(&SystemBufferMnager.busyList.lock);
    appendToList(&SystemBufferMnager.busyList, pointer);
    releaseLWlock(&SystemBufferMnager.busyList.lock);
    return pointer;
}

blockListNodePointer applyBufferBlock(int appliedRealBlockId) {
    blockListNodePointer pointer;

    acquireLWLock(&SystemBufferMnager.freeList.lock);
    pointer = SystemBufferMnager.freeList.head;
    while(pointer != NULL){
        if(pointer->realBlockId == appliedRealBlockId){
            acquireLWLock(&SystemBufferMnager.busyList.lock);
            removeFromList(&SystemBufferMnager.freeList, pointer);
            appendToList(&SystemBufferMnager.busyList, pointer);
            releaseLWlock(&SystemBufferMnager.busyList.lock);
            releaseLWlock(&SystemBufferMnager.freeList.lock);
            return pointer;
        }
        pointer = pointer->nextNode;
    }
    releaseLWlock(&SystemBufferMnager.freeList.lock);

    acquireLWLock(&SystemBufferMnager.busyList.lock);
    pointer = SystemBufferMnager.busyList.head;
    while(pointer != NULL){
        if(pointer->realBlockId == appliedRealBlockId){
            releaseLWlock(&SystemBufferMnager.busyList.lock);
            return NULL;
        }
        pointer = pointer->nextNode;
    }
    releaseLWlock(&SystemBufferMnager.busyList.lock);
    return fetchFromStorage(appliedRealBlockId);
}

int returnBufferBlock(blockListNodePointer returnedBufferBlock) {
    acquireLWLock(&SystemBufferMnager.freeList.lock);
    acquireLWLock(&SystemBufferMnager.busyList.lock);
    appendToList(&SystemBufferMnager.freeList, returnedBufferBlock);
    removeFromList(&SystemBufferMnager.busyList, returnedBufferBlock);
    releaseLWlock(&SystemBufferMnager.busyList.lock);
    releaseLWlock(&SystemBufferMnager.freeList.lock);
    return SUCCESS;
}