#include "mu_test.h"
#include <vector>
#include <map>
#include <list>
#include "generic_utils.hpp"


using namespace advcpp;

BEGIN_TEST(print_vector_int)
	std::vector<int> vec{10, 14, 4, 5, 7, 8};
	std::cout << vec;
	ASSERT_THAT(true);
END_TEST

BEGIN_TEST(print_vector_char)
	std::vector<char> vec{'a', 'b', 'c', 'd'};
	std::cout << vec;
	ASSERT_THAT(true);
END_TEST

BEGIN_TEST(print_vector_string)
	std::vector<std::string> vec{"hello", "world"};
	std::cout << vec;
	ASSERT_THAT(true);
END_TEST

BEGIN_TEST(print_hash)
    std::map<std::string, int> elements = {
        {"Ferrum", 26},
        {"Aurum", 79}
    };
	std::cout << elements;
	ASSERT_THAT(true);
END_TEST

BEGIN_TEST(min_vactor_int)
	std::vector<int> vec{10, 14, 4, 5, 7, 8};		
	int min = Minimal(vec.begin(), vec.end());
	ASSERT_EQUAL(min, 4);
END_TEST

BEGIN_TEST(min_vactor_string)
	std::vector<std::string> vec{"Someone", "told", "me", "long", "ago", "There's"};
	std::string min = Minimal(vec.begin(), vec.end());
	ASSERT_EQUAL(min, "Someone");
END_TEST

BEGIN_TEST(min_list_string)
	std::list<std::string> lst = {"Someone", "told", "me", "long", "ago", "There's"};		
	std::string min = Minimal(lst.begin(), lst.end());
	ASSERT_EQUAL(min, "Someone");
END_TEST

BEGIN_TEST(min_list_double)
	std::list<double> lst = {2.3, 4.1, 2.1, 3, 123};		
	double min = Minimal(lst.begin(), lst.end());
	ASSERT_EQUAL(min, 2.1);
END_TEST

BEGIN_TEST(sum_vector_int)
	std::vector<int> vec{1, 2, 3, 4, 5, 6};	
	ASSERT_EQUAL(Sum(vec.begin(), vec.end()), 21);
END_TEST

BEGIN_TEST(sum_vector_string)
	std::vector<std::string> vec{"a", "b", "c"};
	ASSERT_EQUAL(Sum(vec.begin(), vec.end()), "abc");
END_TEST

BEGIN_TEST(first_unique_vector_int)
	std::vector<int> vec{1, 2, 1, 4, 2, 6};	
	std::vector<int>::const_iterator unique = FirstUnique(vec.begin(), vec.end());
	ASSERT_EQUAL(*unique, 4);
END_TEST

BEGIN_TEST(first_unique_list_string)
	std::list<std::string> lst = {"Someone", "told", "Someone", "long", "ago", "told"};		
	std::list<std::string>::const_iterator unique = FirstUnique(lst.begin(), lst.end());
	ASSERT_EQUAL(*unique, "long");
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])	
	TEST(print_vector_int)
	TEST(print_vector_char)
	TEST(print_vector_string)
	TEST(print_hash)
	TEST(min_vactor_int)
	TEST(min_vactor_string)
	TEST(min_list_string)
	TEST(min_list_double)
	TEST(sum_vector_int)
	TEST(sum_vector_string)
	TEST(first_unique_vector_int)
	TEST(first_unique_list_string)
END_SUITE