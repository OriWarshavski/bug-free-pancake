#include "uiSearch.hpp"


namespace coach_ui {

using namespace nickname;

void ileagleTerm(std::string const& a_term)
{
    std::cout << a_term << ": " << "is not leagle!!\n";
}

void printTerm(std::string const& a_term)
{
    std::cout <<  "search term: " <<  a_term << " - ";
}

void PresentPage(nickname::UrlsContainer const& a_contain, size_t a_listLength)
{
	int i = 1;
	std::cout << "is found on these pages: \n";
    for(auto & page : a_contain){
		std::cout << "====================================================================\n";
        std::cout << i << ") title: \"" << page.title() << "\"\n" << "   url: " << page.url() << "\n";
		std::cout << "-----------------------------------------------------------------\n";
		++i;
		if(--a_listLength == 0) {
			break;
		}
    }
}

void askForTerm(std::string& a_term) noexcept
{
	std::cout << "\nenter your term to search (or 'q' to quit): ";
	std::cin >> a_term;
}

void printCrawlResult(std::string const& a_url, size_t a_ignored, size_t a_pages, size_t a_words) noexcept
{
	std::cout << "crawl result for - "  << a_url << ":\n";
	std::cout << "Ignored pages: " << a_ignored << "\n";
	std::cout << "Indexed pages: " << a_pages << "\n";
	std::cout << "Indexed words: " << a_words << "\n";
	std::cout << "====================================================================\n";
}

void notifyNotFound() noexcept
{
	std::cout << "not found\n";
	std::cout << "====================================================================\n";
}

}//namespace coach_ui
