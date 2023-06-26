#ifndef TRANSFORM_ABSTACT_HPP_c8ddf6e7_2efd_4e47_a1fb_0eeba0663f96
#define TRANSFORM_ABSTACT_HPP_c8ddf6e7_2efd_4e47_a1fb_0eeba0663f96

#include "massage.hpp"

namespace precious_stone {

class TransformAbstract {
public:
    TransformAbstract() = default;
    TransformAbstract(const TransformAbstract &a_other) = delete;
    TransformAbstract& operator=(const TransformAbstract &a_other) = delete;
    virtual ~TransformAbstract() = default;

    virtual const Massage convert(const Massage& a_text) = 0;

};

} //precious_stone

#endif //TRANSFORM_ABSTACT_HPP_c8ddf6e7_2efd_4e47_a1fb_0eeba0663f96
