#include "periodic_executor.hpp"

#include <iostream>
#include <thread>

namespace mt {

PeriodicExecutor::PeriodicExecutor(size_t a_capacity)
: m_tasks(a_capacity + 2) //2 extra place for dummy task and returning task
, m_capacity(a_capacity)
, m_executor([this]() { run(); })
{
}

PeriodicExecutor::~PeriodicExecutor()
{
    {
		std::unique_lock<std::mutex> lkStop(m_mtxStop);
		m_stop = true;
	}
    //resume may cause one more task run after pause when the d-tor will activated
	resume();

    //prevent waiting in dequeue
    addDummyTask();

    m_executor.join();

}

void PeriodicExecutor::addDummyTask()
{
    auto apple = [](){std::cout << "apple\n";};
    Task t(apple, std::chrono::milliseconds(0));
    m_tasks.enqueue(t);
    m_cvWaitingTask.notify_all();
}

bool PeriodicExecutor::stopRequested()
{
    std::unique_lock<std::mutex> lkStop(m_mtxStop);
    if(m_stop) {
        return true;
    }
    return false;
}

void PeriodicExecutor::pauseRequested()
{
    std::unique_lock<std::mutex> lkPause(m_mtxPause);
    m_cvPause.wait(lkPause, [this]{return !m_pause;});
    lkPause.unlock();
}

void PeriodicExecutor::run()
{
    for(;;) {
        if(stopRequested()) {
            break;
        }
        pauseRequested();

        if(!stopRequested()) {
            runTask();
        }
    }
}

void PeriodicExecutor::runTask()
{
    Task t;
    m_tasks.dequeue(t);

    pauseRequested();

    if(!stopRequested()) {
        std::unique_lock<std::mutex> lkTask(m_mtxTask);
        //if run task return false - put it back into the queue
        if(!t.run(lkTask, m_cvWaitingTask)) {
            m_tasks.enqueue(t);
        }
    }
}

void PeriodicExecutor::pause()
{
    std::unique_lock<std::mutex> lkPause(m_mtxPause);
    m_pause = true;
}

void PeriodicExecutor::resume()
{
    std::unique_lock<std::mutex> lkPause(m_mtxPause);
    m_pause = false;
    m_cvPause.notify_all();
}

void PeriodicExecutor::submit(std::function<bool()> a_function
                        , std::chrono::milliseconds a_period)
{
    if(m_tasks.size() == m_capacity) {
        throw std::overflow_error("out of place for tasks");
    }
    if(!stopRequested())
    {
        Task t(a_function, a_period);
        m_tasks.enqueue(t);
        m_cvWaitingTask.notify_one();
    }
}

void PeriodicExecutor::submit(std::function<void()> a_function
                            , std::chrono::milliseconds a_period)
{
    if(m_tasks.size() == m_capacity) {
        throw std::overflow_error("out of place for tasks");
    }
    if(!stopRequested())
    {
        Task t(a_function, a_period);
        m_tasks.enqueue(t);
        m_cvWaitingTask.notify_one();
    }
}

void PeriodicExecutor::submit(std::function<void()> a_function
                            , std::chrono::milliseconds a_period
                            , uint64_t a_repeat_count)
{
    if(m_tasks.size() == m_capacity) {
        throw std::overflow_error("out of place for tasks");
    }
    if(!stopRequested())
    {
        assert(a_repeat_count > 0);
        Task t(a_function, a_period, a_repeat_count);
        m_tasks.enqueue(t);
        m_cvWaitingTask.notify_one();
    }
}

} //namespace mt
