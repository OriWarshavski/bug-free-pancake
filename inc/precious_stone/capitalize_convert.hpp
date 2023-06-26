#ifndef CAPITALIZE_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
#define CAPITALIZE_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91

#include "massage.hpp"
#include "transform_abstract.hpp"

namespace precious_stone {

class CapitalizeConvert final : public TransformAbstract{
public:
    CapitalizeConvert() = default;
    CapitalizeConvert(const CapitalizeConvert &a_other) = delete;
    CapitalizeConvert& operator=(const CapitalizeConvert &a_other) = delete;
    virtual ~CapitalizeConvert() = default;

    const Massage convert(const Massage& a_text) override final;
};

} //precious_stone

#endif //CAPITALIZE_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
