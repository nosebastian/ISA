CC=g++
CFLAGS=-g -std=c++11 -Wall
LDFLAGS=


main: main.o network_data.o dns/dns.o dns/dns_header.o dns/dns_question.o dns/dns_resource_record.o dns/dns_subdomain.o dns/dns_enums.o arguments.o UrlFromArguments.o
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@


main.cpp: network_data.hpp dns/dns.hpp

network_data.cpp: %.cpp : %.hpp
arguments.cpp: %.cpp : %.hpp
UrlFromArguments.cpp: %.cpp : %.hpp

dns/dns.cpp:  %.cpp : %.hpp
dns/dns_header.cpp:  %.cpp : %.hpp
dns/dns_question.cpp:  %.cpp : %.hpp
dns/dns_resource_record.cpp:  %.cpp : %.hpp
dns/dns_subdomain.cpp:  %.cpp : %.hpp
dns/dns_enums.cpp: %.cpp : %.hpp

dns/dns.hpp: dns/dns_pch.hpp dns/dns_header.hpp dns/dns_question.hpp dns/dns_resource_record.hpp
dns/dns_header.hpp: dns/dns_pch.hpp
dns/dns_question.hpp: dns/dns_pch.hpp
dns/dns_resource_record.hpp: dns/dns_pch.hpp dns/dns_subdomain.hpp
dns/dns_subdomain.hpp: dns/dns_pch.hpp
dns/dns_pch.hpp: network_data.hpp dns/dns_defines.hpp


clean:
	rm -rf dns/*.o dns/*.gch *.o main