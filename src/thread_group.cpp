#include <iostream>
#include "thread_group.hpp"

namespace mt {

ThreadGroup::ThreadGroup(size_t a_numOfThreads, TaskType a_task)
: m_isShutDown(false)
, m_numOfThreads(0)
, m_threads{}
, m_task(a_task)
{
    InnerAddWorkers(a_numOfThreads);
}

ThreadGroup::~ThreadGroup()
{

    shutDown();
}

void ThreadGroup::shutDown()
{
    {
        std::unique_lock<std::mutex> lk(m_mtxShutDown);
        m_isShutDown = true;
    }
    removeWorkers(m_numOfThreads);
}

void ThreadGroup::addWorkers(size_t a_amountToAdd)
{
    std::unique_lock<std::mutex> lk(m_mtxShutDown);
    if(m_isShutDown){
        throw std::domain_error("add after shutdown");
    }
    lk.unlock();
    InnerAddWorkers(a_amountToAdd);
}

void ThreadGroup::removeWorkers(size_t a_amountToRemove)
{
    std::unique_lock<std::mutex> lk(m_mtxThreads);
    a_amountToRemove = std::min(a_amountToRemove, m_numOfThreads);


    //remove who is ready
    auto it = m_threads.begin();
    auto end = m_threads.end();
    while((it != end) && (a_amountToRemove > 0)) { 
        if((*it) -> m_readyToExit) {
            (*it) -> m_askForTerminate = true;
            --a_amountToRemove;
            it = m_threads.erase(it);
            --m_numOfThreads;
        }
        else {
            ++it;
        }
    }
    //remove the rest from the end
    while(a_amountToRemove > 0) {
        InnerRemoveWorker();
        --a_amountToRemove;
    }
}

size_t ThreadGroup::size() const noexcept
{
    std::unique_lock<std::mutex> lk(m_mtxThreads);
    return m_numOfThreads;
}


void ThreadGroup::InnerRemoveWorker()
{
    if(m_numOfThreads == 0) {
        return;
    }
    auto th = m_threads.back();

    th -> m_askForTerminate = true;

    m_threads.pop_back();
    --m_numOfThreads;
}

void ThreadGroup::InnerAddWorkers(size_t a_addThreads)
{
    std::unique_lock<std::mutex> lk(m_mtxThreads);
    m_numOfThreads += a_addThreads;
    m_threads.reserve(m_numOfThreads);
    for(size_t i = 0; i < a_addThreads; ++i) {
        m_threads.emplace_back(new ThreadPack(m_task));
    } 
}

} //namespace mt 