#ifndef __DNS_ENUMS_HPP

#define __DNS_ENUMS_HPP

/**
 * Definition of all possible op codes
 */

typedef enum {
    DNS_QUERY = 0,
    DNS_INVERSE_QUERY = 1,
    DNS_STATUS = 2
} dns_opcode_t;

/**
 * Definition of all possible response codes
 */

typedef enum {
    DNS_RESPONSE_OK = 0,
    DNS_RESPONSE_FORMAT_ERROR = 1,
    DNS_RESPONSE_SERVER_ERROR = 2,
    DNS_RESPONSE_NAME_ERROR = 3,
    DNS_RESPONSE_IMPLEMENTATION_ERROR = 4,
    DNS_RESPONSE_REFUSED_ERROR = 5,
} dns_response_code_t;


/**
 * Definition of all possible resource record types
 */
typedef enum {
    //IP v4
    DNS_A               = 1, //a host address
    DNS_NS              = 2, //an authoritative name server
    DNS_MD              = 3, //a mail destination (Obsolete - use MX)
    DNS_MF              = 4, //a mail forwarder (Obsolete - use MX)
    DNS_CNAME           = 5, //the canonical name for an alias
    DNS_SOA             = 6, //marks the start of a zone of authority
    DNS_MB              = 7, //a mailbox domain name (EXPERIMENTAL)
    DNS_MG              = 8, //a mail group member (EXPERIMENTAL)
    DNS_MR              = 9, //a mail rename domain name (EXPERIMENTAL)
    DNS_NULL            = 10, //a null RR (EXPERIMENTAL)
    DNS_WKS             = 11, //a well known service description
    DNS_PTR             = 12, //a domain name pointer
    DNS_HINFO           = 13, //host information
    DNS_MINFO           = 14, //mailbox or mail list information
    DNS_MX              = 15, //mail exchange
    DNS_TXT             = 16, //text strings

    //IP v6

    DNS_AAAA            = 28, //a host address 

    // Additional question types

    DNS_Q_AXFR          = 252, //A request for a transfer of an entire zone
    DNS_Q_MAILB         = 253, //A request for mailbox-related records (MB, MG or MR)
    DNS_Q_MAILA         = 254, //A request for mail agent RRs (Obsolete - see MX)
    DNS_Q_ALL           = 255, //A request for all records

    // For an unknown type

    DNS_UNKNOWN          = 127,
} dns_type_t;

/**
 * Definition of all possible record classes
 */
typedef enum {
    DNS_CLASS_IN              = 1, //the Internet
    DNS_CLASS_CS              = 2, //the CSNET class (Obsolete - used only for examples in some obsolete RFCs)
    DNS_CLASS_CH              = 3, //the CHAOS class
    DNS_CLASS_HS              = 4, //Hesiod [Dyer 87]
    
    //Additional question class
    DNS_CLASS_Q_ANY           = 255, //any class
} dns_class_t;

const char * dns_type_to_string(dns_type_t type);
const char * dns_class_to_string(dns_class_t dns_class);



#endif