#ifndef INPUT_UDP_HPP_a530a97f_338a_40a2_8239_6b04f79c9894
#define INPUT_UDP_HPP_a530a97f_338a_40a2_8239_6b04f79c9894

#include "massage.hpp"
#include "input_abstract.hpp"
#include "udp.hpp"

namespace precious_stone {

class UdpInput : public InputAbstract{
public:
    explicit UdpInput(int a_port);
    UdpInput(const UdpInput &a_other) = delete;
    UdpInput& operator=(const UdpInput &a_other) = delete;
    ~UdpInput() = default;

    const Massage read() override;
    bool continueReading() override;

private:
    Udp m_udp;
    bool m_continueReading;
};

} //precious_stone

#endif //INPUT_UDP_HPP_a530a97f_338a_40a2_8239_6b04f79c9894
