#include <iostream>

#include "mu_test.h"
#include "thread_pool.hpp"

using namespace mt;

BEGIN_TEST(test_submit_after_shutDown)
    ThreadPool pool(Capacity{4}, Threads{1}, Threads{4});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    ASSERT_EQUAL(pool.workersAmount(), 1);

    pool.shutDown();

    ASSERT_EQUAL(pool.workersAmount(), 0);
    try {
        pool.submit([](std::atomic<bool>& a_readyToExit){});
    } catch(...) {
        ASSERT_THAT(true);
    }

    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(test_add_workers)
    ThreadPool pool(Capacity{4}, Threads{1}, Threads{4});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    ASSERT_EQUAL(pool.workersAmount(), 1);
    pool.addWorkers(2);
    ASSERT_EQUAL(pool.workersAmount(), 3);
    pool.addWorkers(2);
    ASSERT_EQUAL(pool.workersAmount(), 4);
END_TEST

BEGIN_TEST(test_remove_workers)
    ThreadPool pool(Capacity{4}, Threads{5});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    ASSERT_EQUAL(pool.workersAmount(), 5);
    pool.removeWorkers(2);
    ASSERT_EQUAL(pool.workersAmount(), 3);
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
END_TEST

BEGIN_TEST(test_too_many_remove_workers)
    ThreadPool pool(Capacity{4}, Threads{2});
    pool.submit([](std::atomic<bool>& a_readyToExit){});
    ASSERT_EQUAL(pool.workersAmount(), 2);
    pool.removeWorkers(6);
    ASSERT_EQUAL(pool.workersAmount(), 1);
END_TEST

BEGIN_TEST(task_throwing_an_exception)
    ThreadPool pool(Capacity{4}, Threads{2});
    pool.submit([](std::atomic<bool>& a_readyToExit) {
        throw std::domain_error("test");
    });
    ASSERT_EQUAL(pool.workersAmount(), 2);
END_TEST

BEGIN_TEST(add_too_many_tasks)
    ThreadPool pool(Capacity{1});
    pool.submit([](std::atomic<bool>& a_readyToExit) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    });

    try {
        pool.submit([](std::atomic<bool>& a_readyToExit) {});
        pool.submit([](std::atomic<bool>& a_readyToExit) {});
        pool.submit([](std::atomic<bool>& a_readyToExit) {});

    } catch(...) {
        ASSERT_THAT(true);
    }
            ASSERT_THAT(true);

END_TEST

BEGIN_TEST(end_task_after_shutdown)
    ThreadPool pool(Capacity{3}, Threads{1});
    int count = 0;
    pool.submit([&count](std::atomic<bool>& a_readyToExit) {
        while(count < 100) {
            ++count;
        }
    });
    int count2 = 0;
    pool.submit([&count2](std::atomic<bool>& a_readyToExit) {
        while(count2 < 100) {
            ++count2;
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    pool.shutDown();
    ASSERT_EQUAL(count, 100);
    ASSERT_EQUAL(count2, 100);
END_TEST

TEST_SUITE()
    TEST(test_submit_after_shutDown)
    TEST(test_add_workers)
    TEST(test_remove_workers)
    TEST(test_too_many_remove_workers)
    TEST(task_throwing_an_exception)
    TEST(add_too_many_tasks)
    TEST(end_task_after_shutdown)

END_SUITE
