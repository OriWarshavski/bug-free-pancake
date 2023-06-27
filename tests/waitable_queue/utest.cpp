#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

#include "mu_test.h"
#include "waitable_queue.hpp"

using namespace advcpp;
using namespace std::chrono;

class Dog {
public:
    enum class Bread {SHI_ZU, GOLDEN, PUG, CHIHUAHUA, KING_CHARLS, POODLE, CRESTED_CHINESE, MORK_SKYWALKER};
    Dog()
    : m_id(0)
    , m_bread(Bread::SHI_ZU)
    , m_adopted(false)
    {};

    Dog(size_t a_id, Bread a_type)
    : m_id(a_id)
    , m_bread(a_type)
    , m_adopted(false)
    {};

    Dog(const Dog &a_other)
    : m_id(a_other.m_id)
    , m_bread(a_other.m_bread)
    , m_adopted(a_other.m_adopted)
    {}

    Dog& operator=(const Dog &a_other)
    {
        if(this != &a_other) {
            m_id = a_other.m_id;
            m_bread = a_other.m_bread;
            m_adopted = a_other.m_adopted;
        }
        return *this;
    }

    size_t id() const noexcept {return m_id;};
    Bread bread() const noexcept {return m_bread;};
    void changeToAdopted() noexcept {m_adopted = true;};
    void setBread(Dog::Bread a_bread) noexcept {m_bread = a_bread;};

private:
    size_t m_id;
    Bread m_bread;
    bool m_adopted;
};

bool operator<(Dog const& a_first, Dog const& a_second)
{
    return a_first.id() < a_second.id();
}

BEGIN_TEST(one_thread_1000_capacity_and_size)
    constexpr auto size = 1'000UL;
	WaitableQueue<Dog> q(size);
    ASSERT_EQUAL(q.size(), 0);
    ASSERT_THAT(q.empty());

    for(size_t i = 0; i < size; ++i) {
        q.enqueue(Dog{i, static_cast<Dog::Bread>(i % 8)});
        ASSERT_THAT(!q.empty());
        ASSERT_EQUAL(q.size(), i + 1);
    }
    ASSERT_THAT(q.full());

    for(size_t i = 0; i < size; ++i) {
        Dog d;
        q.dequeue(d);
        ASSERT_THAT(!q.full());
        ASSERT_EQUAL(q.size(), size - i - 1);
        ASSERT_EQUAL(d.id(), i);
        ASSERT_THAT(static_cast<size_t>(d.bread()) == i % 8);
    }
    ASSERT_THAT(q.empty());
END_TEST

BEGIN_TEST(one_thread_priority_queue)
    constexpr auto size = 1'000UL;
	WaitableQueue<Dog, std::priority_queue<Dog>> q(size);
    ASSERT_EQUAL(q.size(), 0);
    ASSERT_THAT(q.empty());

    //insert from 0 to 999
    for(size_t i = 1; i < size; ++i) {
        q.enqueue(Dog{i, static_cast<Dog::Bread>(i % 8)});
        ASSERT_THAT(!q.empty());
        ASSERT_EQUAL(q.size(), i);
    }
    //insert the biggest
    q.enqueue(Dog{1002, static_cast<Dog::Bread>(1002 % 8)});
    ASSERT_THAT(q.full());
    //first will be the last that was inserted because its the biggest
    Dog d;
    q.dequeue(d);
    ASSERT_EQUAL(d.id(), 1002);
    //dequeue need to take from 999 to 0
    for(size_t i = 1; i < size; ++i) {
        Dog d;
        q.dequeue(d);
        //std::cout << d.id() << '\n';
        ASSERT_THAT(!q.full());
        ASSERT_EQUAL(q.size(), size - i - 1);
        ASSERT_EQUAL(d.id(), size - i);
        ASSERT_THAT(static_cast<size_t>(d.bread()) == (size - i) % 8);
    }
    ASSERT_THAT(q.empty());
END_TEST

BEGIN_TEST(producer_consumer_1Kqueue_1Mdogs)
    constexpr auto size = 1'000UL;
    constexpr auto count = 1'000'000UL;
    WaitableQueue<Dog> q(size);
    std::thread producer([&q]() {
        for(size_t i = 0; i < count; ++i) {
            q.enqueue(Dog{i, static_cast<Dog::Bread>(i % 8)});
        }
    });

    bool isfifo = true;
    for(size_t i = 0; i < count; ++i) {
        Dog res;
        q.dequeue(res);
        if(res.id() != i) {
            isfifo = false;
            break;
        }
        if(static_cast<size_t>(res.bread()) != i % 8) {
            isfifo = false;
            break;
        }
    }
    producer.join();
    ASSERT_THAT(isfifo);
    ASSERT_THAT(q.empty());
