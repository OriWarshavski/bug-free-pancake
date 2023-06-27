#include <vector>
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "dfs_crawl.hpp"

namespace crawl {

DfsCrawl::DfsCrawl(size_t a_maxDepth, size_t a_maxPages, PagesTable& a_urls, WordsTable& a_words, std::string a_firstUrl)
: Crawl(a_maxDepth, a_maxPages, a_urls, a_words, a_firstUrl)
{
    fillUrls();
}

void DfsCrawl::implaceUrlsFromCurrentPage(containers::Page & a_currentPage, std::ostringstream const& a_os, std::stack<std::string>& a_urlList)
{
    std::vector<std::string> links;
    links.reserve(1000);
    m_parser.links(a_currentPage.url() ,a_os, links, m_insertUrlCondition);
    auto begin = links.begin();
    auto end = links.end();
    --end;
    while(end >= begin) {
        a_urlList.push(*end);
        // a_currentPage.insertPageLinks(*end);
        --end;
    }
}

void DfsCrawl::fillUrls()
{
    std::stack<std::string> urlList;
    std::ostringstream html;
    downloadOne(m_firstUrl, html);
    auto page = createPage(m_firstUrl, html);

    indexPage(html, page);
    implaceUrlsFromCurrentPage(page, html, urlList);

    ++m_currentDepth;
    while(!urlList.empty()) {
        if(m_urlsWords.size() >= m_maxPages) {
            break;
        }
        std::string link = urlList.top();
        urlList.pop();
        html.str("");
        html.clear();
        assert(html.str().empty());
        downloadOne(link, html);
        if(html.str().empty()) {
            continue;
        }
        auto page = createPage(link, html);
        if(!m_urlsWords.isExist(page)) {
            indexPage(html, page);
            if(m_currentDepth < m_a_maxDepth) {
                implaceUrlsFromCurrentPage(page, html, urlList);
                ++m_currentDepth;
            }
        }
    }
} 


} // namespace crawl