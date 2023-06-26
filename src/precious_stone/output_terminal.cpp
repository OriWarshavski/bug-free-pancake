#include "output_terminal.hpp"
#include <iostream>

namespace precious_stone {

TerminalOutput::TerminalOutput()
: StreamOutput(std::cout)
{
}

} //precious_stone
