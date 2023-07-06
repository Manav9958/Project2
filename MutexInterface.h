#ifndef MUTEX_INTERFACE_H
#define MUTEX_INTERFACE_H

class MutexInterface {
public:
    virtual ~MutexInterface() = default;
    virtual void lock(int thread_id) = 0;
    virtual void unlock(int thread_id) = 0;
};

#endif // MUTEX_INTERFACE_H
