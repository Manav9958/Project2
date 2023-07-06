#include "PetersonMutex.h"
#include <cmath>
#include <thread>  // <-- Add this line

PetersonMutex::PetersonMutex()
{
    flag[0].store(false, std::memory_order_relaxed);
    flag[1].store(false, std::memory_order_relaxed);
    victim.store(0, std::memory_order_relaxed);
}


void PetersonMutex::lock(int thread_id)
{
    flag[thread_id].store(true, std::memory_order_relaxed);
    victim.store(thread_id, std::memory_order_relaxed);
    while (flag[1 - thread_id].load(std::memory_order_relaxed) && victim.load(std::memory_order_relaxed) == thread_id)
    {
        std::this_thread::yield();  // <-- Add this line
    }
}

void PetersonMutex::unlock(int thread_id)
{
    flag[thread_id].store(false, std::memory_order_relaxed);
}
