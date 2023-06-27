#include "mu_test.h"
#include "configuration.hpp"

#include <fstream>

using namespace coach_search;

static void createJsonLimited()
{
    // Create the JSON object
    json data;
    data["number of urls"] = 1;
    data["max pages"] = 1000;
    data["max depth"] = 3;
    data["search mode"] = "BFS";

    // Create the "pages" array
    json pages;
    json page;
    page["url"] = "https://harrypotter.fandom.com/wiki/Main_Page";
    pages.push_back(page);
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

static void createJsonUnlimited()
{
    json data;

    // Create the "pages" array
    json pages;
    json page;
    page["url"] = "https://harrypotter.fandom.com/wiki/Main_Page";
    pages.push_back(page);
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


static void createEmptyJson()
{
    std::ofstream file("search_config.json");
    if (file.is_open()) {
        file.close();
    } else {
        std::cerr << "Failed to create JSON file." << std::endl;
    }
}

BEGIN_TEST(test_no_json)
    try {
        SearchConfig conf{};
    } catch(const std::exception& ex) {
        // std::cout << ex.what() << '\n';
        ASSERT_THAT(true);
    }

END_TEST

BEGIN_TEST(test_limited)
    createJsonLimited();
    SearchConfig conf{};
    ASSERT_EQUAL(conf.urls()[0], "https://harrypotter.fandom.com/wiki/Main_Page");
    ASSERT_THAT(conf.maxPages().first == SearchConfig::SetDefinition::LIMITED);
    ASSERT_EQUAL(conf.maxPages().second, 1000);
    ASSERT_THAT(conf.maxDepth().first == SearchConfig::SetDefinition::LIMITED);
    ASSERT_EQUAL(conf.maxDepth().second, 3);
    ASSERT_THAT(conf.searchMode() == SearchConfig::SearchMode::BFS);
END_TEST

BEGIN_TEST(test_unlimited)
    createJsonUnlimited();
    SearchConfig conf{};
    ASSERT_EQUAL(conf.urls()[0], "https://harrypotter.fandom.com/wiki/Main_Page");
    ASSERT_THAT(conf.maxPages().first == SearchConfig::SetDefinition::UNLIMITED);
    ASSERT_THAT(conf.maxPages().second == MaxValue);
    ASSERT_THAT(conf.maxDepth().first == SearchConfig::SetDefinition::UNLIMITED);
    ASSERT_THAT(conf.maxDepth().second == MaxValue);
    ASSERT_THAT(conf.searchMode() == SearchConfig::SearchMode::DFS);
END_TEST

BEGIN_TEST(test_without_Url)
    createEmptyJson();
    try {
        SearchConfig conf{};
    } catch(const std::exception& ex) {
        // std::cout << ex.what() << '\n';
        ASSERT_THAT(true);
    }
END_TEST

TEST_SUITE()
    TEST(test_no_json)
    TEST(test_limited)
    TEST(test_unlimited)
    TEST(test_without_Url)

END_SUITE
