#include "mu_test.h"
#include "dictionary.hpp"

#include <cstring>
#include <thread>
#include <vector>

using namespace containers;

BEGIN_TEST(test_map_functions)

    Dictionary<std::string, int> s;
    s.insert("Ori", 1);
    ASSERT_EQUAL(s.isExist("Ori"), true);
    ASSERT_EQUAL(s.isExist("yarden"), false);
	ASSERT_THAT(s.insert("Ori", 2) == InsertResult::DUPLICATE);
    ASSERT_EQUAL(s.getValue("Ori"), 1);
    try {
        ASSERT_EQUAL(s.getValue("Shaul"), 1);
    } catch(std::out_of_range&) {
        ASSERT_THAT(true);
    }
    s.setValue("Ori", 888);
    ASSERT_EQUAL(s.getValue("Ori"), 888);
    s.remove("Ori");
    ASSERT_EQUAL(s.size(), 0);
END_TEST

BEGIN_TEST(test_remove_returned_itr)
    Dictionary<std::string, int> s;
    s.insert("a", 1);
	s.insert("b", 1);
	s.insert("c", 1);

	for (auto i=s.begin(); i!=s.end(); ++i) {
		std::cout << (*i).first << " => " << (*i).second << "\n\n";
	}

    auto itr = s.remove("b");
	ASSERT_EQUAL(s.size(), 2);
	for (auto i=s.begin(); i!=s.end(); ++i) {
    	std::cout << (*i).first << " => " << (*i).second << '\n';
	}
	//return the next element itr
	ASSERT_EQUAL((*itr).first, "c");

	itr = s.remove("a");
	ASSERT_EQUAL(s.size(), 1);
	ASSERT_EQUAL((*itr).first, "c");

	//remove last one
	itr = s.remove("c");
	ASSERT_EQUAL(s.size(), 0);
END_TEST


BEGIN_TEST(test_iterator)
    Dictionary<std::string, std::string> s;

    for(size_t i = 0; i < 10; ++i) {
        s.insert(std::to_string(i), std::to_string(i*i));
    }

    auto iterator = s.begin();
    auto end = s.end();
    size_t i = 0;
    while(iterator != end) {
        ASSERT_EQUAL((*iterator).second, std::to_string(i*i));
        ++iterator;
        ++i;
    }

END_TEST

BEGIN_TEST(test_insert_thread)
    Dictionary<size_t, size_t> s;

    std::thread inserter([&s]() {
        for(size_t i = 0; i < 10; ++i) {
            s.insert(i, i + 1);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        for(size_t i = 10; i < 20; ++i) {
            s.insert(i, i + 1);
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQUAL(s.size(), 10);
    inserter.join();
    ASSERT_EQUAL(s.size(), 20);
END_TEST

BEGIN_TEST(test_two_inserters)
    Dictionary<size_t, size_t> s;
    auto f_insert1 = [&s]() {
        for(size_t i = 0; i < 10'000; ++i) {
            s.insert(i, i + 1);
        } };
    auto f_insert2 = [&s]() {
        for(size_t i = 10'000; i < 20'000; ++i) {
            s.insert(i, i + 1);
        } };
    std::thread t1{f_insert1};
    std::thread t2{f_insert2};
    t1.join();
    t2.join();

    ASSERT_EQUAL(s.size(), 20'000);
END_TEST

BEGIN_TEST(test_insert_remove_two_threads)
    Dictionary<int, size_t> s;
    auto f_insert = [&s]() {
        for(int i = 0; i < 20'000; ++i) {
            s.insert(i, i * i);
        } };
    auto f_remove = [&s]() {
        for(int i = 10'000; i < 20'000; ++i) {
            try {
                s.remove(i);
            } catch(...) {
                --i;
            }
        } };
    std::thread t1{f_insert};
    std::thread t2{f_remove};
    t1.join();
    t2.join();
    size_t i = 0;
    for(auto e : s) {
        ASSERT_EQUAL(e.second, i * i);
        ++i;
    }
    ASSERT_EQUAL(s.size(), 10'000);
END_TEST

BEGIN_TEST(test_insert_remove_multi_threads)
    Dictionary<size_t, size_t> s;
    auto f_insert = [&s](size_t a_start, size_t a_amount) {
        for(size_t i = a_start; i < a_amount; ++i) {
            s.insert(i, i * i);
        } };
    auto f_remove = [&s](size_t a_start, size_t a_amount) {
        for(size_t i = a_start; i < a_amount; ++i) {
            try {
                s.remove(i);
            } catch(...) {
                --i;
            }
        } };

    std::vector<std::thread> insertes;
    insertes.reserve(20);
    //500 insert threads, every thread inserts 1'000 items ---> 10'000
    for(size_t i = 0, start = 0; i < 10; ++i, start += 1'000){
        insertes.emplace_back(f_insert, start, start + 1'000);
    }
    for(auto& e : insertes) {
        e.join();
    }
    std::vector<std::thread> removers;
    //10 removers threads, every thread removes 100 items ---> 1'000
    for(size_t i = 0, start = 0; i < 10; ++i, start += 100){
        removers.emplace_back(f_remove, start, start + 100);
    }

    for(auto& e : removers) {
        e.join();
    }

    size_t i = 1'000;
        for(auto e : s) {
            ASSERT_EQUAL(e.second, i * i);
            ++i;
        }
    ASSERT_EQUAL(s.size(), 9'000);
END_TEST

TEST_SUITE()
    IGNORE_TEST(test_map_functions)
    IGNORE_TEST(test_iterator)
    IGNORE_TEST(test_insert_thread)
    IGNORE_TEST(test_two_inserters)
    IGNORE_TEST(test_insert_remove_two_threads)
    IGNORE_TEST(test_insert_remove_multi_threads)
	IGNORE_TEST(test_remove_returned_itr)
END_SUITE
