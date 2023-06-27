#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>

#include "page.hpp"
#include "nicknames.hpp"

namespace search{
using namespace nickname;

class QuryCache final{
public:
    QuryCache() = default;
    QuryCache(QuryCache const& a_other) = delete;
    QuryCache& operator=(QuryCache const& a_other) = delete;
    ~QuryCache() = default;

    void insert(std::string const& a_terms, UrlsContainer const& a_urlsStr);
    bool urls(std::string const& a_terms, UrlsContainer& a_constainer);

private:
    std::unordered_map<std::string, UrlsContainer> m_urls;
    std::mutex m_mtx;
};



}// search