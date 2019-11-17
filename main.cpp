#include "dns/dns.hpp"
#include "arguments.hpp"
#include "UrlFromArguments.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#define MAX_SEND_NUMBER 1

enum {RUN_OK = 0, RUN_ARG_ERR = 1, RUN_SERVER_ADDR_ERR = 2, RUN_CONNECTION_ERR = 3, RUN_INTERNAL_ERROR = 4, RUN_EXTERNAL_PACKET_ERROR = 5};

int main(int argc, char ** argv)
{
    arguments args(argc, argv);

    if(args.arguments_ok == false)
    {
        std::cerr 
            << "Unknow usage of arguments:" << std::endl 
            << "Programm usage: " << std::endl 
            << "dns [-r] [-x] [-6] -s RequestServerName [-p port] LookupAddress" << std::endl;
        return RUN_ARG_ERR;
    }

    //Process arguments to url
    UrlFromArguments url(args);

    //Structures for getaddrinfo for server hostname lookup
    struct addrinfo hint,  *result, *current_result;
    //Hint for lookup, use any IP protocol only upd
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_DGRAM;
    hint.ai_flags = 0;
    hint.ai_protocol = 0;

    //Lookup
    int ret = getaddrinfo(args.server_hostname.c_str(), args.port_number.c_str(), &hint, &result);
    //Check for error
    if(ret != 0)
    {
        //print error
        std::cerr << "getaddrinfo: " << gai_strerror(ret) << std::endl;
        //exit with error
        return RUN_SERVER_ADDR_ERR;
    }

    //try to create socket
    //following code is inspired by code from
    //getaddrinfo man page http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
    int sock;

    for (current_result = result; current_result != NULL; current_result = current_result->ai_next)
    {
        sock = socket(current_result->ai_family, current_result->ai_socktype, current_result->ai_protocol);
        if (sock == -1)
            continue;
        if (connect(sock, current_result->ai_addr, current_result->ai_addrlen) != -1)
            break;
        close(sock);
    }
    if (current_result == NULL) { /* No address succeeded */
        std::cerr << "Failed to establish connection" << std::endl;
        freeaddrinfo(result);
        return RUN_CONNECTION_ERR;
    }
    freeaddrinfo(result); /* No longer needed */



    //create structure for client packet
    dns datagram;
    uint8_t buffer[DNS_MAX_SIZE] = {0,};
    //constant id randomly selected once uppon the time
    datagram.header.id = 0x0F69;
    datagram.header.is_response = false;
    datagram.header.recursion_desired = args.is_recursive;
    datagram.addQuestion(url.url, DNS_AAAA, DNS_CLASS_IN);
    //encode packet to buffer
    size_t dgram_size = datagram.encode(buffer, DNS_MAX_SIZE);
    //check if encoding went ok
    if(dgram_size == -1)
    {
        std::cerr << "Program has encoutered error while encoding outgoing packet" << std::endl;
        return RUN_INTERNAL_ERROR;
    }



    //create structure for received packet
    dns received;
    uint8_t buffer_receive[DNS_MAX_SIZE] = {0,};
    //Send as untill succes or limit reached
    for (size_t i = 0; i < MAX_SEND_NUMBER; i++)
    {
        ret = send(sock, buffer, DNS_MAX_SIZE, 0);
        if(ret == -1)
        {
            perror("send: ");
        }




        ret = recv(sock, buffer_receive, DNS_MAX_SIZE, 0);
        if(ret == -1)
        {
            perror("recv: ");
        }
    }

    size_t received_size = received.decode(buffer_receive, buffer_receive, DNS_MAX_SIZE);

    close(sock);

    std::cout << received;

    return RUN_OK;
}