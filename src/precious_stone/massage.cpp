#include "massage.hpp"

#include <stdexcept>

namespace precious_stone {

Massage::Massage(std::string a_text) 
: m_text(a_text)
{
}

Massage::Massage(const Massage &a_other)
: m_text(a_other.m_text)
{
}

Massage& Massage::operator=(const Massage &a_other) 
{
    m_text = a_other.m_text;
    return *this;
}

const char* Massage::text() const noexcept
{
    return m_text.c_str();
}

int Massage::size() const noexcept
{
    return m_text.size();
}

const char& Massage::operator[](const int a_index) const
{
    if(a_index >= size() || a_index < 0) {
         throw std::invalid_argument("index out of range");
    }
    return m_text[a_index];
}

char& Massage::operator[](const int a_index) 
{
    if(a_index >= size() || a_index < 0) {
         throw std::invalid_argument("index out of range");
    }
    return m_text[a_index];
}

} //namespace precious_stone