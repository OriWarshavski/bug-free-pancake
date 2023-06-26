#pragma once

#include <thread>
#include <vector>
#include <atomic>
#include <functional>

namespace mt::implementation_details {

using askToTerminate = std::atomic<bool>&;
using ReadyToExit = std::atomic<bool>&;

using TaskType = std::function<void(askToTerminate, ReadyToExit)>;

struct ThreadPack {
    explicit ThreadPack(TaskType a_task);
    ~ThreadPack();

    std::atomic<bool> m_askForTerminate;
    std::atomic<bool> m_readyToExit;
    std::thread m_thread;
};

} //namespace mt::implementation_details
