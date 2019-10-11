#include "dns.hpp"



int dns::encode(void * buffer, std::size_t max_size)
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

}
int dns::decode(void *buffer_start, void * buffer, std::size_t size)
{
    
}

void dns::addQuestion(std::string &_name, dns_type_t _type, dns_class_t _class)
{
    dns_question new_question = dns_question(_name, _type, _class);
    _questions.push_back(new_question);
    header.question_count++;
}


dns::dns()
{}

dns::~dns()
{}




