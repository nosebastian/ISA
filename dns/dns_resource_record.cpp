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
}
int dns_resource_record::decode(uint8_t *buffer_start, uint8_t * buffer, std::size_t size)
{

}
dns_resource_record::dns_resource_record()
{}
dns_resource_record::~dns_resource_record()
{}