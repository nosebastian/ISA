#ifndef __DNS_QUESTION_HPP

#define __DNS_QUESTION_HPP

#include "dns_pch.hpp"
#include "dns_subdomain.hpp"


#define DNS_QUESTION_QTYPE_SIZE 2
#define DNS_QUESTION_QCLASS_SIZE 2

class dns_question : network_data
{
private:
    dns_subdomain _subdomain;
public:
    std::string name;
    dns_type_t qtype;
    dns_class_t qclass;

    virtual int encode(void * buffer, std::size_t max_size);
    virtual int decode(void * buffer, std::size_t size);
    dns_question(char *_name, dns_type_t _type, dns_class_t _class);
    dns_question(std::string &_name, dns_type_t _type, dns_class_t _class);
    dns_question();
    ~dns_question();
};


#endif