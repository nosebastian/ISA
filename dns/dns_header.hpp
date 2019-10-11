#ifndef __DNS_HEADER_HPP

#define __DNS_HEADER_HPP

#include "dns_pch.hpp"

class dns_header : network_data
{
private:
    uint16_t _flags;
    uint8_t _buffer[DNS_HEADER_SIZE];
    void _encodeFlags();
    void _decodeFlags();
public:
    uint16_t id;
    bool is_response;
    dns_opcode_t opcode;
    bool is_authoritative_answer;
    bool is_truncated;
    bool recursion_desired;
    bool recursion_available;
    dns_response_code_t response_code;


    uint16_t question_count;
    uint16_t answer_count;
    uint16_t nameserver_count;
    uint16_t additional_count;

    void createQueryHeader();

    virtual int encode(void * buffer, std::size_t max_size);
    virtual int decode(void *buffer_start, void * buffer, std::size_t size);
    dns_header();
    ~dns_header();
};


#endif