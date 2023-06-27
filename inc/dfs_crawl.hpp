# pragma once

#include <stack>

#include "crawl.hpp"
#include "page.hpp"

namespace crawl {

using ConditionFunction = std::function<bool(std::string const &)>;

class DfsCrawl : public Crawl {
public:

    explicit DfsCrawl(size_t a_maxDepth, size_t a_maxPages, PagesTable& a_urls, WordsTable& a_words , std::string a_firstUrl);
    DfsCrawl(DfsCrawl const & a_other) = delete;
    DfsCrawl& operator=(DfsCrawl const& a_other) = delete;
    ~DfsCrawl() = default;

    

private:    

    void fillUrls() override; 
    void implaceUrlsFromCurrentPage(containers::Page & a_currentPage, std::ostringstream const& a_os, std::stack<std::string>& a_urlList);
};

} // namespace crawl
