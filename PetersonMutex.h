#ifndef PETERSON_MUTEX_H
#define PETERSON_MUTEX_H

#include "MutexInterface.h"
#include <atomic>
#include <memory>

class PetersonMutex : public MutexInterface {
public:
    PetersonMutex();
    void lock(int thread_id) override;
    void unlock(int thread_id) override;

private:
    std::atomic<bool> flag[2];
    std::atomic<int> victim;
};

#endif // PETERSON_MUTEX_H
