#include "dns_subdomain.hpp"


int dns_subdomain::encode(uint8_t * buffer, std::size_t max_size)
{
    size_t offset = 0;
    size_t current_max_size = max_size;
    for (auto &&label : _labels)
    {
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
int dns_subdomain::decode(uint8_t *buffer_start, uint8_t * buffer, std::size_t size)
{
    unsigned char current_char;
    uint8_t current_count;
    std::string current_label;
    size_t i;
    
    for(i = 0; i < size && current_count != 0; i++)
    {
        current_count = current_char = (buffer)[i];
        i++;

        if(current_char == 0xC0)
        {
            
        }

        for (int j = 0; j < current_count && i < size; i++, j++)
        {
            current_char = buffer[i];
            if(current_char == '\0')
                return -1;
            current_label.push_back(current_char);
        }
        if(current_count != 0)
        {
            _labels.push_back(current_label);
            current_label.clear();
        }
        else
            return i;
    }
    return -1;
}

dns_subdomain::dns_subdomain(const char *name)
{
    size_t max_size = strlen(name);
    /**
     *            +---------+
     *    +------>|SUBDOMAIN|<------+
     *    |       +---------+       |
     *    |            |            |
     *    |            | A-Z, a-z   | "."
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
    _labels.clear();
    std::string label("");
    
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
                (current_char >= 'a' && current_char <= 'z')
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
                _labels.push_back(label);
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
                _labels.push_back(label);
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
        _labels.push_back(label);
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
