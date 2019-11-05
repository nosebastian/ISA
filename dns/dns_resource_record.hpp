#ifndef __DNS_RESOURCE_RECORD_HPP
#define __DNS_RESOURCE_RECORD_HPP

#include "dns_pch.hpp"
#include "dns_subdomain.hpp"

class dns_resource_record : network_data
{
private:
public:
    dns_subdomain name;
    dns_type_t rtype;
    dns_class_t rclass;
    uint16_t length;
    uint32_t ttl;
    std::vector<uint8_t> rdata;

    virtual int encode(uint8_t * buffer, std::size_t max_size);
    virtual int decode(uint8_t *buffer_start, uint8_t * buffer, std::size_t size);
    dns_resource_record();
    ~dns_resource_record();

    void format_rdata(std::ostream& os);

    friend std::ostream& operator<<(std::ostream& os, dns_resource_record& data);
};


#endif