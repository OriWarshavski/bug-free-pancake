#ifndef LINK_BOX_HPP_5d265f90_8496_47d7_9574_c76dad74aeb9
#define LINK_BOX_HPP_5d265f90_8496_47d7_9574_c76dad74aeb9

#include "massage.hpp"
#include "input_abstract.hpp"
#include "output_abstract.hpp"
#include "transform_abstract.hpp"

namespace precious_stone {

class LinkBox {
public:
    explicit LinkBox(InputAbstract& a_input, TransformAbstract& a_convert, OutputAbstract& a_output);
    LinkBox(const LinkBox &a_other) = delete;
    LinkBox& operator=(const LinkBox &a_other) = delete;
    ~LinkBox() = default;

    void linking();

private:
    InputAbstract& m_input;
    TransformAbstract& m_convert;   
    OutputAbstract& m_output;
};


} //precious_stone

#endif //LINK_BOX_HPP_5d265f90_8496_47d7_9574_c76dad74aeb9
