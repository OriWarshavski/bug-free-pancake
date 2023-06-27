#pragma once

#include <vector>       //std::vector
#include <map>          //std::map
#include <utility>      //std::pair
#include <limits>		//std::numeric_limits

#include "json.hpp" //json
namespace coach_search {

using UrlsList = std::vector<std::string>;
using json = nlohmann::json;

static const unsigned int MaxValue = std::numeric_limits<unsigned int>::max();

/*configuration will set once according to json file named "search_config.json"
default configurations:
search mode: DFS
maxPages: unlimited == maxValue
maxDepth: unlimited == maxValue*/
class SearchConfig final {
public:
    enum class SearchMode {DFS = 1, BFS = 2};
    enum class SetDefinition {UNLIMITED, LIMITED};

    SearchConfig();
    SearchConfig(const SearchConfig& a_other) = default;
    SearchConfig& operator=(const SearchConfig& a_other) = default;
    ~SearchConfig() = default;

    UrlsList const& urls() const;

    using ConfigPair = std::pair<SetDefinition, unsigned int>;
    ConfigPair maxPages() const;
    ConfigPair maxDepth() const;
    SearchMode searchMode() const;
	ConfigPair listLength() const;

private:
    void defineSearchMode(json& a_json);

private:
    std::map<SearchMode, std::string> m_searchModesMap;
	SearchMode m_searchMode;

    unsigned int m_maxPages;
    bool m_arePagesLimited;

    unsigned int m_maxDepth;
    bool m_isDepthLimited;

	unsigned int m_listLength;
	bool m_islistLengthLimited;

    UrlsList m_urls;
};

} //namespace coach_search
