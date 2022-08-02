#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define FAIL 78
#define SUCCESS 23
#define blockSize 137
#define tupleSize 16

#ifndef Buffer_Structrue
#define Buffer_Structrue

typedef struct tupleItem{
    char content[tupleSize];
} tupleItem;

typedef struct lwlock{
    pthread_mutex_t lock; /* 互斥锁定义 */
} lwlock;

typedef struct blockListNode{
    char memoryBlock[blockSize];
    int realBlockId;
    struct blockListNode* formerNode;
    struct blockListNode* nextNode;
} blockListNode;

typedef blockListNode* blockListNodePointer;

typedef struct listControl{
    lwlock lock;
    blockListNodePointer head;
    blockListNodePointer tail;
} listControl;

typedef struct bufferManager{
    listControl freeList;
    listControl busyList;
    listControl emptyList;
    int bufferSize;
}bufferManager;

#endif

bufferManager SystemBufferMnager;

int initBufferManager();

int acquireLWLock(lwlock* lockToAcquire);
int releaseLWlock(lwlock* lockToRelease);

blockListNodePointer popFromList(listControl* list);
int appendToList(listControl* list, blockListNode* toAppendBlock);
int removeFromList(listControl* list, blockListNode* removeTarget);

blockListNodePointer applyBufferBlock(int appliedRealBlockId);
int returnBufferBlock(blockListNode* returnedBufferBlock);

tupleItem* getATuple(int blockId, int tupleID);
int removeATuple(int blockId, int tupleID);
int insertATuple(int blockId, int newTupleID, tupleItem newTuple);
int updateATuple(int blockId, int tupleID, tupleItem* newTuple);

void* tupleAccessSimulate();
