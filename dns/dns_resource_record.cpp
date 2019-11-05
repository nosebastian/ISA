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
int dns_resource_record::decode(uint8_t *buffer_start, uint8_t * buffer, std::size_t size)
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
    memcpy(rdata.data(), &buffer[offset], length);
    offset += length;
    current_size -= length;

    return offset;
}
dns_resource_record::dns_resource_record()
{}
dns_resource_record::~dns_resource_record()
{}


void dns_resource_record::format_rdata(std::ostream& os)
{
    uint16_t len = length;
    os << std::hex << len;
}

std::ostream& operator<<(std::ostream& os, dns_resource_record& data)
{
    os << data.name << ", " << dns_type_to_string(data.rtype) << ", " << dns_class_to_string(data.rclass) << ", " << data.ttl << ", ";
    data.format_rdata(os); 
    return os;
}



