switch (option) {
	case RES_INIT:		return "init";
	case RES_DEBUG:		return "debug";
	case RES_AAONLY:	return "aaonly(unimpl)";
	case RES_USEVC:		return "usevc";
	case RES_PRIMARY:	return "primry(unimpl)";
	case RES_IGNTC:		return "igntc";
	case RES_RECURSE:	return "recurs";
	case RES_DEFNAMES:	return "defnam";
	case RES_STAYOPEN:	return "styopn";
	case RES_DNSRCH:	return "dnsrch";
	case RES_INSECURE1:	return "insecure1";
	case RES_INSECURE2:	return "insecure2";
	case RES_NOALIASES:	return "noaliases";
	case RES_USE_INET6:	return "inet6";
#ifdef RES_USE_EDNS0	/* KAME extension */
	case RES_USE_EDNS0:	return "edns0";
#endif
#ifdef RES_USE_DNAME
	case RES_USE_DNAME:	return "dname";
#endif
#ifdef RES_USE_DNSSEC
	case RES_USE_DNSSEC:	return "dnssec";
#endif
#ifdef RES_NOTLDQUERY
	case RES_NOTLDQUERY:	return "no-tld-query";
#endif
#ifdef RES_NO_NIBBLE2
	case RES_NO_NIBBLE2:	return "no-nibble2";
#endif
				/* XXX nonreentrant */
	default:		sprintf(nbuf, "?0x%lx?", (u_long)option);
				return (nbuf);
	}
