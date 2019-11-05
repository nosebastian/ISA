#include "dns/dns.hpp"
#include "arguments.hpp"


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>


int main(int argc, char ** argv)
{
    arguments args(argc, argv);

    if(args.arguments_ok == false)
    {
        std::cerr << "Unknow usage of arguments:" << std::endl << "Programm usage: " << std::endl << "dns [-r] [-x] [-6] -s RequestServerName [-p port] LookupAddress" << std::endl;
        return 1;
    }
    dns datagram, received;

    struct addrinfo hint,  *result;
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_DGRAM;
    hint.ai_flags = 0;
    hint.ai_protocol = 0;

    int ret = getaddrinfo("8.8.4.4", "53", &hint, &result);

    auto hostname2 = args.lookup_hostname;

    datagram.header.id = 0x0F69;
    datagram.header.is_response = false;
    datagram.header.recursion_desired = true;
    datagram.addQuestion(hostname2, DNS_A, DNS_CLASS_IN);

    uint8_t buffer[DNS_MAX_SIZE] = {0,};
    uint8_t buffer_receive[DNS_MAX_SIZE] = {0,};
    size_t dgram_size = datagram.encode(buffer, DNS_MAX_SIZE);


    int sock = socket(result->ai_family , result->ai_socktype, result->ai_protocol);
    perror("SOCK: ");

    ret = connect(sock, result->ai_addr, result->ai_addrlen);
    perror("SOCK: ");

    ret = send(sock, buffer, DNS_MAX_SIZE, 0);
    perror("SOCK: ");

    ret = recv(sock, buffer_receive, DNS_MAX_SIZE, 0);
    perror("SOCK: ");

    received.decode(buffer_receive, buffer_receive, DNS_MAX_SIZE);

    close(sock);

    std::cout << received;

    return 0;
}