#include "output_stream.hpp"
#include <iostream>

namespace precious_stone {

StreamOutput::StreamOutput(std::ostream& a_ostreamType)
: m_ostreamType(a_ostreamType)
{
}

void StreamOutput::write(Massage const& a_text) 
{
    m_ostreamType << a_text.text() << '\n';
}

} //precious_stone
