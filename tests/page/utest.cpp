#include "mu_test.h"

#include <string>
#include <climits>
#include <utility>
#include <map>
#include <unordered_map>

#include "page.hpp"
#include "dictionary.hpp"

using namespace containers;

BEGIN_TEST(insert_page_to_map_by_url_key)
	std::map<Page, std::string> map;
	map.insert(std::make_pair(Page("a", "amiti"), "bbb"));
	map.insert(std::make_pair(Page("b", "mat"), "aaa"));
	ASSERT_EQUAL(map.size(), 2);
END_TEST

BEGIN_TEST(insert_page_to_map_by_url_same_key)
	std::map<Page, std::string> map;
	map.insert(std::make_pair(Page("b", "amiti"), "bbb"));
	map.insert(std::make_pair(Page("b", "mat"), "aaa"));
	ASSERT_EQUAL(map.size(), 1);
END_TEST


BEGIN_TEST(insert_page_to_dictionary_by_url_key)
using namespace containers;
	Dictionary<Page, std::string> map;
	map.insert(Page("a", "amiti"), "bbb");
	map.insert(Page("b", "mat"), "aaa");
	ASSERT_EQUAL(map.size(), 2);
END_TEST

BEGIN_TEST(insert_page_to_dictionary_by_url_same_key)
using namespace containers;
	Dictionary<Page, std::string> map;
	map.insert(Page("a", "amiti"), "bbb");
	map.insert(Page("a", "mat"), "aaa");
	ASSERT_EQUAL(map.size(), 1);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(insert_page_to_map_by_url_key)
	TEST(insert_page_to_map_by_url_same_key)
	TEST(insert_page_to_dictionary_by_url_key)
	TEST(insert_page_to_dictionary_by_url_same_key)
END_SUITE
