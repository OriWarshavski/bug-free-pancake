#pragma once

#include <functional>
#include <chrono>
#include <condition_variable>

namespace mt::implementation_details {

class Task {

    using Time = std::chrono::steady_clock::time_point;
    enum class ExitStaus{DONE, CONTINUE};

public:
    Task() = default;
    explicit Task(std::function<bool()> a_function, std::chrono::milliseconds a_period);
    explicit Task(std::function<void()> a_function, std::chrono::milliseconds a_period);
    explicit Task(std::function<void()> a_function, std::chrono::milliseconds a_period, uint64_t a_repeatCount);
    Task(const Task &a_other) = default;
    Task& operator=(const Task &a_other) = default;
    ~Task() = default;

    bool run(std::unique_lock<std::mutex>& a_mtx, std::condition_variable& a_cvWaitingTasks);
    void timeUpdate();
    Time time() const noexcept;

private:
    auto sleepTime() const noexcept;
    using NeedToRepeat = bool;
    ExitStaus runFunction();

private:
    std::function<bool()> m_boolFunction;
    std::function<void()> m_voidFunction;
    std::chrono::milliseconds m_period;
    uint64_t m_repeatCount;

    Time m_nextStartTime;
};

bool operator<(const Task &a_first, const Task &a_second);

} //namespace mt::implementation_details
