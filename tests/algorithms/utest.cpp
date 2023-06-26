#include "mu_test.h"
#include "algorithms.hpp"
#include "generic_utils.hpp"
#include <vector>
#include <list>
#include <forward_list>
#include <array>

using namespace advcpp;

BEGIN_TEST(test_reverse_vec_int)
	std::vector<int> vec {1, 2, 3, 4, 5, 6};
	advcpp::reverse(vec.begin(), vec.end());
	for (int x : vec) {
		std::cout << x <<",";
	}
	ASSERT_EQUAL(vec[0], 6);
	ASSERT_EQUAL(vec[1], 5);
	ASSERT_EQUAL(vec[2], 4);
	ASSERT_EQUAL(vec[3], 3);
	ASSERT_EQUAL(vec[4], 2);
	ASSERT_EQUAL(vec[5], 1);
END_TEST

BEGIN_TEST(test_reverse_list_string)
	std::list<std::string> str {"hello", "world"};
	advcpp::reverse(str.rbegin(), str.rend());
	TRACE (str);
	ASSERT_EQUAL(str.front(), "world");
	ASSERT_EQUAL(str.back(), "hello");
END_TEST

BEGIN_TEST(test_reverse_array_int)
	std::array<int, 3> array = {1,2,3};
	int simpleArr[] = {0, 10, 20, 30, 40, 50};
	advcpp::reverse(array.begin(), array.end());
	advcpp::reverse(&simpleArr[0], &simpleArr[6]);
	TRACE (array);
	for (int x : simpleArr) {
		std::cout << x << ",";
	}
	ASSERT_EQUAL(array[0], 3);
	ASSERT_EQUAL(array[2], 1);
	ASSERT_EQUAL(simpleArr[0], 50);
	ASSERT_EQUAL(simpleArr[5], 0);
END_TEST

BEGIN_TEST(test_reverse_array_string)
	std::array<std::string, 3> array = {"Hi", "what's", "up"};
	advcpp::reverse(array.begin(), array.end());
	TRACE (array);
	ASSERT_EQUAL(array[0], "up");
	ASSERT_EQUAL(array[2], "Hi");
END_TEST

//This test causes compilation problem - PASS
// BEGIN_TEST(test_reverse_forword_list)
// 	std::forward_list<int> list = {0 , 1, 3, 4};
// 	advcpp::reverse(list.begin(), list.end());
// END_TEST

int integereAddition(int const a_x, int const a_y) {
    return a_x + a_y;
}

BEGIN_TEST(reduce_vector_int_addition)
	std::vector<int> vec {1, 2, 3, 4, 5, 6};
	int result = advcpp::reduce(vec.begin(), vec.end(), 0, integereAddition);
	ASSERT_EQUAL(result, 21);
END_TEST

int integereMultiply(int const a_x, int const a_y) {
    return a_x * a_y;
}

BEGIN_TEST(reduce_list_int_multiply)
	std::list<int> list {1, 2, 3, 4, 5, 6};
	int result = advcpp::reduce(list.begin(), list.end(), 1, integereMultiply);
	ASSERT_EQUAL(result, 720);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])	
	TEST(test_reverse_vec_int)
	TEST(test_reverse_list_string)
	TEST(test_reverse_array_int)
	TEST(test_reverse_array_string)
	//TEST(test_reverse_forword_list)
	TEST(reduce_vector_int_addition)
	TEST(reduce_list_int_multiply)
END_SUITE