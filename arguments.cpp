#include "arguments.hpp"


void arguments::_parse_lookup_hostname()
{
    lookup_type = ARGUMENT_DOMAIN;
    int ret = inet_pton(AF_INET, lookup_hostname.c_str(), address);
    if (ret == 0)
    {
        lookup_type = ARGUMENT_IP_V4;
        return;
    }
    ret = inet_pton(AF_INET6, lookup_hostname.c_str(), address);
    if (ret == 0)
    {
        lookup_type = ARGUMENT_IP_V6;
        return;
    }
}

arguments::arguments(int argc, char **argv)
{
    arguments_ok = true;
    is_recursive = false;
    is_v6 = false;
    is_reverse = false;

    bool server_hostname_defined = false;
    bool port_number_defined = false;
    bool expect_server_hostname = false;
    bool expect_port_number = false;
    bool expect_lookup_hostname = true;

    for (int i = 1; i < argc; i++)
    {
        std::string current_argument(argv[i]);

        if(current_argument.compare("-r") == 0 && is_recursive == false && expect_server_hostname == false && expect_port_number == false)
        {
            is_recursive = true;
        }
        else if(current_argument.compare("-x") == 0 && is_reverse == false && expect_server_hostname == false && expect_port_number == false)
        {
            is_reverse = true;
        }
        else if(current_argument.compare("-6") == 0 && is_v6 == false && expect_server_hostname == false && expect_port_number == false)
        {
            is_v6 = true;
        }
        else if(current_argument.compare("-s") == 0 && server_hostname_defined == false  && expect_server_hostname == false && expect_port_number == false)
        {
            server_hostname_defined = true;
            expect_server_hostname = true;
        }
        else if(current_argument.compare("-p") == 0 && port_number_defined == false  && expect_server_hostname == false && expect_port_number == false)
        {
            port_number_defined = true;
            expect_port_number = true;
        }
        else if(expect_port_number == true)
        {
            port_number = current_argument;
            expect_port_number = false;
        }
        else if(expect_server_hostname == true )
        {
            server_hostname = current_argument;
            expect_server_hostname = false;
        }
        else if(expect_lookup_hostname == true)
        {
            lookup_hostname = current_argument;
            expect_lookup_hostname = false;
        }
        else
        {
            arguments_ok = false;
        }
    }

    if(expect_lookup_hostname == true || expect_server_hostname == true || server_hostname_defined == false)
    {
        arguments_ok = false;
    }

    if(!port_number_defined)
    {
        port_number = "53";
    }
}

arguments::~arguments()
{
}

