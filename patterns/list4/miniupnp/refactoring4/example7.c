#if IPFILTER_VERSION >= 5000000
if (eport == ntohs(ipn.in_dpmin) &&
		    eport == ntohs(ipn.in_dpmax) &&
		    strcmp(ipn.in_tag.ipt_tag, group_name) == 0 &&
		    ipn.in_pr[0] == proto)
#else
		if (eport == ntohs(ipn.in_pmin) &&
		    eport == ntohs(ipn.in_pmax) &&
		    strcmp(ipn.in_tag.ipt_tag, group_name) == 0 &&
		    ipn.in_p == proto)
#endif
		{
			strlcpy(desc, "", desclen);
			if (packets != NULL)
				*packets = 0;
			if (bytes != NULL)
				*bytes = 0;
			if (iport != NULL)
#if IPFILTER_VERSION >= 5000000
				*iport = ntohs(ipn.in_dpnext);
#else
				*iport = ntohs(ipn.in_pnext);
#endif
			if ((desc != NULL) && (timestamp != NULL))
				get_redirect_desc(eport, proto, desc, desclen, timestamp);
			if ((rhost != NULL) && (rhostlen > 0))
#if IPFILTER_VERSION >= 5000000
				inet_ntop(AF_INET, &ipn.in_nsrc.na_addr[0].in4, rhost, rhostlen);	/* in_nsrcip */
#else
				inet_ntop(AF_INET, &ipn.in_src[0].in4, rhost, rhostlen);
#endif
#if IPFILTER_VERSION >= 5000000
			inet_ntop(AF_INET, &ipn.in_ndst.na_addr[0].in4, iaddr, iaddrlen);	/* in_ndstip */
#else
			inet_ntop(AF_INET, &ipn.in_in[0].in4, iaddr, iaddrlen);
#endif
			r = 0;
		}
