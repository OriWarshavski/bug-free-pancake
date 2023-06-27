#include "page.hpp"

namespace containers {
    
Page::Page(std::string a_url, std::string a_title)
: m_url(a_url)
, m_title(a_title)
{}

bool Page::operator<(const Page& a_other) const
{
    return m_url < a_other.m_url;
}

bool Page::operator==(const Page& a_other) const {
    return url() == a_other.url();
}

std::string const& Page::url() const
{
    return m_url;
}

std::string const& Page::title() const
{
    return m_title;
}

std::string const& Page::operator()()
{
    return m_url;
}

// void Page::insertPageLinks(std::string const a_url)
// {
//     if(m_currentLinksToPage.count(a_url) > 0) {
//         m_currentLinksToPage[a_url] += 1;
//     } else {
//         m_currentLinksToPage[a_url] = 1;
//     }
    
// }

// std::map<std::string, size_t> const& Page::getMap() const
// {
//     return m_currentLinksToPage;
// }

} // namespace containers

namespace std {
    
size_t hash<containers::Page>::operator()(containers::Page const& a_page) const
{
    return std::hash<std::string>{}(a_page.url());
}




} // namespace std