END_TEST

static bool checkSortedByIndex(std::vector<size_t> a_vec)
{
    //auto prev = a_vec.begin();
    //auto itr = prev + 1;
    auto itr = a_vec.begin();
    auto end = a_vec.end();
    size_t i = 0;
    while(itr != end) {
        if((*itr) != i) {
            return false;
        }
        //std::cout << "itr: " << (*itr) << "prev: " << (*prev) << '\n';
        ++itr;
        //++prev;
        ++i;
    }
    if(i != 500'000) {
        return false;
    }
    return true;
}

BEGIN_TEST(two_producers_1_consumer)
    constexpr auto size = 1'000UL;
    constexpr auto count = 1'000'000UL;
	WaitableQueue<Dog> q(size);

    auto f_shizus = [&q]() {
        for(size_t i = 0; i < (count / 2); ++i) {
            q.enqueue(Dog{i, Dog::Bread::SHI_ZU});
        } };

    auto f_morks = [&q]() {
        for(size_t i = 0; i < (count / 2); ++i) {
            q.enqueue(Dog{i, Dog::Bread::MORK_SKYWALKER});
        } };

    std::thread producer1{f_shizus};
    std::thread producer2{f_morks};

    std::vector<Dog> check;
    check.reserve(count);
    for(size_t i = 0; i < count; ++i) {
        Dog d;
        q.dequeue(d);
        check.push_back(d);
    }

    producer1.join();
    producer2.join();

    std::vector<size_t> shizus;
    std::vector<size_t> morks;
    auto itr = check.begin();
    auto end = check.end();
    while(itr != end) {
        if((*itr).bread() == Dog::Bread::SHI_ZU) {
            shizus.push_back((*itr).id());
        }
        else if((*itr).bread() == Dog::Bread::MORK_SKYWALKER) {
            morks.push_back((*itr).id());
        }
        ++itr;
    }

    ASSERT_THAT(checkSortedByIndex(shizus));
    ASSERT_THAT(checkSortedByIndex(morks));
END_TEST

BEGIN_TEST(one_producers_2_consumers)
    constexpr auto size = 1'000UL;
    constexpr auto count = 1'000'000UL;
	WaitableQueue<Dog> q(size);

    std::vector<size_t> checkOne;
    std::vector<size_t> checkTwo;
    checkOne.reserve(count / 2);
    checkTwo.reserve(count / 2);

    auto f_one = [&q, &checkOne]() {
        for(size_t i = 0; i < (count / 2); ++i) {
            Dog d;
            q.dequeue(d);
            checkOne.push_back(d.id());
        } };

    auto f_two = [&q, &checkTwo]() {
        for(size_t i = 0; i < (count / 2); ++i) {
            Dog d;
            q.dequeue(d);
            checkTwo.push_back(d.id());
        } };

    std::thread consumer1{f_one};
    std::thread consumer2{f_two};

    for(size_t i = 0; i < count; ++i) {
        q.enqueue(Dog{i, static_cast<Dog::Bread>(i)});
    }

    consumer1.join();
    consumer2.join();

    ASSERT_THAT(is_sorted(checkOne.begin(), checkOne.end()));
    ASSERT_THAT(is_sorted(checkTwo.begin(), checkTwo.end()));
    ASSERT_THAT(q.empty());

    std::vector<size_t> counter(count, 0);
    for(size_t i = 0; i < count / 2; ++i) {
        ++counter[checkOne[i]];
        ++counter[checkTwo[i]];
    }
    bool isfifo = true;
    for(size_t e : counter){
        if(e != 1) {
            isfifo = false;
        }
    }
    ASSERT_THAT(isfifo);
END_TEST

static void joinAll(std::vector<std::thread>& a_tasks)
{
    auto itr = a_tasks.begin();
    auto end = a_tasks.end();
    while (itr != end) {
        (*itr).join();
        ++itr;
    }
}

