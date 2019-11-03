#ifndef __DNS_RESOURCE_RECORD_HPP
#define __DNS_RESOURCE_RECORD_HPP

#include "dns_pch.hpp"
#include "dns_rdata.hpp"

class dns_resource_record : network_data
{
private:
public:
    dns_type_t type;
    dns_type_t rclass;
    uint16_t length;
    uint16_t time_to_live;


    virtual int encode(uint8_t * buffer, std::size_t max_size);
    virtual int decode(uint8_t *buffer_start, uint8_t * buffer, std::size_t size);
    dns_resource_record();
    ~dns_resource_record();
};


#endif