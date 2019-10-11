#ifndef __SOCKET_HPP

#define __SOCKET_HPP

#include <vector>
#include <cstddef>
#include <cstdint>

#include "../network_data.hpp"

class socket
{
private:
    std::vector<uint8_t> _buffer;
    int _socket_file_descriptor;
    network_data * out_data;
    network_data * in_data;
    void(*notify_function)(int);
public:
    void connect();
    void sendData();
    void sendData(size_t number_of_out_packets);
    void receiveData();
    
    void setOutData(network_data * protocol_data);
    void setInData(network_data * protocol_data);
    void setReceiveNotify(void(*notify_function)(int));
    socket(int datagram_type, char * hostname, char * service, size_t max_buffersize);
    ~socket();
};

#endif
