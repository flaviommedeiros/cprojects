if (pdu->tDomain == netsnmp_UDPIPv6Domain
#ifdef NETSNMP_TRANSPORT_TCPIPV6_DOMAIN
                   || pdu->tDomain == netsnmp_TCPIPv6Domain
#endif
            ) {
            if (!netsnmp_udp6_getSecName(pdu->transport_data,
                                         pdu->transport_data_length,
                                         pdu_community,
                                         pdu->community_len, &sn,
                                         &contextName)) {
                /*
                 * There are no com2sec entries.  
                 */
                sn = NULL;
            }
            /* force the community -> context name mapping here */
            SNMP_FREE(pdu->contextName);
            pdu->contextName = strdup(contextName);
            pdu->contextNameLen = strlen(contextName);
#endif
#ifdef NETSNMP_TRANSPORT_UNIX_DOMAIN
        } else if (pdu->tDomain == netsnmp_UnixDomain){
            if (!netsnmp_unix_getSecName(pdu->transport_data,
                                         pdu->transport_data_length,
                                         pdu_community,
                                         pdu->community_len, &sn,
                                         &contextName)) {
					sn = NULL;
            }
            /* force the community -> context name mapping here */
            SNMP_FREE(pdu->contextName);
            pdu->contextName = strdup(contextName);
            pdu->contextNameLen = strlen(contextName);
#endif	
        } else {
            /*
             * Map other <community, transport-address> pairs to security names
             * here.  For now just let non-IPv4 transport always succeed.
             * 
             * WHAAAATTTT.  No, we don't let non-IPv4 transports
             * succeed!  You must fix this to make it usable, sorry.
             * From a security standpoint this is insane. -- Wes
             */
            /** @todo alternate com2sec mappings for non v4 transports.
                Should be implemented via registration */
            sn = NULL;
        }
