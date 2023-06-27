#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>

#include "page.hpp"

namespace crawl
{

    using Container = std::vector<std::string>;
    using PageContainer = std::vector<containers::Page>;
    using ConditionFunction = std::function<bool(std::string const &)>;

    class Parser
    {

    public:
        Parser() = default;
        Parser(Parser const &a_other) = default;
        Parser &operator=(Parser const &a_other) = default;
        ~Parser() = default;

        void links(std::string const& a_currentUrl, std::ostringstream const &a_content, std::vector<std::string>& a_urls ,ConditionFunction a_insertUrlCondition) const;
        void words(std::ostringstream const &a_content, Container& a_words) const;
        std::string title(std::ostringstream const &a_content) const;
        std::string extractSite(std::string const& a_url);
    };

} // namespace crawl