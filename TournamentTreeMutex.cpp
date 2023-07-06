#include <iostream>
#include <cmath>
#include <deque> 
#include "TournamentTreeMutex.h"

std::mutex cout_mutex; // A global mutex for std::cout

TournamentTreeMutex::TournamentTreeMutex(int num_threads)
{
    int tree_size = 2 * pow(2, ceil(log2(num_threads))) - 1;
    tree.resize(tree_size);
    for (int i = 0; i < tree_size; ++i) {
        tree[i] = std::unique_ptr<PetersonMutex>();
    }
}

void TournamentTreeMutex::lock(int thread_id)
{
    int index = tree.size() / 2 + thread_id;
    while (index > 0)
    {
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::cout << "Thread " << thread_id << " attempting to acquire lock with index " << index << ".\n";
        tree[index]->lock(thread_id % 2);
        index = (index - 1) / 2; // update the index for the next iteration
    }
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << "Thread " << thread_id << " attempting to acquire lock with index " << 0 << ".\n";
    tree[0]->lock(thread_id % 2);
    std::cout << "Thread " << thread_id << " acquired lock with index " << 0 << ".\n";
}

void TournamentTreeMutex::unlock(int thread_id)
{
    std::deque<int> path;
    int index = tree.size() / 2 + thread_id;
    while (index > 0)
    {
        path.push_front(index);
        index = (index - 1) / 2;
    }
    path.push_front(0);
    for (int index : path)
    {
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::cout << "Thread " << thread_id << " releasing lock with index " << index << ".\n";
        tree[index]->unlock(thread_id % 2);
    }
}
