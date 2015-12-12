void
SendSSDPNotifies2(int * sockets,
                  unsigned short http_port,
#ifdef ENABLE_HTTPS
                  unsigned short https_port,
#endif
                  unsigned int lifetime)
{
	int i;
	struct lan_addr_s * lan_addr;
	for(i = 0, lan_addr = lan_addrs.lh_first;
	    lan_addr != NULL;
	    lan_addr = lan_addr->list.le_next) {
		SendSSDPNotifies(sockets[i], lan_addr->str, http_port,
#ifdef ENABLE_HTTPS
		                 https_port,
#endif
		                 lifetime, 0);
		i++;
#ifdef ENABLE_IPV6
		if(sockets[i] >= 0) {
			SendSSDPNotifies(sockets[i], ipv6_addr_for_http_with_brackets, http_port,
#ifdef ENABLE_HTTPS
			                 https_port,
#endif
			                 lifetime, 1);
		}
		i++;
#endif	/* ENABLE_IPV6 */
	}
}
