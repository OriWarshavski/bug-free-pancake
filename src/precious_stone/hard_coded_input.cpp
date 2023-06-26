#include "hard_coded_input.hpp"

namespace precious_stone {

HardCodedInput::HardCodedInput()
:m_continue(true)
{
}

const Massage HardCodedInput::read() {
    char str[] = "Hello World";
    Massage text(str);
    m_continue = false;
    return text;
}

bool HardCodedInput::continueReading() 
{
    return m_continue;
}
} //precious_stone
