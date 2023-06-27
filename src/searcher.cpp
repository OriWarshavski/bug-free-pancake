#include <algorithm>
#include <iostream>

#include "searcher.hpp"
#include "search_word_protocol.hpp"
namespace search {

Searcher::Searcher(UrlDictionary& a_urls, WordDictionary& a_words)
: m_urls(a_urls)
, m_words(a_words)
{}

void Searcher::seek(std::string const& a_terms, nickname::UrlsContainer& a_urls)
{
    std::string normalizedTerm = words::normalizeWord(a_terms);
    UrlsContainer fromTerm;
    //if there was a previous same query
    if(m_queryCache.urls(a_terms, a_urls)){
    }
    if(a_terms[0] == '-') {
        a_urls = byNegativeTerm(a_terms);
        m_queryCache.insert(a_terms, a_urls);
    }else {
        a_urls = byPositiveTerm(normalizedTerm);
        m_queryCache.insert(normalizedTerm, fromTerm);
    }
}

void Searcher::countWordInPageToUrlsContainer(UrlsContainer& a_fromPositiveTerm, std::shared_ptr<CountWordInPage> const& a_countPerPage)
{
    auto positiveIt = a_fromPositiveTerm.begin();
    auto it = a_countPerPage->begin();
    auto const end = a_countPerPage->end();
    while(it != end){
        auto const& page = (*it).first;
        (*positiveIt) = page;
        ++it;
        ++positiveIt;
    }
}

UrlsContainer Searcher::byPositiveTerm(std::string const& a_term)
{
    if(m_words.isExist(a_term)){
        auto tempPositive = m_words.getValue(a_term);
        UrlsContainer fromPositiveTerm(tempPositive->size());
        countWordInPageToUrlsContainer(fromPositiveTerm, tempPositive);
        sortUrlsByWordApearnce(fromPositiveTerm, a_term);
        return fromPositiveTerm;
    }
    return UrlsContainer{};
}



void Searcher::sortUrlsByWordApearnce(UrlsContainer& a_container, std::string const& a_term)
{
   std::sort(a_container.begin(), a_container.end(),
        [this, &a_term](Page const& a_first, Page const& a_second)
        {
            return (m_urls.getValue(a_first))->getValue(a_term) > (m_urls.getValue(a_second))->getValue(a_term);
        });
}

void Searcher::EntireUrlTOUrlsContainer(UrlsContainer& a_fromPositiveTerm, EntireUrls const& a_entirUrls)
{
    auto positiveIt = a_fromPositiveTerm.begin();
    auto it = a_entirUrls.begin();
    auto const end = a_entirUrls.end();
    while(it != end){
        (*positiveIt) = (*it).first;
        ++it;
        ++positiveIt;
    }
}


UrlsContainer Searcher::byNegativeTerm(std::string const& a_term)
{
    EntireUrls entire = allUrls();
    auto const end = entire.end();
    UrlsContainer const& fromTerm = byPositiveTerm(a_term.substr(1));
	for(auto page : fromTerm){
		auto it = entire.find(page);
		if(it != end){
			entire.erase(it);
		}
	}
    UrlsContainer toUrlContainer(entire.size());
    EntireUrlTOUrlsContainer(toUrlContainer, entire);
    return toUrlContainer;
}

EntireUrls Searcher::allUrls()
{
    EntireUrls fromAll;
    fromAll.reserve(m_urls.size());
    auto it = m_urls.begin();
    auto const end = m_urls.end();
    while(it != end){
        fromAll.emplace((*it).first, "");
        ++it;
    }
    return fromAll;
}

} // namespace Search
