#include "dns_enums.hpp"

const char * dns_type_string[] = {
    "A",
    "NS",
    "MD",
    "MF",
    "CNAME",
    "SOA",
    "MB",
    "MG",
    "MR",
    "NULL",
    "WKS",
    "PTR",
    "HINFO",
    "MINFO",
    "MX",
    "TXT",
    "AAAA",
    "AXFR",
    "MAILB",
    "MAILA",
    "ALL",
    "UNKNOWN",
};

const char * dns_class_string[] = {
    "IN",
    "CS",
    "CH",
    "HS",
    "ANY",
};

const char * dns_type_to_string(dns_type_t type)
{
    switch (type)
    {
    case DNS_A:
        return dns_type_string[0];
        break;
    case DNS_NS:
        return dns_type_string[1];
        break;
    case DNS_MD:
        return dns_type_string[2];
        break;
    case DNS_MF:
        return dns_type_string[3];
        break;
    case DNS_CNAME:
        return dns_type_string[4];
        break;
    case DNS_SOA:
        return dns_type_string[5];
        break;
    case DNS_MB:
        return dns_type_string[6];
        break;
    case DNS_MG:
        return dns_type_string[7];
        break;
    case DNS_MR:
        return dns_type_string[8];
        break;
    case DNS_NULL:
        return dns_type_string[9];
        break;
    case DNS_WKS:
        return dns_type_string[10];
        break;
    case DNS_PTR:
        return dns_type_string[11];
        break;
    case DNS_HINFO:
        return dns_type_string[12];
        break;
    case DNS_MINFO:
        return dns_type_string[13];
        break;
    case DNS_MX:
        return dns_type_string[14];
        break;
    case DNS_TXT:
        return dns_type_string[15];
        break;
    case DNS_AAAA:
        return dns_type_string[16];
        break;
    case DNS_Q_AXFR:
        return dns_type_string[17];
        break;
    case DNS_Q_MAILB:
        return dns_type_string[18];
        break;
    case DNS_Q_MAILA:
        return dns_type_string[19];
        break;
    case DNS_Q_ALL:
        return dns_type_string[20];
        break;
    case DNS_UNKNOWN:
        return dns_type_string[21];
        break;
    default:
        return dns_type_string[21];
        break;
    }
}
const char * dns_class_to_string(dns_class_t dns_class)
{
    switch (dns_class)
    {
    case DNS_CLASS_IN:
        return dns_class_string[0];
        break;
    case DNS_CLASS_CS:
        return dns_class_string[2];
        break;
    case DNS_CLASS_CH:
        return dns_class_string[3];
        break;
    case DNS_CLASS_HS:
        return dns_class_string[4];
        break;
    case DNS_CLASS_Q_ANY:
        return dns_class_string[5];
        break;
    default:
        return dns_class_string[5];
        break;
    }
}