#ifndef CAESAR_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
#define CAESAR_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91

#include "massage.hpp"
#include "transform_abstract.hpp"

namespace precious_stone {

class CaesarConvert final : public TransformAbstract{
public:
    explicit CaesarConvert(const int a_shiftRight);
    CaesarConvert(const CaesarConvert &a_other) = delete;
    CaesarConvert& operator=(const CaesarConvert &a_other) = delete;
    virtual ~CaesarConvert() = default;

    const Massage convert(const Massage& a_text) override final;

private:
    const int m_shiftRight;
};

} //precious_stone

#endif //CAESAR_CONVERT_HPP_4df092fc_6cb6_4f1c_9e46_8afc99508c91
