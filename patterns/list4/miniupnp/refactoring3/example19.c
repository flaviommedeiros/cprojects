switch(ary_options[i].id)
			{
			case UPNPEXT_IFNAME:
				ext_if_name = ary_options[i].value;
				break;
			case UPNPEXT_IP:
				use_ext_ip_addr = ary_options[i].value;
				break;
			case UPNPLISTENING_IP:
				lan_addr = (struct lan_addr_s *) malloc(sizeof(struct lan_addr_s));
				if (lan_addr == NULL)
				{
					fprintf(stderr, "malloc(sizeof(struct lan_addr_s)): %m");
					break;
				}
				if(parselanaddr(lan_addr, ary_options[i].value) != 0)
				{
					fprintf(stderr, "can't parse \"%s\" as a valid "
#ifndef ENABLE_IPV6
					        "LAN address or "
#endif
					        "interface name\n", ary_options[i].value);
					free(lan_addr);
					break;
				}
				LIST_INSERT_HEAD(&lan_addrs, lan_addr, list);
				break;
#ifdef ENABLE_IPV6
			case UPNPIPV6_LISTENING_IP:
				if (inet_pton(AF_INET6, ary_options[i].value, &ipv6_bind_addr) < 1)
				{
					fprintf(stderr, "can't parse \"%s\" as valid IPv6 listening address", ary_options[i].value);
				}
				break;
#endif /* ENABLE_IPV6 */
			case UPNPPORT:
				v->port = atoi(ary_options[i].value);
				break;
#ifdef ENABLE_HTTPS
			case UPNPHTTPSPORT:
				v->https_port = atoi(ary_options[i].value);
				break;
#endif
			case UPNPBITRATE_UP:
				upstream_bitrate = strtoul(ary_options[i].value, 0, 0);
				break;
			case UPNPBITRATE_DOWN:
				downstream_bitrate = strtoul(ary_options[i].value, 0, 0);
				break;
			case UPNPPRESENTATIONURL:
				presurl = ary_options[i].value;
				break;
#ifdef ENABLE_MANUFACTURER_INFO_CONFIGURATION
			case UPNPFRIENDLY_NAME:
				strncpy(friendly_name, ary_options[i].value, FRIENDLY_NAME_MAX_LEN);
				friendly_name[FRIENDLY_NAME_MAX_LEN-1] = '\0';
				break;
			case UPNPMANUFACTURER_NAME:
				strncpy(manufacturer_name, ary_options[i].value, MANUFACTURER_NAME_MAX_LEN);
				manufacturer_name[MANUFACTURER_NAME_MAX_LEN-1] = '\0';
				break;
			case UPNPMANUFACTURER_URL:
				strncpy(manufacturer_url, ary_options[i].value, MANUFACTURER_URL_MAX_LEN);
				manufacturer_url[MANUFACTURER_URL_MAX_LEN-1] = '\0';
				break;
			case UPNPMODEL_NAME:
				strncpy(model_name, ary_options[i].value, MODEL_NAME_MAX_LEN);
				model_name[MODEL_NAME_MAX_LEN-1] = '\0';
				break;
			case UPNPMODEL_DESCRIPTION:
				strncpy(model_description, ary_options[i].value, MODEL_DESCRIPTION_MAX_LEN);
				model_description[MODEL_DESCRIPTION_MAX_LEN-1] = '\0';
				break;
			case UPNPMODEL_URL:
				strncpy(model_url, ary_options[i].value, MODEL_URL_MAX_LEN);
				model_url[MODEL_URL_MAX_LEN-1] = '\0';
				break;
#endif	/* ENABLE_MANUFACTURER_INFO_CONFIGURATION */
#ifdef USE_NETFILTER
			case UPNPFORWARDCHAIN:
				miniupnpd_forward_chain = ary_options[i].value;
				break;
			case UPNPNATCHAIN:
				miniupnpd_nat_chain = ary_options[i].value;
				break;
#endif	/* USE_NETFILTER */
			case UPNPNOTIFY_INTERVAL:
				v->notify_interval = atoi(ary_options[i].value);
				break;
			case UPNPSYSTEM_UPTIME:
				if(strcmp(ary_options[i].value, "yes") == 0)
					SETFLAG(SYSUPTIMEMASK);	/*sysuptime = 1;*/
				break;
#if defined(USE_PF) || defined(USE_IPF)
			case UPNPPACKET_LOG:
				if(strcmp(ary_options[i].value, "yes") == 0)
					SETFLAG(LOGPACKETSMASK);	/*logpackets = 1;*/
				break;
#endif	/* defined(USE_PF) || defined(USE_IPF) */
			case UPNPUUID:
				strncpy(uuidvalue_igd+5, ary_options[i].value,
				        strlen(uuidvalue_igd+5) + 1);
				complete_uuidvalues();
				break;
			case UPNPSERIAL:
				strncpy(serialnumber, ary_options[i].value, SERIALNUMBER_MAX_LEN);
				serialnumber[SERIALNUMBER_MAX_LEN-1] = '\0';
				break;
			case UPNPMODEL_NUMBER:
				strncpy(modelnumber, ary_options[i].value, MODELNUMBER_MAX_LEN);
				modelnumber[MODELNUMBER_MAX_LEN-1] = '\0';
				break;
			case UPNPCLEANTHRESHOLD:
				v->clean_ruleset_threshold = atoi(ary_options[i].value);
				break;
			case UPNPCLEANINTERVAL:
				v->clean_ruleset_interval = atoi(ary_options[i].value);
				break;
#ifdef USE_PF
			case UPNPANCHOR:
				anchor_name = ary_options[i].value;
				break;
			case UPNPQUEUE:
				queue = ary_options[i].value;
				break;
			case UPNPTAG:
				tag = ary_options[i].value;
				break;
#endif	/* USE_PF */
#ifdef ENABLE_NATPMP
			case UPNPENABLENATPMP:
				if(strcmp(ary_options[i].value, "yes") == 0)
					SETFLAG(ENABLENATPMPMASK);	/*enablenatpmp = 1;*/
				else
					if(atoi(ary_options[i].value))
						SETFLAG(ENABLENATPMPMASK);
					/*enablenatpmp = atoi(ary_options[i].value);*/
				break;
#endif	/* ENABLE_NATPMP */
#ifdef ENABLE_PCP
			case UPNPPCPMINLIFETIME:
					min_lifetime = atoi(ary_options[i].value);
					if (min_lifetime > 120 ) {
						min_lifetime = 120;
					}
				break;
			case UPNPPCPMAXLIFETIME:
					max_lifetime = atoi(ary_options[i].value);
					if (max_lifetime > 86400 ) {
						max_lifetime = 86400;
					}
				break;
			case UPNPPCPALLOWTHIRDPARTY:
				if(strcmp(ary_options[i].value, "yes") == 0)
					SETFLAG(PCP_ALLOWTHIRDPARTYMASK);
				break;
#endif	/* ENABLE_PCP */
#ifdef PF_ENABLE_FILTER_RULES
			case UPNPQUICKRULES:
				if(strcmp(ary_options[i].value, "no") == 0)
					SETFLAG(PFNOQUICKRULESMASK);
				break;
#endif	/* PF_ENABLE_FILTER_RULES */
			case UPNPENABLE:
				if(strcmp(ary_options[i].value, "yes") != 0)
					CLEARFLAG(ENABLEUPNPMASK);
				break;
			case UPNPSECUREMODE:
				if(strcmp(ary_options[i].value, "yes") == 0)
					SETFLAG(SECUREMODEMASK);
				break;
#ifdef ENABLE_LEASEFILE
			case UPNPLEASEFILE:
				lease_file = ary_options[i].value;
				break;
#endif	/* ENABLE_LEASEFILE */
			case UPNPMINISSDPDSOCKET:
				minissdpdsocketpath = ary_options[i].value;
				break;
			default:
				fprintf(stderr, "Unknown option in file %s\n",
				        optionsfile);
			}
