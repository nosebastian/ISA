#include "dns_resource_record.hpp"


int dns_resource_record::encode(uint8_t * buffer, std::size_t max_size)
{
    /*  
                         1 1 1 1 1 1
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    /                               /
    /             NAME              /
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |             TYPE              |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |             CLASS             |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |              TTL              |
    |                               |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |           RDLENGTH            |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-|
    /                               /
    /             RDATA             /
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
    */
   return 0;
}
int dns_resource_record::decode(const uint8_t *buffer_start, const uint8_t * buffer, std::size_t size)
{
    size_t offset = 0;
    size_t current_size = size;

    int ret = 0;
    ret = name.decode(buffer_start, buffer, current_size);
    
    if(ret == -1)
        return -1;
    offset += ret;
    current_size -= ret;

    if (current_size < sizeof(uint16_t)*3 + sizeof(uint32_t))
        return -1;
    
    uint16_t ntohs_data;
    uint32_t ntohl_data;

    memcpy(&ntohs_data, &buffer[offset], sizeof(uint16_t));
    rtype = (dns_type_t)ntohs(ntohs_data);
    offset += sizeof(uint16_t);
    current_size -= sizeof(uint16_t);

    memcpy(&ntohs_data, &buffer[offset], sizeof(uint16_t));
    rclass = (dns_class_t)ntohs(ntohs_data);
    offset += sizeof(uint16_t);
    current_size -= sizeof(uint16_t);

    memcpy(&ntohl_data, &buffer[offset], sizeof(uint32_t));
    ttl = ntohl(ntohl_data);
    offset += sizeof(uint32_t);
    current_size -= sizeof(uint32_t);

    memcpy(&ntohs_data, &buffer[offset], sizeof(uint16_t));
    length = ntohs(ntohs_data);
    offset += sizeof(uint16_t);
    current_size -= sizeof(uint16_t);

    rdata.resize(length);
    if (current_size < length)
        return -1;

    if(rtype == DNS_CNAME)
    {
        ret = CNAME_subdomain.decode(buffer_start, buffer, length);
        if(ret == -1 || ret != length)
            return -1;
        offset += ret;
        current_size -= ret;
    }
    else if ((rtype == DNS_A && length == 4)||(rtype == DNS_AAAA && length == 16)|| rtype != DNS_AAAA || ret != DNS_A)
    {
        memcpy(rdata.data(), &buffer[offset], length);
        offset += length;
        current_size -= length;
    }
    else
    {
        return -1;
    }

    return offset;
}
dns_resource_record::dns_resource_record()
{}
dns_resource_record::~dns_resource_record()
{}

std::ostream& dns_resource_record::format_rdata(const dns_resource_record& data, std::ostream& os)
{
    uint16_t len = data.length;
    switch (data.rtype)
    {
    case DNS_A:
        os << static_cast<int>(data.rdata[0]) << "." << static_cast<int>(data.rdata[1]) << "." << static_cast<int>(data.rdata[2]) << "." << static_cast<int>(data.rdata[3]);
        break;
    case DNS_AAAA:
        for (size_t i = 0; i < 8; i++)
        {
            if(data.rdata[2*i] != 0)
                os << std::hex << static_cast<int>(data.rdata[2*i]);
            if(data.rdata[2*i + 1] <= 0xF && data.rdata[2*i] != 0)
                os << "0";
            os << std::hex << static_cast<int>(data.rdata[2*i + 1]);
            if (i != 7)
                os << ":";
        }
        break;
    case DNS_CNAME:
        os << data.CNAME_subdomain;
        break;
    default:
        os << "0x"<< std::hex << len;
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const dns_resource_record& data)
{
    os << data.name << ", " << dns_type_to_string(data.rtype) << ", " << dns_class_to_string(data.rclass) << ", " << data.ttl << ", ";
    return data.format_rdata(data, os); 
}

bool dns_resource_record::operator==(const dns_resource_record &op2)
{
    if(!(name == op2.name))
        return false;
    if(rtype != op2.rtype)
        return false;
    if(rclass != op2.rclass)
        return false;
    if(length != op2.length)
        return false;
    if(ttl != op2.ttl)
        return false;
    
    switch (rtype)
    {
    case DNS_A:
        for (size_t i = 0; i < 4; i++)
        {
            if(op2.A[i] != A[i])
                return false;
        }
        break;
    case DNS_AAAA:
        for (size_t i = 0; i < 16; i++)
        {
            if(op2.AAAA[i] != AAAA[i])
                return false;
        }
        break;
    case DNS_CNAME:
        if(!(CNAME_subdomain == op2.CNAME_subdomain))
            return false;
        break;
    default:
        break;
    }
    return true;
}




