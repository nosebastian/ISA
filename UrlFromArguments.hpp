#ifndef __URLFROMARGUMENTS_HPP
#define __URLFROMARGUMENTS_HPP

#include "arguments.hpp"

#include <string>
#include <sstream>

class UrlFromArguments
{
private:
    /* data */
public:
    std::string url;
    bool is_problematic;
    UrlFromArguments(/* args */);
    UrlFromArguments(arguments &args);
    ~UrlFromArguments();
};

#endif
