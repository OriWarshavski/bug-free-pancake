#pragma once

#include <cstddef>
#include <semaphore.h>

#include "waitable_queue.hpp"
#include "thread_group.hpp"
#include "semaphore.hpp"
#include "strong_types.hpp"

namespace mt {

using Capacity = implementation_details::Capacity;
using Threads = implementation_details::Threads;

class ThreadPool {
public: 
    static const size_t MaximumThreads = 8; //in case of unknown number of cores
    //if maxThreads < minThreads ---> maxThreads = minThreads
    explicit ThreadPool(Capacity a_capacity, Threads a_minimum, Threads a_maximum);
    explicit ThreadPool(Capacity a_capacity, Threads a_minThreadsNum);
    explicit ThreadPool(Capacity a_capacity);

    ThreadPool(const ThreadPool &a_other) = delete;
    ThreadPool& operator=(const ThreadPool &a_other) = delete;
    ~ThreadPool();

    void shutDown();

    //if task throwing exception it will thrown out of the pool
    using functionType = std::function<void(std::atomic<bool>&)>;

    void submit(functionType a_task);
    void addWorkers(size_t a_toAdd);       //to limit of m_maxThreadsNum   
    void removeWorkers(size_t a_toRemove); //at least 1 thread will remain
    size_t workersAmount() const;          

private:
    void worker(std::atomic<bool>& a_askTerminate, std::atomic<bool>& a_readyToExit);
    void runTask(std::atomic<bool>& a_askTerminate, std::atomic<bool>& a_readyToExit);
    bool shutDownRequested(std::atomic<bool>& a_askTerminate, std::atomic<bool>& a_readyToExit);
    void addDummyTask(semaphore::Semaphore* a_sem);
    size_t updateDefaultMaxThreads() noexcept;
    void poisonAndRemove(size_t a_toRemove);

private:
    Capacity m_capacity;
    Threads m_minimum;
    Threads m_maximum;

    std::atomic<bool> m_atomicShutDown;

    advcpp::WaitableQueue<functionType> m_tasks;
    ThreadGroup m_workers;
};

} // namespace mt