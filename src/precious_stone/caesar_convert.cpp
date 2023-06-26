#include "caesar_convert.hpp"
#include <cctype>

namespace precious_stone {

static const int LETTERS_NUM = 26;

static void ceasar_algorithm(std::string& a_text, const int a_shiftRight) 
{
    int length = a_text.size();
    for(int i = 0; i < length; ++i) {
        if(std::isalpha(a_text[i])) {
            char factor = 'a';
            std::isupper(a_text[i]) ? factor = 'A' : factor;
            a_text[i] = ((a_text[i] + a_shiftRight - factor) % LETTERS_NUM) + factor;
        }
    }

}

CaesarConvert::CaesarConvert(const int a_shiftRight) 
: m_shiftRight(a_shiftRight)
{
}

const Massage CaesarConvert::convert(const Massage& a_text)
{
    std::string transformed = static_cast<std::string>(a_text.text());
    ceasar_algorithm(transformed, m_shiftRight);
    return Massage(transformed);
}


} //precious_stone