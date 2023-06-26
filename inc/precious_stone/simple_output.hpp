#ifndef SIMPLE_OUTPUT_HPP_dd176319_2535_439a_bcec_30af8c069879
#define SIMPLE_OUTPUT_HPP_dd176319_2535_439a_bcec_30af8c069879

#include "output_abstract.hpp"
#include <string>

namespace precious_stone {

class SimpleOutput : public OutputAbstract {
public:
    SimpleOutput() = default;
    SimpleOutput(const SimpleOutput &a_other) = delete;
    SimpleOutput& operator=(const SimpleOutput &a_other) = delete;
    virtual ~SimpleOutput() = default;

    void write(Massage const& a_text) override {m_result = a_text; };

    Massage m_result;

};

} //precious_stone

#endif //SIMPLE_OUTPUT_HPP_dd176319_2535_439a_bcec_30af8c069879
