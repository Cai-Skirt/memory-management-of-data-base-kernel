#include "head.h"

int acquireLWLock(lwlock* lockToAcquire){
    return pthread_mutex_lock(&lockToAcquire->lock);
};

int releaseLWlock(lwlock* lockToRelease){
    return pthread_mutex_unlock(&lockToRelease->lock);
};