#ifndef HARD_CODED_INPUT_HPP_4fb89d0e_ac4c_44f7_aa81_0b0ba4a9761c
#define HARD_CODED_INPUT_HPP_4fb89d0e_ac4c_44f7_aa81_0b0ba4a9761c

#include "massage.hpp"
#include "input_abstract.hpp"

namespace precious_stone {

class HardCodedInput : public InputAbstract{
public:
    HardCodedInput();
    HardCodedInput(const HardCodedInput &a_other) = delete;
    HardCodedInput& operator=(const HardCodedInput &a_other) = delete;
    ~HardCodedInput() = default;

    const Massage read() override final;
    bool continueReading() override final;

private:
    bool m_continue;
};

} //precious_stone

#endif //HARD_CODED_INPUT_HPP_4fb89d0e_ac4c_44f7_aa81_0b0ba4a9761c
