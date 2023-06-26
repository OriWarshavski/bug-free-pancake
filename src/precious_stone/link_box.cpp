#include "link_box.hpp"

namespace precious_stone {

LinkBox::LinkBox(InputAbstract& a_input, TransformAbstract& a_convert, OutputAbstract& a_output)
: m_input(a_input)
, m_convert(a_convert)
, m_output(a_output)
{
}

void LinkBox::linking()
{
    while(m_input.continueReading()) {
        Massage text = m_input.read();
        Massage convertedText = m_convert.convert(text);
        m_output.write(convertedText);
    }
}

} //precious_stone
