#include "UrlFromArguments.hpp"

UrlFromArguments::UrlFromArguments(/* args */)
{
}

UrlFromArguments::UrlFromArguments(arguments &args)
{
    is_problematic = false;
    std::stringstream helper_stream;
    if(args.lookup_type == ARGUMENT_DOMAIN)
    {
        if(args.is_reverse)
            is_problematic = true;
        helper_stream << args.lookup_hostname;
        if (args.is_reverse)
        {
            is_problematic = true;
            if(!args.is_v6)
            {
                helper_stream << "." << "in-addr.arpa";
            }
            else
            {
                helper_stream << "." << "ip6.arpa";
            }
        }
    }
    else if(args.lookup_type == ARGUMENT_IP_V4)
    {
        if(!args.is_reverse)
            is_problematic = true;
        for (int i = 4 - 1; i >= 0; i--)
        {
            helper_stream << args.address[i];
            if (i != 0)
            {
                helper_stream << ".";
            }
        }
        if(!args.is_reverse)
        {
            is_problematic = true;
        }
        else
        {
            if(!args.is_v6)
            {
                helper_stream << "." << "in-addr.arpa";
            }
            else
            {
                is_problematic = true;
                helper_stream << "." << "ip6.arpa";
            }
        }
    }
    else if(args.lookup_type == ARGUMENT_IP_V6)
    {
        for (int i = 16 - 1; i >= 0; i--)
        {
            helper_stream << ((args.address[i]  & 0x0F)) << "." << ((args.address[i] & 0xF0)>> 4);
            if (i != 0)
            {
                helper_stream << ".";
            }
        }
        if(!args.is_reverse)
        {
            is_problematic = true;
        }
        else
        {
            if(!args.is_v6)
            {
                is_problematic = true;
                helper_stream << "." << "in-addr.arpa";
            }
            else
            {
                helper_stream << "." << "ip6.arpa";
            }
        }
    }
    url = helper_stream.str();
}

UrlFromArguments::~UrlFromArguments()
{
}
