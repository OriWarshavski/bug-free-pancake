#pragma once
#include <iostream>
#include <string>

#include "qury_cache.hpp"
#include "nicknames.hpp"

namespace coach_ui {

void ileagleTerm(std::string const& a_term);

void PresentPage(nickname::UrlsContainer const& a_contain, size_t a_listLength);

void printTerm(std::string const& a_term);

void askForTerm(std::string& a_term) noexcept;

void printCrawlResult(std::string const& a_url, size_t a_ignored, size_t a_pages, size_t a_words) noexcept;

void notifyNotFound() noexcept;

}// namespace coach_ui
