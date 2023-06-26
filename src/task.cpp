#include <iostream>

#include "task.hpp"

namespace mt::implementation_details {

Task::Task(std::function<bool()> a_function, std::chrono::milliseconds a_period)
: m_boolFunction(a_function)
, m_period(a_period)
, m_repeatCount(0)
{
    timeUpdate();
}

Task::Task(std::function<void()> a_function, std::chrono::milliseconds a_period)
: m_voidFunction(a_function)
, m_period(a_period)
, m_repeatCount(0)
{
    timeUpdate();
}

Task::Task(std::function<void()> a_function, std::chrono::milliseconds a_period, uint64_t a_repeatCount)
: m_voidFunction(a_function)
, m_period(a_period)
, m_repeatCount(a_repeatCount)
{
    timeUpdate();
}

auto Task::sleepTime() const noexcept
{
    return m_nextStartTime - std::chrono::steady_clock::now();
}

Task::ExitStaus Task::runFunction()
{
    ExitStaus status = ExitStaus::CONTINUE;
    if(m_boolFunction) {
        //if returning true - DO NOT repeat
        if(m_boolFunction()) {
            status = ExitStaus::DONE;
        }
    }
    else if(m_voidFunction) {
        m_voidFunction();
        //there are more repeats
        if(m_repeatCount > 1) {
            --m_repeatCount;
        } 
        //there are no repeats: m_repeatCount == 1
        else if (m_repeatCount == 1) {
            status = ExitStaus::DONE;
        }
        //repeats to infinity: m_repeatCount == 0
    }
    return status;
}

bool Task::run(std::unique_lock<std::mutex>& a_mtx, std::condition_variable& a_cvWaitingTasks)
{
    std::cv_status cvs = a_cvWaitingTasks.wait_for(a_mtx, sleepTime());
    //awake but start time has not yet come
    if(cvs == std::cv_status::no_timeout) {
        return false;
    }
    try {
        if(runFunction() == ExitStaus::CONTINUE) {
            timeUpdate();
            return false;
        }
    } catch (std::exception const& x) {
        std::cerr << "exeption in task: " << x.what() << '\n';
    } catch (...) {
        std::cerr << "unknown exeption in task\n";
    }
    return true;
}

Task::Time Task::time() const noexcept
{
    return m_nextStartTime;
}

void Task::timeUpdate()
{
    m_nextStartTime = std::chrono::steady_clock::now() + m_period;
}

bool operator<(const Task &a_first, const Task &a_second)
{
    return a_first.time() > a_second.time();
}


} //mt::implementation_details