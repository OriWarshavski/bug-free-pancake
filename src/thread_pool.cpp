#include <iostream>

#include "thread_pool.hpp"

namespace mt {

ThreadPool::ThreadPool(Capacity a_capacity, Threads a_minimum, Threads a_maximum)
: m_capacity(a_capacity)
, m_minimum(a_minimum)
, m_maximum(a_maximum)
, m_atomicShutDown(false)
, m_tasks(m_capacity + m_maximum) //extra places for dummy task
, m_workers(m_minimum, [this](std::atomic<bool>& a_askTerminate
                           , std::atomic<bool>& a_readyToExit) 
                            { worker(a_askTerminate, a_readyToExit); })
{
    if(m_minimum > m_maximum) {
        m_maximum = m_minimum;
    }
}

ThreadPool::ThreadPool(Capacity a_capacity, Threads a_minimum)
: m_capacity(a_capacity)
, m_minimum(a_minimum)
, m_maximum(updateDefaultMaxThreads())
, m_atomicShutDown(false)
, m_tasks(m_capacity + m_maximum) //extra places for dummy task
, m_workers(m_minimum, [this](std::atomic<bool>& a_askTerminate
                           , std::atomic<bool>& a_readyToExit) 
                            { worker(a_askTerminate, a_readyToExit); })
{
    if(m_minimum > m_maximum) {
        m_maximum = m_minimum;
    }
}

ThreadPool::ThreadPool(Capacity a_capacity)
: m_capacity(a_capacity)
, m_minimum(1)
, m_maximum(updateDefaultMaxThreads())
, m_atomicShutDown(false)
, m_tasks(m_capacity + m_maximum) //extra places for dummy task
, m_workers(m_minimum, [this](std::atomic<bool>& a_askTerminate
                           , std::atomic<bool>& a_readyToExit) 
                            { worker(a_askTerminate, a_readyToExit); })
{
    if(m_minimum > m_maximum) {
        m_maximum = m_minimum;
    }
}

size_t ThreadPool::updateDefaultMaxThreads() noexcept
{
    unsigned int cores = std::thread::hardware_concurrency();
    if(cores != 0)
    {
        return cores;
    }
    else {
        return MaximumThreads;
    }
}

ThreadPool::~ThreadPool()
{
    shutDown();
}

void ThreadPool::shutDown()
{
    if(m_atomicShutDown) {
        return;
    }

    removeWorkers(m_workers.size() - 1);

    //remove last one
    addDummyTask(nullptr);
    m_workers.removeWorkers(1);

    m_atomicShutDown = true;

}

void ThreadPool::submit(std::function<void(std::atomic<bool>&)> a_task)
{
    if(m_atomicShutDown) {
        throw std::domain_error("cant add task after shutdown");
    }

    if(m_tasks.size() == m_capacity) {
        throw std::domain_error("the pool is full of tasks");
    }

    m_tasks.enqueue(a_task);
}

void ThreadPool::addWorkers(size_t a_toAdd)
{
    if(m_atomicShutDown) {
        throw std::domain_error("cant add worker after shutdown");
    }

    //cant add more than maxThreads
    if((m_workers.size() + a_toAdd) > m_maximum) {
        a_toAdd = m_maximum - m_workers.size();
    }
    m_workers.addWorkers(a_toAdd);
}

void ThreadPool::removeWorkers(size_t a_toRemove)
{
    if(m_atomicShutDown) {
        throw std::domain_error("cant remove worker after shutdown");
    }
    size_t workersSize = m_workers.size();
    assert(workersSize > 0);

    //need to be at least 1 worker after remove
    a_toRemove = std::min(a_toRemove, workersSize - 1);
    if(a_toRemove == 0) {
        return;
    }

    poisonAndRemove(a_toRemove);
}

void ThreadPool::poisonAndRemove(size_t a_toRemove)
{
    semaphore::Semaphore semCountPoisoned{0};

    for(size_t i = 0; i < a_toRemove; ++i) {
        addDummyTask(&semCountPoisoned);
    }
    // Wait for all workers threads to complete
    semCountPoisoned.aquire(a_toRemove);

    m_workers.removeWorkers(a_toRemove);
}

void ThreadPool::addDummyTask(semaphore::Semaphore* a_semCountPoisoned)
{
    auto apple = [a_semCountPoisoned](std::atomic<bool>& a_readyToExit) {
        a_readyToExit = true;
        if(a_semCountPoisoned != nullptr) {
            (*a_semCountPoisoned).relese(1);
        }
    };
    m_tasks.enqueue(apple);
}

size_t ThreadPool::workersAmount() const
{
    return m_workers.size();
}


bool ThreadPool::shutDownRequested(std::atomic<bool>& a_askTerminate, std::atomic<bool>& a_readyToExit)
{
    if(a_askTerminate || a_readyToExit || m_atomicShutDown)
    {
        return true;
    }
    return false;
}

void ThreadPool::worker(std::atomic<bool>& a_askTerminate, std::atomic<bool>& a_readyToExit)
{
    for(;;) {
        if(shutDownRequested(a_askTerminate, a_readyToExit)) {
            break;
        }
        runTask(a_askTerminate, a_readyToExit);
    }
}

void ThreadPool::runTask(std::atomic<bool>& a_askTerminate, std::atomic<bool>& a_readyToExit)
{
    std::function<void(std::atomic<bool>&)> task;
    //waiting for tasks
    m_tasks.dequeue(task);
    if(!shutDownRequested(a_askTerminate, a_readyToExit)) {
        try {
            task(a_readyToExit);
        } catch (std::exception const& x) {
            std::cerr << "exeption in task is: " << x.what() << "\nthrown out of the pool\n";
        } catch (...) {
            std::cerr << "unknown exeption in task\n thrown out of the pool\n";
        }
    }
}

} // namespace mt
