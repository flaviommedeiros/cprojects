switch(v->ieventvalue) {
			case 0:
				break;
			case CONNECTIONSTATUS_MAGICALVALUE:
				/* or get_wan_connection_status_str(ext_if_name) */
				str = strcat_str(str, len, &tmplen,
				   upnpallowedvalues[18 + get_wan_connection_status(ext_if_name)]);
				break;
#ifdef ENABLE_6FC_SERVICE
			case FIREWALLENABLED_MAGICALVALUE:
				/* see 2.4.2 of UPnP-gw-WANIPv6FirewallControl-v1-Service.pdf */
				snprintf(tmp, sizeof(tmp), "%d",
				         GETFLAG(IPV6FCFWDISABLEDMASK) ? 0 : 1);
				str = strcat_str(str, len, &tmplen, tmp);
				break;
			case INBOUNDPINHOLEALLOWED_MAGICALVALUE:
				/* see 2.4.3 of UPnP-gw-WANIPv6FirewallControl-v1-Service.pdf */
				snprintf(tmp, sizeof(tmp), "%d",
				         GETFLAG(IPV6FCINBOUNDDISALLOWEDMASK) ? 0 : 1);
				str = strcat_str(str, len, &tmplen, tmp);
				break;
#endif
#ifdef IGD_V2
			case SYSTEMUPDATEID_MAGICALVALUE:
				/* Please read section 2.3.23 SystemUpdateID
				 * of UPnP-gw-WANIPConnection-v2-Service.pdf */
				snprintf(tmp, sizeof(tmp), "%d",
				         1/* system update id */);
				str = strcat_str(str, len, &tmplen, tmp);
				break;
#endif
			case PORTMAPPINGNUMBEROFENTRIES_MAGICALVALUE:
				/* Port mapping number of entries magical value */
				snprintf(tmp, sizeof(tmp), "%d",
				         upnp_get_portmapping_number_of_entries());
				str = strcat_str(str, len, &tmplen, tmp);
				break;
			case EXTERNALIPADDRESS_MAGICALVALUE:
				/* External ip address magical value */
				if(use_ext_ip_addr)
					str = strcat_str(str, len, &tmplen, use_ext_ip_addr);
				else {
					char ext_ip_addr[INET_ADDRSTRLEN];
					if(getifaddr(ext_if_name, ext_ip_addr, INET_ADDRSTRLEN, NULL, NULL) < 0) {
						str = strcat_str(str, len, &tmplen, "0.0.0.0");
					} else {
						str = strcat_str(str, len, &tmplen, ext_ip_addr);
					}
				}
				break;
			case DEFAULTCONNECTIONSERVICE_MAGICALVALUE:
				/* DefaultConnectionService magical value */
				str = strcat_str(str, len, &tmplen, uuidvalue_wcd);
#ifdef IGD_V2
				str = strcat_str(str, len, &tmplen, ":WANConnectionDevice:2,urn:upnp-org:serviceId:WANIPConn1");
#else
				str = strcat_str(str, len, &tmplen, ":WANConnectionDevice:1,urn:upnp-org:serviceId:WANIPConn1");
#endif
				break;
			default:
				str = strcat_str(str, len, &tmplen, upnpallowedvalues[v->ieventvalue]);
			}
