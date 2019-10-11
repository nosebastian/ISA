#ifndef __DNS_HPP

#define __DNS_HPP

#include "dns_pch.hpp"
#include "dns_header.hpp"
#include "dns_resource_record.hpp"
#include "dns_question.hpp"


class dns : network_data
{
private:
    std::vector<dns_question> _questions;
    std::vector<dns_resource_record> _answers;
    std::vector<dns_resource_record> _authorities;
    std::vector<dns_resource_record> _additionals;
    uint8_t _buffer[DNS_MAX_SIZE];
public:
    dns_header header;
    void addQuestion(std::string &_name, dns_type_t _type, dns_class_t _class);
    virtual int encode(void * buffer, std::size_t max_size);
    virtual int decode(void *buffer_start, void * buffer, std::size_t size);
    dns();
    ~dns();
};

#endif
