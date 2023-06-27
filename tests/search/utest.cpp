#include "mu_test.h"
#include <vector>
#include <memory>
#include <string>
#include "qury_cache.hpp"
#include "searcher.hpp"
#include "page.hpp"
#include "nicknames.hpp"



BEGIN_TEST(insert_compare_test)
	using namespace search;

	QuryCache catches;
	UrlsContainer urls{Page("abc", "ami"), Page("def", "mat"), Page("hig", "ori")};
	std::string terms{"abc"};
	catches.insert(terms,urls);
	UrlsContainer res;
	ASSERT_EQUAL(catches.urls(terms, res), true);

END_TEST

BEGIN_TEST(get_UrlsContainer_test)
	using namespace search;

	QuryCache catches;
	UrlsContainer urls{Page("abc", "ami"), Page("def", "mat"), Page("hig", "ori")};
	std::string terms{"abc"};
	catches.insert(terms,urls);
	UrlsContainer res;
	ASSERT_EQUAL(catches.urls(terms,res), true);
	ASSERT_THAT(res == urls);

END_TEST

BEGIN_TEST(get_UrlsContainer_test_urls_false)
	using namespace search;

	QuryCache cache;
	std::string terms{"abc"};
	
	UrlsContainer res;
	ASSERT_EQUAL(cache.urls(terms,res), false);

END_TEST

	using WordCount = containers::Dictionary<std::string, size_t>;
	using namespace search;
	using namespace containers;
	using namespace nickname;
BEGIN_TEST(test_serch_one_term_positive_hi_term)
	

	
	std::shared_ptr<WordCount> words = std::make_shared<WordCount>();
	(*words).insert("hi", 10);
	(*words).insert("stay", 2);
	(*words).insert("bay", 2);

	std::shared_ptr<WordCount> words1 = std::make_shared<WordCount>();
	(*words1).insert("hi", 5);
	(*words1).insert("sTay", 6);

	UrlDictionary byUrl;
	byUrl.insert(Page("www.google.com", "goooogle"), words);
	byUrl.insert(Page("www.walla.com", "waaaalllllaaaaa"), words1);

	std::shared_ptr<CountWordInPage> wordPerPageHi = std::make_shared<CountWordInPage>();
	wordPerPageHi->insert(Page("www.google.com", "goooogle"), 10);
	wordPerPageHi->insert(Page("www.walla.com", "waaaalllllaaaaa"), 5);
	WordDictionary byWord;
	byWord.insert("hi", wordPerPageHi);
	std::shared_ptr<CountWordInPage> wordPerPageBuy = std::make_shared<CountWordInPage>();
	wordPerPageBuy->insert(Page("www.google.com", "goooogle"), 2);
	byWord.insert("bay", wordPerPageBuy);
	std::shared_ptr<CountWordInPage> wordPerPageStay = std::make_shared<CountWordInPage>();
	wordPerPageStay->insert(Page("www.google.com", "goooogle"), 2);
	wordPerPageStay->insert(Page("www.walla.com", "waaaalllllaaaaa"), 6);
	byWord.insert("stay", wordPerPageStay);

	Searcher search(byUrl, byWord); 

	std::string terms{"hi"};

	search.seek(terms);
	ASSERT_PASS();

END_TEST

BEGIN_TEST(test_serch_one_term_positive_stay_term)
	
	std::shared_ptr<WordCount> words = std::make_shared<WordCount>();
	(*words).insert("hi", 10);
	(*words).insert("stay", 2);
	(*words).insert("bay", 2);

	std::shared_ptr<WordCount> words1 = std::make_shared<WordCount>();
	(*words1).insert("hi", 5);
	(*words1).insert("stay", 6);

	UrlDictionary byUrl;
	byUrl.insert(Page("www.google.com", "goooogle"), words);
	byUrl.insert(Page("www.walla.com", "waaaalllllaaaaa"), words1);

	std::shared_ptr<CountWordInPage> wordPerPageHi = std::make_shared<CountWordInPage>();
	wordPerPageHi->insert(Page("www.google.com", "goooogle"), 10);
	wordPerPageHi->insert(Page("www.walla.com", "waaaalllllaaaaa"), 5);
	WordDictionary byWord;
	byWord.insert("hi", wordPerPageHi);
	std::shared_ptr<CountWordInPage> wordPerPageBuy = std::make_shared<CountWordInPage>();
	wordPerPageBuy->insert(Page("www.google.com", "goooogle"), 2);
	byWord.insert("bay", wordPerPageBuy);
	std::shared_ptr<CountWordInPage> wordPerPageStay = std::make_shared<CountWordInPage>();
	wordPerPageStay->insert(Page("www.google.com", "goooogle"), 2);
	wordPerPageStay->insert(Page("www.walla.com", "waaaalllllaaaaa"), 6);
	byWord.insert("stay", wordPerPageStay);

	Searcher search(byUrl, byWord); 

	std::string terms{"stay"};

	search.seek(terms);
	ASSERT_PASS();

