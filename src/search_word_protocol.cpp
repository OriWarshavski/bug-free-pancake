#include "search_word_protocol.hpp"

namespace words {

std::string normalizeWord(std::string const& a_word) 
{
    size_t size = a_word.size();
    std::string result{""};
    
    for (size_t i = 0; i < size; ++i) {
        char c = a_word[i];
        if (c == '\'') {
            if (i + 1 < size && a_word[i + 1] == 's') {
                break;
            } else {
                continue;
            }
        } else if (isalpha(c)) {
            result += tolower(c);
        }
    }
    return result;
}


} // namespace word