#include <iostream>

#include "mu_test.h"
#include "thread_group.hpp"

using namespace mt;

void task(std::atomic<bool>& a_askTerminate, std::atomic<bool>& a_readyToExits)
{
    int count = 0;
    for(;;) {
        if(a_askTerminate) {
            break;
        }
        std::cout << ++count << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(count == 10) {
            a_readyToExits = true;
        }
    }
}

BEGIN_TEST(test)
    ThreadGroup group(5, task);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    group.removeWorkers(4);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    group.shutDown();
    try {
        group.addWorkers(6);
    } catch(...) {
        ASSERT_THAT(true);
    }
END_TEST

TEST_SUITE()
    TEST(test)

END_SUITE
