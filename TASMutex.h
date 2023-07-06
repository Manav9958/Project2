#ifndef TAS_MUTEX_H
#define TAS_MUTEX_H

#include "MutexInterface.h"
#include <atomic>

class TASMutex : public MutexInterface {
public:
    TASMutex();
    void lock(int thread_id = 0) override;
    void unlock(int thread_id = 0) override;

private:
    std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;
};

#endif // TAS_MUTEX_H
