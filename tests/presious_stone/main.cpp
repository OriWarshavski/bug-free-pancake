
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>
#include "output_udp.hpp"

using namespace precious_stone;

int main() 
{
    UdpOutput udp("127.0.0.1", 7777);
    udp.write(ping);
    sin = Recieve(sock);
    return 0;
}
