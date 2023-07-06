#include <iostream>
#include <thread>
#include <vector>
#include "MutexInterface.h"
#include "TASMutex.h"
#include "PetersonMutex.h"
#include "TournamentTreeMutex.h"
#include "FAIMutex.h"


// global mutex to protect std::cout
std::mutex mtx;

void doWork(int id, MutexInterface& mutex, std::vector<int>& counter) {
    for (int i = 0; i < counter.size(); ++i) {
        {
            std::lock_guard<std::mutex> lck(mtx);
            std::cout << "Thread " << id << " attempting to acquire lock.\n";
        }
        mutex.lock(id);
        {
            std::lock_guard<std::mutex> lck(mtx);
            std::cout << "Thread " << id << " acquired lock.\n";
            ++counter[0];
            std::cout << "Thread " << id << " releasing lock.\n";
        }
        mutex.unlock(id);
        {
            std::lock_guard<std::mutex> lck(mtx);
            std::cout << "Thread " << id << " released lock.\n";
        }
    }
}

int main() {
    // Use the mutex of your choice here
    auto mutex = std::make_unique<TASMutex>();

    std::vector<int> counter(1, 0);
    int num_threads = 5;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(doWork, i, std::ref(*mutex), std::ref(counter)));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Counter value: " << counter[0] << std::endl;

    return 0;
}
