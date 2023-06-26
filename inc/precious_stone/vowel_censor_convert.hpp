#ifndef VOWEL_CENSOR_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
#define VOWEL_CENSOR_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91

#include "massage.hpp"
#include "transform_abstract.hpp"

namespace precious_stone {

class VowelCensorConvert : public TransformAbstract{
public:
    VowelCensorConvert() = default;
    VowelCensorConvert(const VowelCensorConvert &a_other) = delete;
    VowelCensorConvert& operator=(const VowelCensorConvert &a_other) = delete;
    virtual ~VowelCensorConvert() = default;

    const Massage convert(const Massage& a_text) override;

private:
    static const std::string m_vowls;
};

} //precious_stone

#endif //VOWEL_CENSOR_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
