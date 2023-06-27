#pragma once

#include <string>  // std::string
#include <memory>  // std::shared_ptr

#include "dictionary.hpp"
#include "parser.hpp"
#include "page.hpp"
#include "coach_definitions.hpp"
namespace crawl {

//----> table to fill with : index:page  | value:shared_ptr(index:words | value:counter)
using PagesTable = coach_search::definitions::PagesTable;
//----> table to fill with : index:word | value:shared_ptr(index:pages | value:counter)
using WordsTable = coach_search::definitions::WordsTable;

using WordsCounterTable = coach_search::definitions::WordsCounterTable;
using PageCounterTable = coach_search::definitions::PageCounterTable;

using WordsCounterTablePtr = coach_search::definitions::WordsCounterTablePtr;
using PageCounterTablePtr = coach_search::definitions::PageCounterTablePtr;

class Crawl {
public:
    virtual ~Crawl() = default;
    size_t getCounterIgnore() const noexcept;

protected:
    explicit Crawl(size_t a_maxDepth, size_t a_maxPages, PagesTable& a_urls, WordsTable& a_words, std::string const & a_firstUrl);
    Crawl(Crawl const & a_other) = delete;
    Crawl& operator=(Crawl const& a_other) = delete;

    virtual void fillUrls() = 0;
    void indexWords(containers::Page const& a_page, std::vector<std::string> const& a_words);
    void downloadOne(std::string const& a_firstUrl, std::ostringstream & a_os);
    containers::Page createPage(std::string const& a_firstUrl, std::ostringstream const& a_os);
    void indexPage(std::ostringstream const& a_os, containers::Page& a_page);

    WordsCounterTablePtr createWordsCounterPtr() const;
    PageCounterTablePtr createPagesCounterPtr() const;

private:
    bool indexing(std::string const& a_word, containers::Page const& a_page);

protected:
    size_t m_a_maxDepth;
    size_t m_currentDepth;

    size_t m_maxPages;
    PagesTable& m_urlsWords;
    WordsTable& m_wordsTable;

    Parser m_parser;
    ConditionFunction m_insertUrlCondition;

    size_t m_uniqueWords;
    size_t m_countIgnore;

    std::string m_site;
    std::string m_firstUrl;

private:

};

} // namespace crawl

