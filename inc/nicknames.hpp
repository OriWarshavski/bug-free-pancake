#pragma once
#include <memory>

#include "dictionary.hpp"
#include "page.hpp"


namespace nickname {

using Page = containers::Page;
using CountWordInPage = containers::Dictionary<Page, size_t>;
using UrlsContainer = std::vector<containers::Page>;
// using UrlDictionary = containers::Dictionary<Page, std::shared_ptr<containers::Dictionary<std::string, size_t>>>;
// using WordDictionary = containers::Dictionary<std::string, std::shared_ptr<CountWordInPage>>;
using EntireUrls = std::unordered_map<Page, std::string>;

}

