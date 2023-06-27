#include "coach_searcher.hpp"
#include "uiSearch.hpp"

namespace coach_search {

CoachSearcher::CoachSearcher()
: m_pagesTable{}
, m_wordsTable{}
, m_config{}
, m_searcher{m_pagesTable, m_wordsTable}
{
	size_t pagesToCrawl = m_config.maxPages().second;
	size_t pagesForUrl = pagesToCrawl;
	size_t NumOfFirstUrls = m_config.urls().size();

	if(m_config.maxPages().first == SearchConfig::SetDefinition::LIMITED && NumOfFirstUrls > 1) {
		pagesForUrl = pagesToCrawl / NumOfFirstUrls;
	}

	crawling(pagesToCrawl, pagesForUrl, NumOfFirstUrls);

}

void CoachSearcher::crawling(size_t a_pageToCrawl, size_t a_pagesForUrl, size_t a_numOfFirstUrls)
{
	if(m_config.searchMode() == SearchConfig::SearchMode::DFS) {
		auto itrUrls = m_config.urls().begin();
		auto endUrls = m_config.urls().end();
		while(itrUrls != endUrls) {
			auto url = *itrUrls;
			//last one - add the remain pages to crawl
			if(itrUrls + 1 == endUrls && a_numOfFirstUrls > 1) {
				a_pagesForUrl += a_pageToCrawl;
			}
			m_crawls.emplace_back(std::make_shared<crawl::DfsCrawl>(m_config.maxDepth().second, a_pagesForUrl, m_pagesTable, m_wordsTable, url));
			coach_ui::printCrawlResult(url , m_crawls.back() -> getCounterIgnore(), m_pagesTable.size(), m_wordsTable.size());
			a_pageToCrawl -= a_pagesForUrl; //remain pages
			++itrUrls;
		}
	}

	else {
		throw std::domain_error("mode search has not yet been configured");
	}
}

void CoachSearcher::run()
{
	std::string term;
	coach_ui::askForTerm(term);
	while(term != "q") {
		coach_ui::printTerm(term);
		nickname::UrlsContainer urls;

		m_searcher.seek(term, urls);
		if(urls.empty()) {
			coach_ui::notifyNotFound();
		}
		else {
			coach_ui::PresentPage(urls , m_config.listLength().second);
		}
		coach_ui::askForTerm(term);
	}
}

} //namespace coach_search
