#include "head.h"

int appendToList(listControl* list, blockListNodePointer toAppendBlock){
    if(list->head == NULL){
        list->head = toAppendBlock;
        list->tail = toAppendBlock;
        toAppendBlock->formerNode = NULL;
        toAppendBlock->nextNode = NULL;
    } else {
        list->tail->nextNode = toAppendBlock;
        toAppendBlock->formerNode = list->tail;
        toAppendBlock->nextNode = NULL;
        list->tail = toAppendBlock;
    }
    return SUCCESS;
}

blockListNodePointer popFromList(listControl* list){
    blockListNodePointer popTarget;
    if(list->head == NULL){
        popTarget = NULL;
    } else if (list->head == list->tail){
        popTarget = list->head;
        list->head = NULL;
        list->tail = NULL;
    } else {
        popTarget = list->head;
        list->head = list->head->nextNode;
        list->head->formerNode = NULL;
    }
    return popTarget;
}

int removeFromList(listControl* list, blockListNodePointer removeTarget){
    if(list->head == removeTarget || list->tail == removeTarget){
        list->head = NULL;
        list->tail = NULL;
    } else if (list->head == removeTarget){
        popFromList(list);
    } else if (list->tail == removeTarget){
        list->tail = list->tail->formerNode;
        list->tail->nextNode = NULL;
    } else {
        removeTarget->formerNode->nextNode = removeTarget->nextNode;
        removeTarget->nextNode->formerNode = removeTarget->formerNode;
    }
    return SUCCESS;
}
