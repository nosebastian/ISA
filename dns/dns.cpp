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
int dns::decode(const uint8_t *buffer_start, const uint8_t * buffer, std::size_t size)
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

    _questions.clear();
    for (size_t i = 0; i < header.question_count; i++)
    {
        ret = current_question.decode(buffer_start, &buffer[offset], current_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_size -= ret;
        _questions.push_back(current_question);
    }

    dns_resource_record current_rr;
    _answers.clear();
    for (size_t i = 0; i < header.answer_count; i++)
    {
        ret = current_rr.decode(buffer_start, &buffer[offset], current_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_size -= ret;
        _answers.push_back(current_rr);
    }
    _authorities.clear();
    for (size_t i = 0; i < header.nameserver_count; i++)
    {
        ret = current_rr.decode(buffer_start, &buffer[offset], current_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_size -= ret;
        _authorities.push_back(current_rr);
    }
    _additionals.clear();
    for (size_t i = 0; i < header.additional_count; i++)
    {
        ret = current_rr.decode(buffer_start, &buffer[offset], current_size);
        if(ret == -1)
            return -1;
        offset += ret;
        current_size -= ret;
        _additionals.push_back(current_rr);
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
    for (auto &&question : data._questions)
    {
        os << " " << question << std::endl;
    }
    os << "Answer section (" << data.header.answer_count << ")" << std::endl;
    for (auto &&answer : data._answers)
    {
        os << " " << answer << std::endl;
    }
    os << "Authority section (" << data.header.nameserver_count << ")" << std::endl;
    for (auto &&authority : data._authorities)
    {
        os << " " << authority << std::endl;
    }
    os << "Additional section (" << data.header.additional_count << ")" << std::endl;
    for (auto &&additional : data._additionals)
    {
        os << " " << additional << std::endl;
    }
    return os;
}

bool dns::operator==(const dns &op2)
{
    if(_questions.size() != op2._questions.size())
        return false;
    if(_answers.size() != op2._answers.size())
        return false;
    if(_authorities.size() != op2._authorities.size())
        return false;
    if(_additionals.size() != op2._additionals.size())
        return false;
    for (size_t i = 0; i < _questions.size() && i < op2._questions.size(); i++)
    {
        if(!(_questions[i] == op2._questions[i]))
            return false;
    }
    for (size_t i = 0; i < _answers.size() && i < op2._answers.size(); i++)
    {
        if(!(_answers[i] == op2._answers[i]))
            return false;
    }
    for (size_t i = 0; i < _authorities.size() && i < op2._authorities.size(); i++)
    {
        if(!(_authorities[i] == op2._authorities[i]))
            return false;
    }
    for (size_t i = 0; i < _additionals.size() && i < op2._additionals.size(); i++)
    {
        if(!(_additionals[i] == op2._additionals[i]))
            return false;
    }
    if(!(header == op2.header))
        return false;
    return true;
}





