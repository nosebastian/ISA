#ifndef __ARGUMENTS_HPP

#define __ARGUMENTS_HPP

#include <string>
#include <arpa/inet.h>

typedef enum {
    ARGUMENT_IP_V4,
    ARGUMENT_IP_V6,
    ARGUMENT_DOMAIN,
} arguments_lookup_t;

class arguments
{
private:
    void _parse_lookup_hostname();
public:
    bool is_v6;
    bool is_recursive;
    bool is_reverse;
    bool arguments_ok;
    arguments_lookup_t lookup_type;
    std::string server_hostname;
    std::string lookup_hostname;
    std::string port_number;

    uint8_t address[16];

    arguments(int argc, char **argv);
    ~arguments();
};





#endif