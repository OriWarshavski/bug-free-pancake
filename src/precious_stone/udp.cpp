#include "udp.hpp"
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

namespace precious_stone {

static int create_socket() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock >= 0);
    return sock;
}

static sockaddr_in create_channel(const char* a_ip, int a_port, int a_socket) {
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(a_ip);
    sin.sin_port = htons(a_port);
    //bind(a_socket, reinterpret_cast<sockaddr*>(&sin), sizeof(sin));
    return sin;
}

Udp::Udp(const char* a_ip, int a_port)
: m_socket(create_socket())
, m_channel(create_channel(a_ip, a_port, m_socket))
{
}

Udp::~Udp()
{
    close(m_socket);
}

char* Udp::recieve()
{
    sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int num_bytes = recvfrom(m_socket, m_buffer, sizeof(m_buffer), 0, 
                                reinterpret_cast<sockaddr*>(&client_addr), &addr_len);
    m_buffer[num_bytes] = '\0';
    return m_buffer;
}

int Udp::send(const char* a_data)
{
    int sent_bytes;
    sent_bytes = sendto(m_socket, a_data, strlen(a_data), 0, reinterpret_cast<sockaddr*>(&m_channel), sizeof(m_channel));
    assert(sent_bytes >= 0);
    return sent_bytes;
}

} //precious_stone