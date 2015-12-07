#ifdef USE_NAPTR
if (cfg_get(core, core_cfg, dns_try_naptr))
		res = naptr_sip_resolvehost(name, port, proto);
	else
#endif
	res = srv_sip_resolvehost(name, 0, port, proto, 0, 0);
