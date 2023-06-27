#pragma once

#include <string>  			// std::string
#include <memory>  			// std::shared_ptr

#include "dictionary.hpp"
#include "page.hpp"

namespace coach_search::definitions {

//----> table to fill with : index:page  | value:shared_ptr(index:words | value:counter)
using WordRepetitions = size_t;
using WordsCounterTable = containers::Dictionary<std::string, WordRepetitions>;
using WordsCounterTablePtr = std::shared_ptr<WordsCounterTable>;
using PagesTable = containers::Dictionary<containers::Page, WordsCounterTablePtr>;

//----> table to fill with : index:word | value:shared_ptr(index:pages | value:counter)
using PageCounterTable = containers::Dictionary<containers::Page, WordRepetitions>;
using PageCounterTablePtr = std::shared_ptr<PageCounterTable>;
using WordsTable = containers::Dictionary<std::string, PageCounterTablePtr>;

} //namespace coach_search::definitions
