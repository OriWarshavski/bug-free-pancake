#include "input_stream.hpp"
#include <iostream>

namespace precious_stone {

StreamInput::StreamInput(std::istream& a_streamType, bool a_oneMassage)
: m_istreamType(a_streamType)
, m_continueReading(true)
, m_oneMassage(a_oneMassage)
{
}

const Massage StreamInput::read() {
    try {
        std::getline(m_istreamType, m_lastLine);
    } catch(...) {
        std::cout << "read fail" << '\n';
        throw;
    }
    return Massage(m_lastLine);
}

bool StreamInput::continueReading()
{
    if(m_msgCounter == 1) {
        m_continueReading = false;
    }
    else if(m_oneMassage) {
        ++m_msgCounter;
    }
    return m_continueReading;
}

} //precious_stone
