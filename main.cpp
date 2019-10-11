#include "dns/dns.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


int main(int argc, char ** argv)
{
    dns datagram;

    auto hostname2 = std::string("google.com");

    datagram.header.id = 0x0F69;
    datagram.header.is_response = false;
    datagram.header.recursion_desired = true;
    datagram.addQuestion(hostname2, DNS_Q_ALL, DNS_CLASS_IN);

    uint8_t buffer[DNS_MAX_SIZE] = {0,};
    size_t dgram_size = datagram.encode(buffer, DNS_MAX_SIZE);


    struct addrinfo hint,  *result;
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_DGRAM;
    hint.ai_flags = 0;
    hint.ai_protocol = 0;

    int ret = getaddrinfo("2001:4860:4860::8888", "53", &hint, &result);
    
    int sock = socket(result->ai_family , result->ai_socktype, result->ai_protocol);

    ret = connect(sock, result->ai_addr, result->ai_addrlen);

    ret = send(sock, buffer, DNS_MAX_SIZE, 0);
    perror("SOCK: ");
    close(sock);

    return 0;
}