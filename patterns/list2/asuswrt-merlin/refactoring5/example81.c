#ifdef RTCONFIG_IPV6
if (ip && *ip && inet_addr_(ip) != INADDR_ANY)
					fprintf(fp, "-A INPUT -i %s ! -s %s -p icmp --icmp-type 8 -j %s\n", wan_if, ip, logdrop);
				else
#endif
				fprintf(fp, "-A INPUT -i %s -p icmp --icmp-type 8 -j %s\n", wan_if, logdrop);
