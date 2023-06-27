#include "mu_test.h"

#include <vector>
#include <string>
#include <curlpp/Options.hpp>
#include <fstream>
#include <chrono>

#include "dictionary.hpp"
#include "dfs_crawl.hpp"
#include "parser.hpp"
#include "page.hpp"

BEGIN_TEST(crawltt)

	crawl::PagesTable pageTable{}; 
	crawl::WordsTable wordsTable{};

	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";


	crawl::DfsCrawl dfs(5, 20, pageTable, wordsTable, url);

	for(auto link : pageTable) {
		std::cout << link.first.url() << "  --"  << link.first.title() << "\n";
	}

	size_t count = dfs.getCounterIgnore();
	std::cout << "count ignore: " << count << "\n";
	std::cout << "num unique page: " << pageTable.size() << "\n";
	std::cout << "num add words: " << wordsTable.size() << "\n";


	ASSERT_EQUAL(pageTable.size(), 20);

END_TEST

BEGIN_TEST(crawl_url_words)

	crawl::PagesTable pageTable{}; 
	crawl::WordsTable wordsTable{};

	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";


	crawl::DfsCrawl dfs(2, 20, pageTable, wordsTable, url);

	// dfs.fillUrls();

	for(auto link : pageTable) {
		std::cout << link.first.url() << "  --"  << link.first.title() << "\n";
		std::cout << "number unique words: " << link.second->size() << "\n";
		auto begin = link.second->begin();
		auto end = link.second->end();
		while(begin != end) {
			std::cout << (*begin).first << " --- " << (*begin).second << "\n";
			++begin;
		}
	}

	size_t count = dfs.getCounterIgnore();
	std::cout << "count ignore: " << count << "\n";
	std::cout << "num unique page: " << pageTable.size() << "\n";
	std::cout << "num add words: " << wordsTable.size() << "\n";
	TRACE(count);

	ASSERT_EQUAL(pageTable.size(), 20);

END_TEST

// BEGIN_TEST(fill_words_one_url)

// 	// std::ostringstream os;
// 	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";
// 	size_t pos = url.find("/", 8);
//     std::string site = url.substr(0, pos);
// 	auto f = [&site](std::string const& a_link)->bool {
// 		return a_link.find(site) != std::string::npos;
// 	};
// 	crawl::PageCounterTable urlsTable{};
// 	crawl::PageCounterTablePtr wordsTable; 			//----> table to fill with url index and words+counter as values
// 	crawl::DfsCrawl dfs(2, 20, urlsTable, f);

// 	//-----> insert one url
// 	urlsTable.insert(url, dfs.createTablePtr());

// 	crawl::Table wordsTable{}; 	//----> table to fill with words index and urls+counter as values
// 	dfs.indexWords(wordsTable);

// 	auto itr = (*(urlsTable.getValue(url))).begin();
// 	auto end = (*(urlsTable.getValue(url))).end();
// 	size_t countWords = 0;	//with repetition
// 	while(itr != end) {
// 		std::cout << (*itr).first << " counter: " << (*itr).second << '\n';
// 		countWords += (*itr).second;
// 		++itr;
// 	}

// 	//get url curl
// 	std::ostringstream os;
// 	os << curlpp::options::Url(url);
// 	//extract works from curl
// 	crawl::Parser parser;
// 	std::vector<std::string> words = parser.words(os);

// 	ASSERT_EQUAL(countWords, words.size());

// END_TEST

// static void exportUrlsToFile(crawl::Table const& a_table) 
// {
// 	std::ofstream file ("url_index.txt");
// 	auto itrUrls = a_table.begin();
// 	auto endUrls = a_table.end();
// 	// size_t countWordsTotal = 0;
// 	while(itrUrls != endUrls) {
// 		std::string url = (*itrUrls).first;
// 		auto itrWords = (*(a_table.getValue(url))).begin();
// 		auto end = (*(a_table.getValue(url))).end();
// 		file << "\nurl: " << url << '\n';
// 		while(itrWords != end) {
// 			file << (*itrWords).first << " counter: " << (*itrWords).second << '\n';
// 			// countWordsTotal += (*itrWords).second;

// 			++itrWords;
// 		}
// 		++itrUrls;
// 	}
// }

// static void exportWordsToFile(crawl::Table const& a_words) 
// {
// 	std::ofstream file ("words_index.txt");
// 	auto itrWords = a_words.begin();
// 	auto endUWords = a_words.end();
// 	// size_t countWordsTotal = 0;
// 	while(itrWords != endUWords) {
// 		std::string word = (*itrWords).first;
// 		auto itrUrls = (*(a_words.getValue(word))).begin();
// 		auto end = (*(a_words.getValue(word))).end();
// 		file << "\nword: " << word << '\n';
// 		while(itrUrls != end) {
// 			file << (*itrUrls).first << " counter: " << (*itrUrls).second << '\n';
// 			// countWordsTotal += (*itrWords).second;

// 			++itrUrls;
// 		}
// 		++itrWords;
// 	}
// }

// BEGIN_TEST(fill_words_all_dfs_urls)
// 	crawl::Table table{};
// 	std::ostringstream os;
// 	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";
// 	size_t pos = url.find("/", 8);
//     std::string site = url.substr(0, pos);
// 	auto f = [&site](std::string const& a_link)->bool {
// 		return a_link.find(site) != std::string::npos;
// 	};
// 	crawl::DfsCrawl dfs(2, 20, table, f);
// 	//-----> fill with all urls
// 	dfs.fillUrls(url);
// 	std::cout << "--->fillUrls done\n";

// 	crawl::Table wordsTable{}; 	//----> table to fill with words index and urls+counter as values

// 	size_t count = dfs.indexWords(wordsTable);
// 	std::cout << "\n--->fill words done\n";

// 	exportUrlsToFile(table);
// 	exportWordsToFile(wordsTable);

// 	ASSERT_EQUAL(count, 8082); //from "words_index" file

// END_TEST

TEST_SUITE()
	TEST(crawltt)
	//TEST(crawl_url_words)
	// TEST(fill_words_one_url)
	// TEST(fill_words_all_dfs_urls)

END_SUITE
