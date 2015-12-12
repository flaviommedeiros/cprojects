#ifdef _WIN32
if (resolv_conf == NULL)
			res = evdns_base_config_windows_nameservers(evdns_base);
		else
#endif
			res = evdns_base_resolv_conf_parse(evdns_base,
			    DNS_OPTION_NAMESERVERS,
			    resolv_conf ? resolv_conf : "/etc/resolv.conf");
