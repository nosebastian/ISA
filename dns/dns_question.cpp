#include "dns_question.hpp"

int dns_question::encode(uint8_t * buffer, std::size_t max_size)
{

    size_t offset = 0;
    size_t current_max_size = max_size;
    uint16_t htonsData;
    
    int ret = 0;
    ret = _subdomain.encode(buffer, max_size);
    if(ret == -1)
        return -1;

    offset += ret;
    current_max_size -= ret;

    if(current_max_size < DNS_QUESTION_QCLASS_SIZE + DNS_QUESTION_QTYPE_SIZE)
        return -1;

    htonsData = htons(qtype);
    memcpy(buffer + offset, &htonsData, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    
    htonsData = htons(qclass);
    memcpy(buffer + offset, &htonsData, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    return offset;
}
int dns_question::decode(uint8_t *buffer_start, uint8_t * buffer, std::size_t size)
{
}
dns_question::dns_question(char *_name, dns_type_t _type, dns_class_t _class)
{
    name = _name;
    _subdomain = dns_subdomain(name.c_str());
    qtype = _type;
    qclass = _class;
}
dns_question::dns_question(std::string &_name, dns_type_t _type, dns_class_t _class)
{
    name = _name;
    _subdomain = dns_subdomain(name.c_str());
    qtype = _type;
    qclass = _class;
}

dns_question::dns_question()
{

}
dns_question::~dns_question()
{

}