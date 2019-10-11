#ifndef __DNS_RDATA_HPP

#define __DNS_RDATA_HPP

#include "dns_pch.hpp"

struct dns_rData_A : network_data {
    uint8_t address[4];
};

struct dns_rData_AAAA : network_data {
    uint8_t address[16];
};

struct dns_rData_CNAME : network_data {
    std::string cname;
};

struct dns_rData_HINFO : network_data {
    std::string cpu;
    std::string os;
};

struct dns_rData_MX : network_data {
    uint16_t preference;
    std::string exchange;
};

struct dns_rData_NS : network_data {
    std::string nsdname;
};

#endif