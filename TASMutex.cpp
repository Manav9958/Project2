// TASMutex.cpp
#include <atomic>
#include <vector>
#include <memory>
#include "TASMutex.h"

std::unique_ptr<TASMutex> mutex(new TASMutex());

// TASMutex class encapsulates the TestAnd Set algorithm. It uses an atomic_flag as the lock.
TASMutex::TASMutex() {
    // Initialize the lock to false (clear state)
    lock_flag.clear(std::memory_order_release);
}

// The lock method repeatedly calls test_and_set until it acquires the lock.
// test_and_set sets the flag to true and returns the previous value.
// If the previous value was false, it means the lock was not held by any thread and now it's acquired by the current thread.
void TASMutex::lock(int thread_id) {
    while (lock_flag.test_and_set(std::memory_order_acquire));
}

// The unlock method simply sets the flag to false, releasing the lock.
void TASMutex::unlock(int thread_id) {
    lock_flag.clear(std::memory_order_release);
}
