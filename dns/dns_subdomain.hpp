#ifndef __DNS_LABEL_HPP
#define __DNS_LABEL_HPP

#include "dns_pch.hpp"

class dns_subdomain : network_data
{
private:
    std::vector<std::string> _labels;
public:
    virtual int encode(uint8_t * buffer, std::size_t max_size);
    virtual int decode(uint8_t *buffer_start, uint8_t * buffer, std::size_t size);
    dns_subdomain(const char *name);
    dns_subdomain();
    ~dns_subdomain();
};



#endif