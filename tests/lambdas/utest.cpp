#include "mu_test.h"
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <algorithm>
#include <cassert>

template <typename T, typename U>
std::ostream& operator <<(std::ostream& os, std::pair<T, U> const& pair) 
{
	return os << '[' << pair.first << ", " << pair.second << ']';
}

template<typename C>
void print(C const& c){
    for(auto e: c){
        std::cout << e << ' ';
    }
    std::cout << '\n';
}

BEGIN_TEST(test_20_evens_from_32)
	std::vector<int> vector;
	vector.reserve(20);
	int first = 30; 
	std::generate_n(std::back_inserter(vector), 20, [init = first]() mutable {
		return init += 2;
	});
	print(vector);
	size_t size = vector.size();
	ASSERT_EQUAL(size , 20);
	int check = 30;
	for(size_t i = 0; i < size; ++i) {
		ASSERT_EQUAL(vector[i], check += 2);
	}
END_TEST


std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
						return std::tolower(c); 
					});
    return s;
}

BEGIN_TEST(map_strings_case_insensitive)
	auto CaseInsensitiveComp = [](std::string a_first, std::string a_second) {
		auto str_tolower = [](std::string& a_string) {
			std::transform(a_string.begin(), a_string.end(), a_string.begin(), [](unsigned char a_letter) {
							return std::tolower(a_letter); 
						});
			return a_string;
		};
		return str_tolower(a_first) < str_tolower(a_second);
	};
	std::map<std::string, int, decltype(CaseInsensitiveComp)> map(CaseInsensitiveComp);
	map.insert(std::make_pair("a", 1));
	map.insert(std::make_pair("b", 2));
	map.insert(std::make_pair("A", 3));
	map.insert(std::make_pair("AbC", 4));
	map.insert(std::make_pair("abc", 5));
	print(map);
	ASSERT_EQUAL(map.size(), 3);
	ASSERT_EQUAL(map["A"], 1);
	ASSERT_EQUAL(map["abc"], 4);
END_TEST

template<typename Container, typename T>
typename Container::const_iterator firstDoubleInInterval(Container const& a_container, std::pair<T, T> const& a_interval)
{
	if(a_interval.first > a_interval.second) {
		assert(a_interval.first < a_interval.second);
		return a_container.end();
	}
	//if there is no interval - simple search without lambda
	if(a_interval.first == a_interval.second) {
		return std::find(a_container.begin(), a_container.end(), a_interval.first);
	}

	return std::find_if(a_container.begin(), a_container.end(), [a_interval](T const& a_check){ 
		return a_check >= a_interval.first && a_check <= a_interval.second;
	});
}

BEGIN_TEST(list_double_interval)
	std::list<double> list = {0.45, 3.1, 2.2, 1.9, 10.12, 5.5, 6.9, -1.1, -2.0};
	using Iterator = std::list<double>::const_iterator;
	Iterator it = firstDoubleInInterval(list, std::make_pair(1.1, 2.5));
	ASSERT_EQUAL(*it, 2.2);
	Iterator result2 = firstDoubleInInterval(list, std::make_pair(-2.0, -1.1));
	ASSERT_EQUAL(*result2, -1.1);
	Iterator result3 = firstDoubleInInterval(list, std::make_pair(0.0, 1.0));
	ASSERT_EQUAL(*result3, 0.45);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])	
	TEST(test_20_evens_from_32)
	TEST(map_strings_case_insensitive)
	TEST(list_double_interval)

END_SUITE
