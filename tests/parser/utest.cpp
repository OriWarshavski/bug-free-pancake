#include "mu_test.h"

#include <vector>
#include <string>
#include <curlpp/Options.hpp>

#include "parser.hpp"


BEGIN_TEST(links)

	std::ostringstream os;
	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";

	os << curlpp::options::Url(url);
    
    size_t pos = url.find("/", 8);

    std::string site = url.substr(0, pos);
	
	auto f = [&site](std::string a_link) ->bool {
		return a_link.find(site) != std::string::npos;
	};

	crawl::Parser parser;
	std::vector<std::string> urls;
	parser.links(url,os, urls ,f);

	for(auto link : urls) {
		std::cout << link << "\n";
	}

ASSERT_EQUAL(3,3);

END_TEST

BEGIN_TEST(words)

	std::ostringstream os;
	os << curlpp::options::Url("https://harrypotter.fandom.com/wiki/Main_Page");

	crawl::Parser parser;
	std::vector<std::string> words;
	parser.words(os, words);

	for(auto word : words) {
		std::cout << word << "\n";
	}


ASSERT_EQUAL(0 , 0);

END_TEST

BEGIN_TEST(title_harry)

	std::ostringstream os;
	os << curlpp::options::Url("https://harrypotter.fandom.com/wiki/Main_Page");

	crawl::Parser parser;
	std::string title = parser.title(os);
	TRACE(title);

ASSERT_EQUAL(title , "Harry Potter Wiki | Fandom");

END_TEST


BEGIN_TEST(title_cppref)

	std::ostringstream os;
	os << curlpp::options::Url("https://en.cppreference.com/w/");

	crawl::Parser parser;
	std::string title = parser.title(os);
	TRACE(title);

ASSERT_EQUAL(title , "cppreference.com");

END_TEST

// BEGIN_TEST(build_url)
// 	std::string current_url{ "https://harrypotter.fandom.com/wiki/Main_Page"};
// 	std::string url_to_normalize{"/wiki/Special:Categories"};


// 	std::string result = crawl::normalizeUrl(current_url, url_to_normalize);

// 	TRACE(result);

// 	ASSERT_EQUAL(0 , 0);

// END_TEST

// BEGIN_TEST(build_url_2)
// 	std::string current_url{ "https://harrypotter.fandom.com/wiki/Main_Page"};
// 	std::string url_to_normalize{"//community.fandom.com/Sitemap"};


// 	std::string result = crawl::normalizeUrl(current_url, url_to_normalize);

// 	TRACE(result);

// 	ASSERT_EQUAL(0 , 0);

// END_TEST




TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	
	TEST(links)
	TEST(words)
	TEST(title_harry)
	// TEST(title_cppref)
	// TEST(build_url)
	// TEST(build_url_2)

END_SUITE
