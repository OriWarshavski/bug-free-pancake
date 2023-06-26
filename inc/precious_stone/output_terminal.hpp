#ifndef OUTPUT_TERMINAL_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
#define OUTPUT_TERMINAL_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91

#include "output_stream.hpp"

namespace precious_stone {

class TerminalOutput : public StreamOutput {
public:
    TerminalOutput();
    TerminalOutput(const TerminalOutput &a_other) = delete;
    TerminalOutput& operator=(const TerminalOutput &a_other) = delete;
    virtual ~TerminalOutput() = default;
};

} //precious_stone

#endif //OUTPUT_TERMINAL_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
