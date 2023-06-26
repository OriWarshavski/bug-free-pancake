#ifndef COLOR_HPP_b940cdaa_a6fd_42cf_b60e_30cc78131f0b
#define COLOR_HPP_b940cdaa_a6fd_42cf_b60e_30cc78131f0b

namespace advcpp {

    static const int INIT_COLOR = 255;

struct Color {

    Color();
    Color(unsigned int a_red, unsigned int a_green, unsigned int a_blue);
    
    unsigned int m_red;
    unsigned int m_green;
    unsigned int m_blue;
};

inline Color::Color() 
: m_red(INIT_COLOR)
, m_green(INIT_COLOR)
, m_blue(INIT_COLOR)
{
}

inline Color::Color(unsigned int a_red, unsigned int a_green, unsigned int a_blue) 
: m_red(a_red)
, m_green(a_green)
, m_blue(a_blue)
{
}

}


#endif // COLOR_HPP_b940cdaa_a6fd_42cf_b60e_30cc78131f0b