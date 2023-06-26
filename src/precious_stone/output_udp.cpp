#include "output_udp.hpp"

namespace precious_stone {

UdpOutput::UdpOutput(const char* a_ip, int a_port)
: m_udp(a_ip, a_port)
{
}

void UdpOutput::write(Massage const& a_text) {
    m_udp.send(a_text.text());
}

} //precious_stone
