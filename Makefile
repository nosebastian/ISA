CC=g++
CFLAGS=-g -std=c++11
LDFLAGS=


main: main.o network_data.o dns/dns.o dns/dns_header.o dns/dns_question.o dns/dns_rdata.o dns/dns_resource_record.o dns/dns_subdomain.o
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@


main.cpp: network_data.hpp dns/dns.hpp

network_data.cpp: %.cpp : %.hpp

dns/dns.cpp:  %.cpp : %.hpp
dns/dns_header.cpp:  %.cpp : %.hpp
dns/dns_question.cpp:  %.cpp : %.hpp
dns/dns_rdata.cpp:  %.cpp : %.hpp
dns/dns_resource_record.cpp:  %.cpp : %.hpp
dns/dns_subdomain.cpp:  %.cpp : %.hpp

dns/dns.hpp: dns/dns_pch.hpp dns/dns_header.hpp dns/dns_question.hpp dns/dns_rdata.hpp dns/dns_resource_record.hpp
dns/dns_header.hpp: dns/dns_pch.hpp
dns/dns_question.hpp: dns/dns_pch.hpp
dns/dns_rdata.hpp: dns/dns_pch.hpp 
dns/dns_resource_record.hpp: dns/dns_pch.hpp dns/dns_rdata.hpp
dns/dns_subdomain.hpp: dns/dns_pch.hpp
dns/dns_pch.hpp: network_data.hpp dns/dns_defines.hpp

clean:
	rm -rf dns/*.o dns/*.gch *.o main