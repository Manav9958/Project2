// FAIMutex.h
#ifndef FAI_MUTEX_H
#define FAI_MUTEX_H

#include <atomic>
#include <vector>
#include <memory>
#include "MutexInterface.h"

class FAIMutex : public MutexInterface {
public:
    FAIMutex(int num_threads);

    void lock(int thread_id) override;
    void unlock(int thread_id) override;

private:
    std::atomic<int> counter;    // The ticket counter
    std::atomic<int> next_ticket;  // The next ticket to be served
    std::vector<std::shared_ptr<std::atomic<int>>> turn;  // The turn of each thread
};

#endif // FAI_MUTEX_H
