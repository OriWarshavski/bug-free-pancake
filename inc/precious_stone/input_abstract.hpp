#ifndef INPUT_ABSTACT_HPP_ac6f21ef_3148_4ff3_8736_9934f301b907
#define INPUT_ABSTACT_HPP_ac6f21ef_3148_4ff3_8736_9934f301b907

#include "massage.hpp"

namespace precious_stone {

class InputAbstract {
public:
    virtual ~InputAbstract() = default;

    virtual const Massage read() = 0;
    virtual bool continueReading() = 0;

protected: 
    InputAbstract() = default;
    InputAbstract(const InputAbstract &a_other) = delete;
    InputAbstract& operator=(const InputAbstract &a_other) = delete;

};

} //precious_stone

#endif //INPUT_ABSTACT_HPP_ac6f21ef_3148_4ff3_8736_9934f301b907
