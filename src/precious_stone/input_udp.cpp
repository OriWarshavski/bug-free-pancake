#include "input_udp.hpp"

namespace precious_stone {

UdpInput::UdpInput(int a_port)
: m_udp("127.0.0.1", a_port)
, m_continueReading(true)
{
}

const Massage UdpInput::read() {
    std::string msg{m_udp.recieve()};
    if(msg == "q") {
        m_continueReading = false;
    }
    return Massage(msg);
}

bool UdpInput::continueReading() 
{
    return m_continueReading;
}
} //precious_stone
