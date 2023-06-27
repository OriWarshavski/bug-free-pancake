#pragma once
#include <unordered_map>
#include <map>

#include <string>

namespace containers {
    
class Page final {
public:
    Page() = default;
    Page(std::string a_url, std::string a_title);
    Page(const Page& a_other) = default;
    Page& operator=(const Page& a_other) = default;
    ~Page() = default;
    
    std::string const& operator()();
    std::string const& url() const;
    std::string const& title() const;
    bool operator<(const Page& a_other) const;
    bool operator==(const Page& a_other) const;
    // void insertPageLinks(std::string const a_url);
    // std::map<std::string, size_t> const& getMap() const;

private:
    std::string m_url;
    std::string m_title;
    // std::map<std::string, size_t> m_currentLinksToPage;
};

} // namespace containers

namespace std {
    
template<>
struct hash<containers::Page> 
{
    size_t operator()(containers::Page const& a_page) const;
};
    
} // namespace std
