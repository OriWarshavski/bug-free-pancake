#include "vowel_censor_convert.hpp"
#include <cctype>

namespace precious_stone {

std::string const VowelCensorConvert::m_vowls = ("AEIOUaeiou");

const Massage VowelCensorConvert::convert(const Massage& a_text)
{
    int length = a_text.size();
    std::string transformed = a_text.text();
    for(int i = 0; i < length; ++i) {
        if(m_vowls.find(transformed[i]) != std::string::npos) {
            transformed[i] = '*';
        }
    }
    return Massage(transformed);
}


} //precious_stone