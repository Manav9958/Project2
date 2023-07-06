// FAIMutex.cpp
#include <atomic>
#include <vector>
#include <memory>
#include "FAIMutex.h"

FAIMutex::FAIMutex(int num_threads) : counter(0), next_ticket(0) {
    for(int i=0; i<num_threads; i++)
    {
        turn.push_back(std::make_shared<std::atomic<int>>(0));
    }
}

void FAIMutex::lock(int thread_id) {
    int my_turn = counter.fetch_add(1, std::memory_order_relaxed);
    while ((*turn[thread_id]).load(std::memory_order_acquire) != my_turn);
}

void FAIMutex::unlock(int thread_id) {
    (*turn[thread_id]).store(next_ticket.fetch_add(1, std::memory_order_relaxed), std::memory_order_release);
}