END_TEST

BEGIN_TEST(test_serch_one_term_negative_bay_term)
	
	std::shared_ptr<WordCount> words = std::make_shared<WordCount>();
	(*words).insert("hi", 10);
	(*words).insert("stay", 2);
	(*words).insert("bay", 2);

	std::shared_ptr<WordCount> words1 = std::make_shared<WordCount>();
	(*words1).insert("hi", 5);
	(*words1).insert("stay", 6);

	UrlDictionary byUrl;
	byUrl.insert(Page("www.google.com", "goooogle"), words);
	byUrl.insert(Page("www.walla.com", "waaaalllllaaaaa"), words1);

	std::shared_ptr<CountWordInPage> wordPerPageHi = std::make_shared<CountWordInPage>();
	wordPerPageHi->insert(Page("www.google.com", "goooogle"), 10);
	wordPerPageHi->insert(Page("www.walla.com", "waaaalllllaaaaa"), 5);
	WordDictionary byWord;
	byWord.insert("hi", wordPerPageHi);
	std::shared_ptr<CountWordInPage> wordPerPageBuy = std::make_shared<CountWordInPage>();
	wordPerPageBuy->insert(Page("www.google.com", "goooogle"), 2);
	byWord.insert("bay", wordPerPageBuy);
	std::shared_ptr<CountWordInPage> wordPerPageStay = std::make_shared<CountWordInPage>();
	wordPerPageStay->insert(Page("www.google.com", "goooogle"), 2);
	wordPerPageStay->insert(Page("www.walla.com", "waaaalllllaaaaa"), 6);
	byWord.insert("stay", wordPerPageStay);

	Searcher search(byUrl, byWord); 

	std::string terms{"-bay"};

	search.seek(terms);
	ASSERT_PASS();

END_TEST

BEGIN_TEST(test_serch_one_term_not_exist)
	
	std::shared_ptr<WordCount> words = std::make_shared<WordCount>();
	(*words).insert("hi", 10);
	(*words).insert("stay", 2);
	(*words).insert("bay", 2);

	std::shared_ptr<WordCount> words1 = std::make_shared<WordCount>();
	(*words1).insert("hi", 5);
	(*words1).insert("stay", 6);

	UrlDictionary byUrl;
	byUrl.insert(Page("www.google.com", "goooogle"), words);
	byUrl.insert(Page("www.walla.com", "waaaalllllaaaaa"), words1);

	std::shared_ptr<CountWordInPage> wordPerPageHi = std::make_shared<CountWordInPage>();
	wordPerPageHi->insert(Page("www.google.com", "goooogle"), 10);
	wordPerPageHi->insert(Page("www.walla.com", "waaaalllllaaaaa"), 5);
	WordDictionary byWord;
	byWord.insert("hi", wordPerPageHi);
	std::shared_ptr<CountWordInPage> wordPerPageBuy = std::make_shared<CountWordInPage>();
	wordPerPageBuy->insert(Page("www.google.com", "goooogle"), 2);
	byWord.insert("bay", wordPerPageBuy);
	std::shared_ptr<CountWordInPage> wordPerPageStay = std::make_shared<CountWordInPage>();
	wordPerPageStay->insert(Page("www.google.com", "goooogle"), 2);
	wordPerPageStay->insert(Page("www.walla.com", "waaaalllllaaaaa"), 6);
	byWord.insert("stay", wordPerPageStay);

	Searcher search(byUrl, byWord); 

	std::string terms{"amitai"};

	search.seek(terms);
	ASSERT_PASS();

END_TEST


 TEST_SUITE(search tests)

	TEST(insert_compare_test)
	TEST(get_UrlsContainer_test_urls_false)
	TEST(get_UrlsContainer_test)
 	TEST(test_serch_one_term_positive_hi_term)
	TEST(test_serch_one_term_positive_stay_term)
	TEST(test_serch_one_term_negative_bay_term)
	TEST(test_serch_one_term_not_exist)

 END_SUITE
