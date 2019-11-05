#include "dns.hpp"



int dns::encode(uint8_t * buffer, std::size_t max_size)
{
    size_t current_max_size = max_size;
    size_t offset = 0;
    int ret = 0;

    ret = header.encode(buffer + offset, current_max_size);
    if(ret == -1)
        return -1;
    offset += ret;
    current_max_size -= ret;

    for (auto &&question : _questions)
    {
        ret = question.encode(buffer + offset, current_max_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_max_size -= ret;
    }
    return offset;
}
int dns::decode(uint8_t *buffer_start, uint8_t * buffer, std::size_t size)
{
    size_t current_size = size;
    size_t offset = 0;
    int ret = 0;

    ret = header.decode(buffer_start, buffer + offset, current_size);
    if(ret == -1)
        return -1;
    offset += ret;
    current_size -= ret;

    dns_question current_question;

    for (size_t i = 0; i < header.question_count; i++)
    {
        ret = current_question.decode(buffer_start, &buffer[offset], current_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_size -= ret;
    }

    dns_resource_record current_rr;

    for (size_t i = 0; i < header.answer_count; i++)
    {
        ret = current_rr.decode(buffer_start, &buffer[offset], current_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_size -= ret;
    }
    for (size_t i = 0; i < header.nameserver_count; i++)
    {
        ret = current_rr.decode(buffer_start, &buffer[offset], current_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_size -= ret;
    }
    for (size_t i = 0; i < header.additional_count; i++)
    {
        ret = current_rr.decode(buffer_start, &buffer[offset], current_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_size -= ret;
    }
    return offset;
}

void dns::addQuestion(std::string &_name, dns_type_t _type, dns_class_t _class)
{
    dns_question new_question = dns_question(_name, _type, _class);
    _questions.push_back(new_question);
    header.question_count = header.question_count + 1;
}


dns::dns()
{}

dns::~dns()
{}

std::ostream& operator<<(std::ostream& os, const dns& data)
{
    os  << data.header
        << "Question section (" << data.header.question_count << ")" << std::endl;

    os << "Answer section (" << data.header.answer_count << ")" << std::endl;
    os << "Authority section (" << data.header.nameserver_count << ")" << std::endl;
    os << "Additional section (" << data.header.additional_count << ")" << std::endl;
    return os;
}




