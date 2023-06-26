#include <iostream>
#include <thread>
#include <chrono>
#include <exception>
#include <vector>

#include "mu_test.h"
#include "periodic_executor.hpp"

using namespace mt;
using namespace std::chrono;

int rep1;
void task1() {
    ++rep1;
}

int rep2;
void task2() {
    ++rep2;
}

BEGIN_TEST(run_task_4_times)
    rep1 = 0;
    PeriodicExecutor pe(1);
    pe.submit(task1, std::chrono::milliseconds(20), 4);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQUAL(rep1, 4);
END_TEST

BEGIN_TEST(run_task_2_times_and_pause)
    rep1 = 0;
    PeriodicExecutor pe(1);
    pe.submit(task1, std::chrono::milliseconds(20));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    pe.pause();
    ASSERT_EQUAL(rep1, 2);
END_TEST

BEGIN_TEST(run_task_2_times_pause_and_resume)
    rep1 = 0;
    PeriodicExecutor pe(1);
    pe.submit(task1, std::chrono::milliseconds(20));
    std::this_thread::sleep_for(std::chrono::milliseconds(49));
    pe.pause();
    ASSERT_EQUAL(rep1, 2);
    pe.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(45));
    ASSERT_EQUAL(rep1, 4);
END_TEST

BEGIN_TEST(two_tasks)
    rep1 = 0;
    rep2 = 0;
    PeriodicExecutor pe(2);
    pe.pause();
    pe.submit(task1, std::chrono::milliseconds(20));
    pe.submit(task2, std::chrono::milliseconds(10));
    pe.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(45));
    pe.pause();
    ASSERT_EQUAL(rep1, 2);
    ASSERT_EQUAL(rep2, 4);
    pe.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(45));
    ASSERT_EQUAL(rep1, 4);
    ASSERT_EQUAL(rep2, 8);
END_TEST

BEGIN_TEST(submit_overflow)
    rep1 = 0;
    PeriodicExecutor pe(2);
    pe.submit(task1, std::chrono::milliseconds(20));
    pe.submit(task1, std::chrono::milliseconds(10));
    try {
        pe.submit(task1, std::chrono::milliseconds(40));
    } catch(std::overflow_error const& x) {

        ASSERT_THAT(true);
    }
END_TEST

using mili = std::chrono::milliseconds;

BEGIN_TEST(timing_check_one_task)
    std::vector<steady_clock::time_point> timingDocument{};
    mili epsilon = mili(5);

    timingDocument.reserve(10);
    auto task = [&timingDocument]() {
        // std::cout << "task\n";
        timingDocument.emplace_back(std::chrono::steady_clock::now());
    };

    PeriodicExecutor pe(100);
    pe.pause();
    pe.submit(task, mili(10));

    steady_clock::time_point t0 = std::chrono::steady_clock::now();
    pe.resume();
    std::this_thread::sleep_for(mili(1000));
    pe.pause();
   
    for(auto e : timingDocument) {
        mili delta = std::chrono::duration_cast<mili>(e - t0);
        ASSERT_THAT(delta >= mili(10)
        && delta <= mili(10) + epsilon);
        t0 = e;
    }
END_TEST

BEGIN_TEST(timing_check_2_tasks)
    mili epsilon = mili(5);

    std::vector<steady_clock::time_point> timingDocument1{};
    timingDocument1.reserve(10);

    auto task1 = [&timingDocument1]() {
        // std::cout << "task1\n";
        timingDocument1.emplace_back(std::chrono::steady_clock::now());
    };

    std::vector<steady_clock::time_point> timingDocument2{};
    timingDocument2.reserve(10);

    auto task2 = [&timingDocument2]() {
        // std::cout << "task2\n";
        timingDocument2.emplace_back(std::chrono::steady_clock::now());
    };

    PeriodicExecutor pe(100);
    pe.pause();
    pe.submit(task1, mili(15));
    pe.submit(task2, mili(21));

    steady_clock::time_point t0 = std::chrono::steady_clock::now();
    pe.resume();
    std::this_thread::sleep_for(mili(1000));
    pe.pause();
    steady_clock::time_point save = t0;
    for(auto e : timingDocument1) {
        mili delta = std::chrono::duration_cast<mili>(e - t0);
        ASSERT_THAT(delta >= mili(15)
        && delta <= mili(15) + epsilon);
        t0 = e;
    }
    t0 = save;
    for(auto e : timingDocument2) {
        mili delta = std::chrono::duration_cast<mili>(e - t0);
        ASSERT_THAT(delta >= mili(21)
        && delta <= mili(21) + epsilon);
        t0 = e;
    }
END_TEST

TEST_SUITE()
    TEST(run_task_4_times)
    TEST(run_task_2_times_and_pause)
    TEST(run_task_2_times_pause_and_resume)
    TEST(two_tasks)
    TEST(submit_overflow)
    TEST(timing_check_one_task)
    TEST(timing_check_2_tasks)
END_SUITE