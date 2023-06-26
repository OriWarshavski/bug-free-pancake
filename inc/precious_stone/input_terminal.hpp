#ifndef INPUT_TERMINAL_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
#define INPUT_TERMINAL_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91

#include "input_stream.hpp"

namespace precious_stone {

class TerminalInput final : public StreamInput{
public:
    explicit TerminalInput(bool a_oneMassage = false);
    TerminalInput(const TerminalInput &a_other) = delete;
    TerminalInput& operator=(const TerminalInput &a_other) = delete;
    virtual ~TerminalInput() = default;

    bool continueReading() override;

private:
    bool m_continueReading;
    bool m_oneMassage;
    int m_msgCounter = 0;
    
};

} //precious_stone

#endif //INPUT_TERMINAL_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