BEGIN_TEST(two_producers_two_consumers)
    constexpr auto size = 1'000UL;
    constexpr auto count = 600'000UL;
    constexpr auto numOfThreads = 2;
	WaitableQueue<Dog> q(size);
    bool isfifo[numOfThreads];
    for(int i = 0; i < numOfThreads; ++i) {
        isfifo[i] = true;
    }
    auto f_consumer = [&q, &isfifo](size_t* a_counter) {
        size_t savePrevs[numOfThreads] = {0};
        for(size_t i = 0; i < (count / numOfThreads); ++i) {
            Dog d;
            q.dequeue(d);
            size_t breadNum = static_cast<size_t>(d.bread());
            if(savePrevs[breadNum] >= d.id()) {
                isfifo[breadNum] = false;
                break;
            }
            ++(a_counter[d.id() - 1]);
            savePrevs[breadNum] = d.id();
        } };

    auto f_producer = [&q](int a_type) {
        for(size_t i = 1; i <= (count / numOfThreads); ++i) {
            q.enqueue(Dog{i, static_cast<Dog::Bread>(a_type)});
        } };

    std::vector<std::thread> producers;
    producers.reserve(numOfThreads);
    std::vector<std::thread> consumers;
    consumers.reserve(numOfThreads);

    for(int i = 0; i < numOfThreads; ++i) {
        producers.emplace_back(f_producer, i);
    }

    size_t counters[numOfThreads][count / numOfThreads] = {};
    for(int i = 0; i < numOfThreads; ++i) {
        consumers.emplace_back(f_consumer, counters[i]);
    }

    joinAll(consumers);
    joinAll(producers);

    ASSERT_THAT(q.empty());
    for(auto e : isfifo) {
        ASSERT_THAT(e);
    }

    size_t accumulate[count / numOfThreads] = {0};
    for(int i = 0; i < numOfThreads; ++i) {
        for(size_t j = 0; j < count / numOfThreads; ++j) {
            accumulate[j] += counters[i][j];
        }
    }
    for(auto e : accumulate) {
        ASSERT_EQUAL(e, numOfThreads);
    }
END_TEST

BEGIN_TEST(four_producers_four_consumers)
    constexpr auto size = 1'000UL;
    constexpr auto count = 800'000UL;
    constexpr auto numOfThreads = 4;

	WaitableQueue<Dog> q(size);
    bool isfifo[numOfThreads];
    for(int i = 0; i < numOfThreads; ++i) {
        isfifo[i] = true;
    }
    auto f_consumer = [&q, &isfifo](size_t* a_counter) {
        size_t savePrevs[numOfThreads] = {0};
        for(size_t i = 0; i < (count / numOfThreads); ++i) {
            Dog d;
            q.dequeue(d);
            size_t breadNum = static_cast<size_t>(d.bread());
            if(savePrevs[breadNum] >= d.id()) {
                isfifo[breadNum] = false;
                break;
            }
            ++(a_counter[d.id() - 1]);
            savePrevs[breadNum] = d.id();
        } };

    auto f_producer = [&q](int a_type) {
        for(size_t i = 1; i <= (count / numOfThreads); ++i) {
            q.enqueue(Dog{i, static_cast<Dog::Bread>(a_type)});
        } };

    std::vector<std::thread> producers;
    producers.reserve(numOfThreads);
    std::vector<std::thread> consumers;
    consumers.reserve(numOfThreads);

    for(int i = 0; i < numOfThreads; ++i) {
        producers.emplace_back(f_producer, i);
    }

    size_t counters[numOfThreads][count / numOfThreads] = {};
    for(int i = 0; i < numOfThreads; ++i) {
        consumers.emplace_back(f_consumer, counters[i]);
    }

    joinAll(consumers);
    joinAll(producers);

    ASSERT_THAT(q.empty());
    for(auto e : isfifo) {
        ASSERT_THAT(e);
    }

    size_t accumulate[count / numOfThreads] = {};
    for(int i = 0; i < numOfThreads; ++i) {
        for(size_t j = 0; j < count / numOfThreads; ++j) {
            accumulate[j] += counters[i][j];
        }
    }
    for(auto e : accumulate) {
        ASSERT_EQUAL(e, numOfThreads);
    }
END_TEST

TEST_SUITE()
    TEST(one_thread_1000_capacity_and_size)
    TEST(producer_consumer_1Kqueue_1Mdogs)
    TEST(two_producers_1_consumer)
    TEST(one_producers_2_consumers)
    TEST(two_producers_two_consumers)
    TEST(four_producers_four_consumers)

    TEST(one_thread_priority_queue)
END_SUITE

