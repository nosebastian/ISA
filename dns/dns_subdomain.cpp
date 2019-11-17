#include "dns_subdomain.hpp"


int dns_subdomain::encode(uint8_t * buffer, std::size_t max_size)
{
    size_t offset = 0;
    size_t current_max_size = max_size;
    //encode each label in vector
    for (auto &&label : labels)
    {
        //if would overflow
        if (label.length() + 1 > current_max_size)
            return -1;
        uint8_t len = label.length();

        memcpy(buffer + offset, &len, sizeof(uint8_t));
        offset += sizeof(uint8_t);
        current_max_size -= sizeof(uint8_t);

        memcpy(buffer + offset, label.c_str(), len);
        offset += len;
        current_max_size -= len;
    }

    uint8_t last_zero = 0;
    if(1 > current_max_size)
        return -1;
    memcpy(buffer + offset, &last_zero, sizeof(uint8_t));
    offset += sizeof(uint8_t);
    current_max_size -= sizeof(uint8_t);

    return offset;
}
int dns_subdomain::decode(const uint8_t *buffer_start, const uint8_t * buffer, std::size_t size)
{
    unsigned char current_char = buffer[0];
    uint8_t current_count = buffer[0];
    std::string current_label;
    size_t i;

    const uint8_t *subdomain_buffer;
    size_t subdomain_max_size;
    bool is_pointer = false;

    //check for pointer
    if((current_char & 0xC0) == 0xC0)
    {
        if( size < 2)
            return -1;
        //Get value refferenced by pointer
        size_t offset = (buffer[0]&(~0xC0));
        offset = (offset << 8) + buffer[1];
        //check for range of value
        if( offset > size + (buffer - buffer_start))
            return -1;
        //set necesary variables
        subdomain_buffer = &buffer_start[offset];
        subdomain_max_size = buffer - subdomain_buffer + size;
        is_pointer = true;
    }
    else
    {
        subdomain_buffer = buffer;
        subdomain_max_size = size;
    }
    
    //go through domain name, 
    //i is counter for progress in subdomain
    for(i = 0; i < subdomain_max_size && current_count != 0;)
    {
        //get count of chars in label
        current_count = current_char = subdomain_buffer[i];
        i++;
        //go through each char in current label
        //j is counter for progress in currently read label
        //j and i are both incremented since cycle is progressing in label and also in domain name
        for (int j = 0; j < current_count && i < subdomain_max_size; i++, j++)
        {
            //read label char
            current_char = subdomain_buffer[i];
            //invalid charater (signalizes end of subdomain but label should continue)
            if(current_char == '\0')
                return -1;
            //add read character to string for current label
            current_label.push_back(current_char);
        }
        if(current_count != 0)
        {
            //label has non 0 length (isn't last byte of domain name) 
            labels.push_back(current_label);
            current_label.clear();
        }
        else
        {
            //reached end of domain name
            //return different values since pointer is only of size 2
            return (is_pointer)?2:i;
        }
    }
    //Main cycle stopped due to reaching max size
    return -1;
}

dns_subdomain::dns_subdomain(const char *name)
{
    size_t max_size = strlen(name);
    /**
     * FSM diagram
     *            +---------+
     *    +------>|SUBDOMAIN|<------+
     *    |       +---------+       |
     *    |            |            |
     *    |            | A-Z, a-z   | "."
     *    |            | 0-9        |
     *    |            V            |
     *    |         F=====F         |
     *    |         |LABEL|---------+
     *    |         F=====F   +----+
     *    |A-Z, a-z | "-"|    |    |
     *    |     0-9 |    V    V    |
     *    |    +----+    +----+ "-"|
     * "."|    |  +----->|HYPH|----+
     *    |    |  |      +----+
     *    |    V  |"-"     | A-Z, a-z
     *    F=======F        | 0-9
     *    |NUM_CHR|<-------+
     *    F=======F
     *     |    ^
     *     |    |
     *     +----+
     *     A-Z, a-z
     *     0-9
     */
    labels.clear();
    std::string label("");
    
    //FSM states definition
    enum {SUBDOMAIN, LABEL, HYPH, NUM_CHR, ERROR};
    int state = SUBDOMAIN;
    for(size_t i = 0; i < max_size && state != ERROR; i++)
    {
        char current_char = name[i];
        switch (state)
        {
        case SUBDOMAIN:
            if(
                (current_char >= 'A' && current_char <= 'Z') || 
                (current_char >= 'a' && current_char <= 'z') ||
                (current_char >= '0' && current_char <= '9')
                )
            {
                label.push_back(current_char);
                state = LABEL;
            }
            else
                state = ERROR;
            break;
        case LABEL:
            if(
                (current_char >= 'A' && current_char <= 'Z') || 
                (current_char >= 'a' && current_char <= 'z') || 
                (current_char >= '0' && current_char <= '9')
                )
            {
                label.push_back(current_char);
                state = NUM_CHR;
            }
            else if(current_char == '-')
            {
                label.push_back(current_char);
                state = HYPH;
            }
            else if(current_char == '.')
            {
                //end of label, push current label
                labels.push_back(label);
                label.clear();
                state = SUBDOMAIN;
            }
            else
                state = ERROR;
            break;
        case NUM_CHR:
            if(
                (current_char >= 'A' && current_char <= 'Z') || 
                (current_char >= 'a' && current_char <= 'z') || 
                (current_char >= '0' && current_char <= '9')
                )
            {
                label.push_back(current_char);
                state = NUM_CHR;
            }
            else if(current_char == '-')
            {
                label.push_back(current_char);
                state = HYPH;
            }
            else if(current_char == '.')
            {
                labels.push_back(label);
                label.clear();
                state = SUBDOMAIN;
            }
            else
                state = ERROR;
            break;
        case HYPH:
            if(
                (current_char >= 'A' && current_char <= 'Z') || 
                (current_char >= 'a' && current_char <= 'z') || 
                (current_char >= '0' && current_char <= '9')
                )
            {
                label.push_back(current_char);
                state = NUM_CHR;
            }
            else if(current_char == '-')
            {
                label.push_back(current_char);
                state = HYPH;
            }
            else
                state = ERROR;
            break;
        default:
            break;
        }
    }

    if(state == LABEL || state == NUM_CHR)
    {
        labels.push_back(label);
        label.clear();
    }
    else
    {
        //ERROR
    }
}

dns_subdomain::dns_subdomain()
{}

dns_subdomain::~dns_subdomain()
{}

std::ostream& operator<<(std::ostream& os, const dns_subdomain& data)
{
    for (auto &&label : data.labels)
    {
        os << label << ".";
    }
    return os;
}

bool dns_subdomain::operator==(const dns_subdomain& op2)
{
    if(op2.labels.size() != labels.size())
        return false;

    for (size_t i = 0; i < op2.labels.size() &&  i < labels.size(); i++)
    {
        if (op2.labels[i] != labels[i])
        {
            return false;
        }
    }
    return true;
}


