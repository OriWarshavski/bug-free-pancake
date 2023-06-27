#include <fstream>  //std::ifstream
#include <iostream> //std::cerr
#include <string>   //std::string

#include "configuration.hpp"

namespace coach_search {

static json createJson()
{
    std::string fileName = "search_config.json";
    std::ifstream configFile{fileName};
    if(!configFile.is_open()) {
        throw(std::ios_base::failure("search_config.json file didn't found"));
    }
    json j;
    configFile >> j;
    return j;
}

SearchConfig::SearchConfig()
: m_searchModesMap{ { SearchMode::DFS, "DFS" }, { SearchMode::BFS, "BFS" }}
, m_arePagesLimited(true)
, m_isDepthLimited(true)
, m_islistLengthLimited(true)
{
    json j = createJson();

    if(!j.contains("pages")) {
        throw(std::domain_error("at least one page must be configured"));
    }

    if(j.contains("number of urls")) {
        m_urls.reserve(j["number of urls"]);
    }

    for(auto& page : j["pages"]) {
        m_urls.emplace_back(page["url"]);
    }

    if(j.contains("max pages")) {
        m_maxPages = j["max pages"];
    }
    else {
        m_arePagesLimited = false;
    }

    if(j.contains("max depth")) {
        m_maxDepth = j["max depth"];
    }
    else {
        m_isDepthLimited = false;
    }

    if(j.contains("list length")) {
		m_listLength = j["list length"];
    }
	else {
		m_islistLengthLimited = false;
	}

    defineSearchMode(j);
}

void SearchConfig::defineSearchMode(json& a_json)
{
    if(a_json.contains("search mode")) {
        auto searchModeValue = a_json["search mode"];
        auto itr = m_searchModesMap.begin();
        auto end = m_searchModesMap.end();

        while(itr != end) {
            if((*itr).second == searchModeValue || static_cast<int>((*itr).first) == searchModeValue) {
                m_searchMode = (*itr).first;
                return;
            }
            ++itr;
        }
    }
    //wrong search mode in json file
    m_searchMode = SearchMode::DFS;
}

UrlsList const& SearchConfig::urls() const
{
    return m_urls;
}

SearchConfig::ConfigPair SearchConfig::maxPages() const
{
    if(m_arePagesLimited) {
        return std::make_pair(SetDefinition::LIMITED, m_maxPages);
    }
    return std::make_pair(SetDefinition::UNLIMITED, MaxValue);
}

SearchConfig::ConfigPair SearchConfig::maxDepth() const
{
    if(m_isDepthLimited) {
        return std::make_pair(SetDefinition::LIMITED, m_maxDepth);
    }
    return std::make_pair(SetDefinition::UNLIMITED, MaxValue);
}

SearchConfig::SearchMode SearchConfig::searchMode() const
{
    return m_searchMode;
}

SearchConfig::ConfigPair SearchConfig::listLength() const
{
    if(m_islistLengthLimited) {
        return std::make_pair(SetDefinition::LIMITED, m_listLength);
    }
    return std::make_pair(SetDefinition::UNLIMITED, MaxValue);
}

} //namespace coach_search
