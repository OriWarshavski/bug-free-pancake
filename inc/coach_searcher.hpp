#pragma once

#include <memory>  // std::shared_ptr
#include <vector>

#include "configuration.hpp"
#include "crawl.hpp"
#include "dfs_crawl.hpp"
#include "searcher.hpp"
#include "coach_definitions.hpp"

namespace coach_search
{

class CoachSearcher final {
public:
    CoachSearcher();
    CoachSearcher(const CoachSearcher &a_other) = delete;
    CoachSearcher& operator=(const CoachSearcher &a_other) = delete;
    ~CoachSearcher() = default;

	void run();

private:
	void crawling(size_t a_pageToCrawl, size_t a_pagesForUrl, size_t a_numOfFirstUrls);

private:
	definitions::PagesTable m_pagesTable;
	definitions::WordsTable m_wordsTable;

	SearchConfig m_config;
	std::vector<std::shared_ptr<crawl::Crawl>> m_crawls;
	search::Searcher m_searcher;
};

} //namespace coach_search
