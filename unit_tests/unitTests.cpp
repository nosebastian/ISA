#include <vector>
#include <iostream>

#include <cstring>
#include <cassert>

#include "../arguments.hpp"
#include "../UrlFromArguments.hpp"
#include "../network_data.hpp"
#include "../dns/dns.hpp"
#include "../dns/dns_enums.hpp"
#include "../dns/dns_header.hpp"
#include "../dns/dns_question.hpp"
#include "../dns/dns_resource_record.hpp"
#include "../dns/dns_subdomain.hpp"

void testSubdomainDecode(const uint8_t * data_to_decode, dns_subdomain &data_to_compare, size_t size_of_data)
{
    dns_subdomain decoded_data;
    decoded_data.decode(data_to_decode, data_to_decode, size_of_data);
    assert(data_to_compare == decoded_data);
}
void testQuestionDecode(const uint8_t * data_to_decode, dns_question &data_to_compare, size_t size_of_data)
{
    dns_question decoded_data;
    decoded_data.decode(data_to_decode, data_to_decode, size_of_data);
    assert(data_to_compare == decoded_data);
}
void testResourceRecordDecode(const uint8_t * data_to_decode, dns_resource_record &data_to_compare, size_t size_of_data)
{
    dns_resource_record decoded_data;
    decoded_data.decode(data_to_decode, data_to_decode, size_of_data);
    assert(data_to_compare == decoded_data);
}
void testHeaderDecode(const uint8_t * data_to_decode, dns_header &data_to_compare, size_t size_of_data)
{
    dns_header decoded_data;
    decoded_data.decode(data_to_decode, data_to_decode, size_of_data);
    assert(data_to_compare == decoded_data);
}
void testDnsDecode(const uint8_t * data_to_decode, dns &data_to_compare, size_t size_of_data)
{
    dns decoded_data;
    decoded_data.decode(data_to_decode, data_to_decode, size_of_data);
    assert(data_to_compare == decoded_data);
}
void testEncode(const uint8_t * data_to_compare, network_data &data_to_encode, size_t size_of_data)
{
    std::vector<uint8_t> encoded_buffer(size_of_data); 
    int ret = data_to_encode.encode(&encoded_buffer[0], size_of_data);
    assert(ret != -1);
    assert(ret == size_of_data);
    assert(memcmp(&encoded_buffer[0], data_to_compare, size_of_data) == 0);
}

int main()
{
    std::cout << "-- Running UnitTests" << std::endl;









    return 0;
}