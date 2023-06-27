#include <curlpp/Options.hpp> //curlpp::options::Url
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <boost/regex.hpp>

#include "crawl.hpp"

namespace crawl {

    Crawl::Crawl(size_t a_maxDepth, size_t a_maxPages, PagesTable& a_urls, WordsTable& a_words, std::string const& a_firstUrl)
    : m_a_maxDepth(a_maxDepth)
    , m_currentDepth(0)
    , m_maxPages(a_maxPages)
    , m_urlsWords(a_urls)
    , m_wordsTable(a_words)
    , m_uniqueWords(0)
    , m_countIgnore(0)
    , m_site(m_parser.extractSite(a_firstUrl))
    , m_firstUrl(a_firstUrl)
    {
        auto f = [this](std::string const& a_link)->bool {
		    if(a_link.find(m_site) == std::string::npos) {
			    ++m_countIgnore;
                return false;
		    }
		    return true;
	    };
        m_insertUrlCondition = f;
    }

WordsCounterTablePtr Crawl::createWordsCounterPtr() const
{
    return std::make_shared<WordsCounterTable>();
}

PageCounterTablePtr Crawl::createPagesCounterPtr() const
{
    return std::make_shared<PageCounterTable>();
}

//returns if new word was indexes
bool Crawl::indexing(std::string const& a_word, containers::Page const& a_page)
{
    containers::InsertResult result = m_wordsTable.insert(a_word, createPagesCounterPtr());
    //insert exists word to words table --> increase url counter
    if(result == containers::InsertResult::DUPLICATE) {
        ++(*(m_wordsTable[a_word]))[a_page];
        return false;
    }
    //insert new word to words table
    m_wordsTable[a_word] -> insert(a_page, 1);
    return true;
}

void Crawl::indexWords(containers::Page const& a_page, std::vector<std::string> const& a_words)
{
        //fill table with words and counters
        auto itrWords = a_words.begin();
        auto end = a_words.end();
        while(itrWords != end) {
            std::string word = *itrWords;
            containers::InsertResult result = m_urlsWords[a_page] -> insert(word, 1);
            //increase counter in case of duplicate
            if(result == containers::InsertResult::DUPLICATE) {
                ++(*(m_urlsWords[a_page]))[word];
            }

            if(indexing(word, a_page)) {
                m_uniqueWords += 1;
            }
            ++itrWords;
        }
}

size_t Crawl::getCounterIgnore() const noexcept
{
    return m_countIgnore;
}

void Crawl::downloadOne(std::string const& a_firstUrl ,std::ostringstream & a_os)
{
    // curlpp::Easy myRequest;
    // myRequest.setOpt<curlpp::options::Url>(a_firstUrl);
  
    // //if(httpCode == 200) {
       
    // a_os << curlpp::options::Url(a_firstUrl);
    // //}

   
    try {
        // Create an instance of curlpp::Easy
        curlpp::Easy request;

        // Set the URL
        request.setOpt(curlpp::options::Url(a_firstUrl));

        // Perform the request
        request.setOpt(curlpp::options::WriteStream(&a_os));
        request.perform();

        // Get the response code
                //long responseCode;
        //request.getOpt(curlpp::options::Http2StatusCode(responseCode));

        // Check if the response code is 200
        // if (responseCode == 200) {
        //     std::cout << "Request succeeded (status 200)" << std::endl;
        // } else {
        //     std::cout << "Request failed with status code: " << responseCode << std::endl;
        // }

    } catch (curlpp::RuntimeError& e) {
        std::cerr << e.what() << std::endl;
    } catch (curlpp::LogicError& e) {
        std::cerr << e.what() << std::endl;
    }
}


containers::Page Crawl::createPage(std::string const& a_firstUrl, std::ostringstream const& a_os)
{
    std::string title = m_parser.title(a_os);
    return containers::Page{a_firstUrl, title};
}

void Crawl::indexPage(std::ostringstream const& a_os, containers::Page & a_page) 
{
    std::vector<std::string> words;
    
    m_parser.words(a_os,words);
    m_urlsWords.insert(a_page, createWordsCounterPtr());

    indexWords(a_page, words);
}


} // namespace crawl
