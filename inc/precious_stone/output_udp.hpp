#ifndef OUTPUT_UDP_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6
#define OUTPUT_UDP_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6

#include "massage.hpp"
#include "output_abstract.hpp"
#include "udp.hpp"

namespace precious_stone {

class UdpOutput : public OutputAbstract{
public:
    explicit UdpOutput(const char* a_ip, int a_port);
    UdpOutput(const UdpOutput &a_other) = delete;
    UdpOutput& operator=(const UdpOutput &a_other) = delete;
    ~UdpOutput() = default;

    void write(Massage const& a_text) override;

private:
    Udp m_udp;
};

} //precious_stone

#endif //OUTPUT_UDP_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6
