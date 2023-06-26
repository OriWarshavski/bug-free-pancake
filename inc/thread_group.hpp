#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <memory>

#include "thread_pack.hpp"

namespace mt {

using TaskType = mt::implementation_details::TaskType;

class ThreadGroup {
public:
    explicit ThreadGroup(size_t a_numOfThreads, TaskType a_task);
    ThreadGroup(const ThreadGroup &a_other) = delete;
    ThreadGroup& operator=(const ThreadGroup &a_other) = delete;
    ~ThreadGroup();

    void shutDown();
    void addWorkers(size_t a_amount);
    void removeWorkers(size_t a_amount); //will remove first tasks who sign ReadyToExit
    size_t size() const noexcept;

private:
    void InnerAddWorkers(size_t a_addThreads);
    void InnerRemoveWorker();

private:
    bool m_isShutDown;
    mutable std::mutex m_mtxShutDown;

    size_t m_numOfThreads;

    using ThreadPack = implementation_details::ThreadPack;
    std::vector<std::shared_ptr<ThreadPack>> m_threads;
    TaskType m_task;

    mutable std::mutex m_mtxThreads;
};


} //namespace mt
