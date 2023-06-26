#ifndef UDP_HPP_4e0c94d9_7a01_4768_9847_f7036cec7e8f
#define UDP_HPP_4e0c94d9_7a01_4768_9847_f7036cec7e8f

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>

namespace precious_stone {

static const unsigned int BUFFER_SIZE = 50;

class Udp {
public:
    explicit Udp(const char* a_ip, int a_port);
    Udp(const Udp &a_other) = delete;
    Udp& operator=(const Udp &a_other) = delete;
    ~Udp();

    char* recieve();
    int send(const char* a_data);

private:
    int m_socket;
    sockaddr_in m_channel;
    char m_buffer[BUFFER_SIZE] = {0};

};

} //precious_stone

#endif //UDP_HPP_4e0c94d9_7a01_4768_9847_f7036cec7e8f
