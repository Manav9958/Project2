#ifndef TOURNAMENT_TREE_MUTEX_H
#define TOURNAMENT_TREE_MUTEX_H

#include "MutexInterface.h"
#include "PetersonMutex.h"
#include <vector>
#include <memory>

class TournamentTreeMutex : public MutexInterface {
public:
    explicit TournamentTreeMutex(int num_threads);
    void lock(int thread_id) override;
    void unlock(int thread_id) override;
private:
    std::vector<std::unique_ptr<PetersonMutex>> tree;
};

#endif // TOURNAMENT_TREE_MUTEX_H
