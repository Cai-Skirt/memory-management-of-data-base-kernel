#include "head.h"

tupleItem* getATuple(int blockId, int tupleID){
    tupleItem* tuple = NULL;
    blockListNodePointer pointer = applyBufferBlock(blockId);
    if(pointer == NULL){
        return tuple;
    } else {
        printf("got a tuple in block %d\n", blockId);
        tuple = (tupleItem*) malloc(sizeof(tupleItem));
        returnBufferBlock(pointer);
        return tuple;
    }
}

int removeATuple(int blockId, int tupleID){
    blockListNodePointer pointer = applyBufferBlock(blockId);
    if(pointer == NULL){
        return FAIL;
    } else {
        printf("removed a tuple in block %d\n", blockId);
        returnBufferBlock(pointer);
        return SUCCESS;
    }
}

int insertATuple(int blockId, int newTupleID, tupleItem newTuple){
    blockListNodePointer pointer = applyBufferBlock(blockId);
    if(pointer == NULL){
        return FAIL;
    } else {
        printf("inserted a tuple in block %d\n", blockId);
        returnBufferBlock(pointer);
        return SUCCESS;
    }
}

int updateATuple(int blockId, int tupleID, tupleItem* newTuple){
    blockListNodePointer pointer = applyBufferBlock(blockId);
    if(pointer == NULL){
        return FAIL;
    } else {
        printf("updated a tuple in block %d\n", blockId);
        returnBufferBlock(pointer);
        return SUCCESS;
    }
}
