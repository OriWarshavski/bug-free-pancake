#include "input_terminal.hpp"
#include <iostream>

namespace precious_stone {

TerminalInput::TerminalInput(bool a_oneMassage)
: StreamInput(std::cin)
, m_continueReading(true)
, m_oneMassage(a_oneMassage)
{
}

bool TerminalInput::continueReading()
{
    if(m_lastLine == "q" || m_msgCounter == 1) {
        m_continueReading = false;
    }
    else if(m_oneMassage) {
        ++m_msgCounter;
    }
    else {
        std::cout << "type your massege: \n(type q to exit)\n";
    }
    return m_continueReading;
}

} //precious_stone
