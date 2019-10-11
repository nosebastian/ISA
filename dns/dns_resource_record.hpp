#ifndef __DNS_RESOURCE_RECORD_HPP
#define __DNS_RESOURCE_RECORD_HPP

#include "dns_pch.hpp"
#include "dns_rdata.hpp"

class dns_resource_record : network_data
{
private:
public:
    //std::variant<dns_rData_A, dns_rData_AAAA, dns_rData_CNAME, dns_rData_HINFO, dns_rData_MX, dns_rData_NS> rData;
    
    virtual int encode(void * buffer, std::size_t max_size);
    virtual int decode(void * buffer, std::size_t size);
    dns_resource_record();
    ~dns_resource_record();
};


#endif