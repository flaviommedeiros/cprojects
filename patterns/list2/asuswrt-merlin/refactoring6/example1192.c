if(l<=st_len && (0 == memcmp(st, known_service_types[i].s, l))
#ifdef UPNP_STRICT
				   && (st_ver <= known_service_types[i].version)
		/* only answer for service version lower or equal of supported one */
#endif
				   )
				{
					/* SSDP_RESPOND_SAME_VERSION :
					 * response is urn:schemas-upnp-org:service:WANIPConnection:1 when
					 * M-SEARCH included urn:schemas-upnp-org:service:WANIPConnection:1
					 * else the implemented versions is included in the response
					 *
					 * From UPnP Device Architecture v1.1 :
					 * 1.3.2 [...] Updated versions of device and service types
					 * are REQUIRED to be fully backward compatible with
					 * previous versions. Devices MUST respond to M-SEARCH
					 * requests for any supported version. For example, if a
					 * device implements âurn:schemas-upnporg:service:xyz:2â,
					 * it MUST respond to search requests for both that type
					 * and âurn:schemas-upnp-org:service:xyz:1â. The response
					 * MUST specify the same version as was contained in the
					 * search request. [...] */
#ifndef SSDP_RESPOND_SAME_VERSION
					if(i==0)
						ver_str[0] = '\0';
					else
						snprintf(ver_str, sizeof(ver_str), "%d", known_service_types[i].version);
#endif
					syslog(LOG_INFO, "Single search found");
#ifdef DELAY_MSEARCH_RESPONSE
					delay = random() / (1 + RAND_MAX / (1000 * mx_value));
#ifdef DEBUG
					syslog(LOG_DEBUG, "mx=%dsec delay=%ums", mx_value, delay);
#endif
#endif
					SendSSDPResponse(s, sender,
#ifdef SSDP_RESPOND_SAME_VERSION
					                 st, st_len, "",
#else
					                 known_service_types[i].s, l, ver_str,
#endif
					                 announced_host, http_port,
#ifdef ENABLE_HTTPS
					                 https_port,
#endif
					                 known_service_types[i].uuid,
					                 delay);
					break;
				}
