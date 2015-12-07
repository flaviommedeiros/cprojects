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
			obj.ipfo_rev = IPFILTER_VERSION;
			obj.ipfo_size = sizeof(ipn);
			obj.ipfo_ptr = &ipn;
			obj.ipfo_type = IPFOBJ_IPNAT;
			r = ioctl(dev, SIOCRMNAT, &obj);
			if (r == -1)
				syslog(LOG_ERR, "%s:ioctl(SIOCRMNAT): %m",
				    "delete_redirect_rule");
			/* Delete the desc even if the above failed */
			del_redirect_desc(eport, proto);
			break;
		}
