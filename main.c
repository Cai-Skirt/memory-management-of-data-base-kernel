#include "head.h"

int main(){
    initBufferManager();

    srand(time(NULL));
    pthread_t pid[9];

    for(int i = 0; i < 9; i++){
        pthread_create(&pid[i], NULL, tupleAccessSimulate, NULL);
    }

    for(int i = 0; i < 9; i++){
        pthread_join(pid[i], NULL);
    }

    return SUCCESS;
}