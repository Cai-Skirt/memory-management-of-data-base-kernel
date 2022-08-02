#include "head.h"

void* tupleAccessSimulate(){
    tupleItem aTuple;
    char content[32] = "Barbara";
    memcpy(aTuple.content, content, tupleSize);
    for(int i = 0; i < 50; i++) {
        usleep(rand() % 9 * 1500);
        int blockID = rand() % 99;
        int tupleID = rand() % 99;
        if(insertATuple(blockID, tupleID, aTuple) == FAIL){
            printf("Insert failed.\n");
        }
        usleep(rand() % 9 * 1500);
        tupleItem* pointer = getATuple(blockID, tupleID);
        if(pointer == NULL){
            printf("Get failed.\n");
        } else {
            free(pointer);
        }
        usleep(rand() % 9 * 1500);
        if(updateATuple(blockID, tupleID, &aTuple) == FAIL){
            printf("updateFailed\n");
        }
        usleep(rand() % 9 * 1500);
        if(removeATuple(blockID, tupleID) == FAIL){
            printf("removeFailed\n");
        }
        printf("%d\n", i);
    }
    return (void*) SUCCESS;
}
