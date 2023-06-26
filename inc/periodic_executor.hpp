#pragma once

#include <thread>
#include <condition_variable>

#include "waitable_queue.hpp"
#include "task.hpp"

namespace mt {

class PeriodicExecutor {
public:
    explicit PeriodicExecutor(size_t a_capacity); // create one thread to run the tasks
    PeriodicExecutor(const PeriodicExecutor &a_other) = delete;
    PeriodicExecutor& operator=(const PeriodicExecutor &a_other) = delete;
    ~PeriodicExecutor();

    void submit(std::function<bool()> a_function, std::chrono::milliseconds a_period);
    void submit(std::function<void()> a_function, std::chrono::milliseconds a_period);
    void submit(std::function<void()> a_function, std::chrono::milliseconds a_period, uint64_t a_repeat_count);

    void pause();
    void resume();

private:
    //if task is throwing exeption it will deleted from the queue
    void run();
    void runTask();
    bool stopRequested();
    void pauseRequested();
    void addDummyTask();

private:
    using Task = mt::implementation_details::Task;
    advcpp::WaitableQueue<Task, std::priority_queue<Task>> m_tasks;
    const size_t m_capacity;

    bool m_pause = false;
    std::condition_variable m_cvPause;
    std::mutex mutable m_mtxPause;

    bool m_stop = false;
    std::mutex mutable m_mtxStop;

    std::condition_variable m_cvWaitingTask;
    std::mutex mutable m_mtxTask;
    std::thread m_executor;
};


} //namespace mt
