#include "capitalize_convert.hpp"
#include <cctype>

namespace precious_stone {

const Massage CapitalizeConvert::convert(const Massage& a_text)
{
    std::string transformed = a_text.text();
    transformed[0] = toupper(transformed[0]);
    int length = a_text.size();
    for(int i = 1; i < length; ++i) {
        if(std::isalpha(transformed[i]) && (!std::isalpha(transformed[i - 1]) && !std::isdigit(transformed[i - 1]))) {
            transformed[i] = toupper(a_text[i]);
        }
    }
    return Massage(transformed);
}


} //precious_stone