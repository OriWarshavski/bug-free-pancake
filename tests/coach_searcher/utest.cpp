#include "mu_test.h"
#include "coach_searcher.hpp"

#include <fstream>

using namespace coach_search;

static void createJson3Urls(std::string const& a_mode)
{
    // Create the JSON object
    json data;
    data["number of urls"] = 2;
    data["max pages"] = 10;
    data["max depth"] = 3;
    data["search mode"] = a_mode;

    // Create the "pages" array
    json pages;
    json page1;
	json page2;
	json page3;
    page1["url"] = "https://harrypotter.fandom.com/wiki/Main_Page";
	page2["url"] = "https://cplusplus.com";
	page3["url"] = "https://google.com";
    pages.push_back(page1);
	pages.push_back(page2);
	pages.push_back(page3);
    data["pages"] = pages;

    // Write the JSON object to a file
    std::ofstream file("search_config.json");
    if (file.is_open()) {
        file << data.dump(4);  // Indentation with 4 spaces
        file.close();
    } else {
        std::cerr << "Failed to create JSON file." << std::endl;
    }
}

static void createJsonLimitedList(std::string const& a_mode)
{
    // Create the JSON object
    json data;
    data["number of urls"] = 3;
    data["max pages"] = 10;
    data["max depth"] = 3;
    data["search mode"] = a_mode;
	data["list length"] = 3;

    // Create the "pages" array
    json pages;
    json page1;

    page1["url"] = "https://harrypotter.fandom.com/wiki/Main_Page";

    pages.push_back(page1);

    data["pages"] = pages;

    // Write the JSON object to a file
    std::ofstream file("search_config.json");
    if (file.is_open()) {
        file << data.dump(4);  // Indentation with 4 spaces
        file.close();
    } else {
        std::cerr << "Failed to create JSON file." << std::endl;
    }
}

BEGIN_TEST(test_dfs)
	createJson3Urls("DFS");
    CoachSearcher coach{};
	coach.run();
	ASSERT_PASS();
END_TEST

BEGIN_TEST(test_dfs_limited_list)
	createJsonLimitedList("DFS");
    CoachSearcher coach{};
	coach.run();
	ASSERT_PASS();
END_TEST

BEGIN_TEST(test_bfs)
	createJson3Urls("BFS");
	try {
		CoachSearcher coach{};

	} catch (std::domain_error& x) {
		std::cout << x.what() << '\n';
		ASSERT_PASS();

	}
END_TEST

BEGIN_TEST(test_wrong_mode)
	createJson3Urls("AAA");
	try {
		CoachSearcher coach{};

	} catch (std::domain_error& x) {
		std::cout << x.what() << '\n';
		ASSERT_THAT(false);

	}
	ASSERT_PASS();
END_TEST

TEST_SUITE()
    TEST(test_dfs)
	TEST(test_bfs)
	TEST(test_wrong_mode)
	TEST(test_dfs_limited_list)

END_SUITE
