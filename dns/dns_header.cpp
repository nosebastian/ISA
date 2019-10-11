#include "dns_header.hpp"


void dns_header::_encodeFlags()
{
    /* 
                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+ 
    */
    _flags  = 0x0000;
    _flags |= (is_response)? 0x8000:0x0000;
    switch (opcode)
    {
    case DNS_QUERY:
        _flags |= 0x0000;
        break;
    case DNS_INVERSE_QUERY:
        _flags |= 0x0800;
        break;
    case DNS_STATUS:
        _flags |= 0x1000;
        break;
    
    default:
        //not supported
        break;
    }

    _flags |= (is_authoritative_answer)?0x0400:0x0000;
    _flags |= (is_truncated)?0x0200:0x0000;
    _flags |= (recursion_desired)?0x0100:0x0000;
    _flags |= (recursion_available)?0x0080:0x0000;
    
    switch (response_code)
    {
    case DNS_RESPONSE_OK:
        _flags |= 0x0000;
        break;
    case DNS_RESPONSE_FORMAT_ERROR:
        _flags |= 0x0001;
        break;
    case DNS_RESPONSE_SERVER_ERROR:
        _flags |= 0x0002;
        break;
    case DNS_RESPONSE_NAME_ERROR:
        _flags |= 0x0003;
        break;
    case DNS_RESPONSE_IMPLEMENTATION_ERROR:
        _flags |= 0x0004;
        break;
    case DNS_RESPONSE_REFUSED_ERROR:
        _flags |= 0x0005;
        break;
    
    default:
        //not supported
        break;
    }
}
void dns_header::_decodeFlags()
{
    is_response = _flags & 0x8000 == 0x8000;
    switch (_flags & 0x7800)
    {
    case 0x0000:
        opcode = DNS_QUERY;
        break;
    case 0x0800:
        opcode = DNS_INVERSE_QUERY;
        break;
    case 0x1000:
        opcode = DNS_STATUS;
        break;
    
    default:
        //not supported
        break;
    }

    is_authoritative_answer = _flags & 0x0400 == 0x0400;
    is_truncated = _flags & 0x0200 == 0x0200;
    recursion_desired = _flags & 0x0100 == 0x0100;
    recursion_available = _flags & 0x0080 == 0x0080;
    
    switch (_flags & 0x000f)
    {
    case 0x0000:
        response_code = DNS_RESPONSE_OK;
        break;
    case 0x0001:
        response_code = DNS_RESPONSE_FORMAT_ERROR;
        break;
    case 0x0002:
        response_code = DNS_RESPONSE_SERVER_ERROR;
        break;
    case 0x0003:
        response_code = DNS_RESPONSE_NAME_ERROR;
        break;
    case 0x0004:
        response_code = DNS_RESPONSE_IMPLEMENTATION_ERROR;
        break;
    case 0x0005:
        response_code = DNS_RESPONSE_REFUSED_ERROR;
        break;
    
    default:
        //not supported
        break;
    }
}

void dns_header::createQueryHeader()
{
    
}
int dns_header::encode(void * buffer, std::size_t max_size)
{
    /*
                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      ID                       |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    QDCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ANCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    NSCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ARCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+ 
    */
    if(max_size < sizeof(_buffer))
        return -1;

    memset(buffer, 0, sizeof(_buffer));
    _encodeFlags();

    size_t offset = 0;

    uint16_t htonsData = htons(id);
    memcpy(buffer + offset, &htonsData, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    htonsData = htons(_flags);
    memcpy(buffer + offset, &htonsData, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    htonsData = htons(question_count);
    memcpy(buffer + offset, &htonsData, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    htonsData = htons(answer_count);
    memcpy(buffer + offset, &htonsData, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    htonsData = htons(nameserver_count);
    memcpy(buffer + offset, &htonsData, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    htonsData = htons(additional_count);
    memcpy(buffer + offset, &htonsData, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    memcpy(_buffer, buffer, sizeof(_buffer));
    
    return offset;
}
int dns_header::decode(void * buffer, std::size_t size)
{
    if(size < sizeof(_buffer))
        return -1;

    size_t offset = 0;

    uint16_t ntohsData;

    memcpy(&ntohsData, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    id = ntohs(ntohsData);

    memcpy(&ntohsData, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    _flags = ntohs(ntohsData);

    memcpy(&ntohsData, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    question_count = ntohs(ntohsData);

    memcpy(&ntohsData, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    answer_count = ntohs(ntohsData);

    memcpy(&ntohsData, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    nameserver_count = ntohs(ntohsData);

    memcpy(&ntohsData, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    additional_count = ntohs(ntohsData);

    memcpy(_buffer, buffer, sizeof(_buffer));
    _decodeFlags();

    return offset;
}
dns_header::dns_header()
{
    id = 0;
    is_response = false;
    opcode = DNS_QUERY;
    is_authoritative_answer = false;
    is_truncated = false;
    recursion_desired = false;
    recursion_available = false;
    response_code = DNS_RESPONSE_OK;
    question_count = 0;
    answer_count = 0;
    nameserver_count = 0;
    additional_count = 0;
}
dns_header::~dns_header()
{}
