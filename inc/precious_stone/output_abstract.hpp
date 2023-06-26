#ifndef OUTPUT_ABSTACT_HPP_dee39396_6834_4880_92c2_84c54234bdc2
#define OUTPUT_ABSTACT_HPP_dee39396_6834_4880_92c2_84c54234bdc2

#include "massage.hpp"

namespace precious_stone {

class OutputAbstract {
public:
    virtual ~OutputAbstract() = default;

    virtual void write(Massage const& a_text) = 0;

protected:
    OutputAbstract() = default;
    OutputAbstract(const OutputAbstract &a_other) = delete;
    OutputAbstract& operator=(const OutputAbstract &a_other) = delete;

};

} //precious_stone

#endif //OUTPUT_ABSTACT_HPP_dee39396_6834_4880_92c2_84c54234bdc2
