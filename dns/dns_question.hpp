#ifndef __DNS_QUESTION_HPP

#define __DNS_QUESTION_HPP

#include "dns_pch.hpp"
#include "dns_subdomain.hpp"


#define DNS_QUESTION_QTYPE_SIZE 2
#define DNS_QUESTION_QCLASS_SIZE 2

class dns_question : network_data
{
private:
public:
    dns_subdomain subdomain;
    std::string name;
    dns_type_t qtype;
    dns_class_t qclass;

    virtual int encode(uint8_t * buffer, std::size_t max_size);
    virtual int decode(const uint8_t *buffer_start, const uint8_t * buffer, std::size_t size);
    dns_question(char *_name, dns_type_t _type, dns_class_t _class);
    dns_question(std::string &_name, dns_type_t _type, dns_class_t _class);
    dns_question();
    ~dns_question();
    
    friend std::ostream& operator<<(std::ostream& os, const dns_question& data);

    bool operator==(const dns_question& op2);
};


#endif