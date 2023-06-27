#pragma once
#include <string>
#include <map>
#include <mutex>
#include <utility>
#include <memory>

#include "qury_cache.hpp"
#include "dictionary.hpp"
#include "page.hpp"
#include "nicknames.hpp"
#include "coach_definitions.hpp"
namespace search{

using namespace nickname;

//----> table to fill with : index:page  | value:shared_ptr(index:words | value:counter)
using UrlDictionary = coach_search::definitions::PagesTable;
//----> table to fill with : index:word | value:shared_ptr(index:pages | value:counter)
using WordDictionary = coach_search::definitions::WordsTable;

class Searcher final{
public:
    explicit Searcher(UrlDictionary& a_urls, WordDictionary& a_words);
    Searcher(Searcher const& a_other) = delete;
    Searcher& operator=(Searcher const& a_other) = delete;
    ~Searcher() = default;
    void seek(std::string const& a_terms, nickname::UrlsContainer& a_urls);

private:
    UrlsContainer byPositiveTerm(std::string const& a_term);
    UrlsContainer byNegativeTerm(std::string const& a_term);
    EntireUrls allUrls();
    void sortUrlsByWordApearnce(UrlsContainer& a_container, std::string const& a_term);
    void countWordInPageToUrlsContainer(UrlsContainer& a_fromPositiveTerm, std::shared_ptr<CountWordInPage> const& a_countPerPage);
    void EntireUrlTOUrlsContainer(UrlsContainer& a_fromPositiveTerm, EntireUrls const& a_entirUrls) ;

private:
    UrlDictionary& m_urls;
    WordDictionary& m_words;
    QuryCache m_queryCache;
    std::mutex m_mtx;
};


} // namespace search
