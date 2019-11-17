#ifndef __DNS_LABEL_HPP
#define __DNS_LABEL_HPP

#include "dns_pch.hpp"

class dns_subdomain : network_data
{
private:
public:
    std::vector<std::string> labels;
    virtual int encode(uint8_t * buffer, std::size_t max_size);
    virtual int decode(const uint8_t *buffer_start, const uint8_t * buffer, std::size_t size);
    dns_subdomain(const char *name);
    dns_subdomain();
    ~dns_subdomain();

    friend std::ostream& operator<<(std::ostream& os, const dns_subdomain& data);
    bool operator==(const dns_subdomain& op2);
};



#endif