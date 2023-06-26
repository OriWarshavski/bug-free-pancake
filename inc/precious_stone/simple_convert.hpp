#ifndef SIMPLE_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
#define SIMPLE_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91

#include "massage.hpp"
#include "transform_abstract.hpp"

namespace precious_stone {

class SimpleConvert : public TransformAbstract{
public:
    SimpleConvert() = default;
    SimpleConvert(const SimpleConvert &a_other) = delete;
    SimpleConvert& operator=(const SimpleConvert &a_other) = delete;
    virtual ~SimpleConvert() = default;

    const Massage convert(const Massage& a_text) override {return a_text; };
};

} //precious_stone

#endif //SIMPLE_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
