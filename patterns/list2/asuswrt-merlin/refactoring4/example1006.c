#if !defined(NETSNMP_DISABLE_SNMPV1) || !defined(NETSNMP_DISABLE_SNMPV2C)
if (pdu->version == SNMP_VERSION_2c)
#else
#if defined(NETSNMP_DISABLE_SNMPV2C)
    if (pdu->version == SNMP_VERSION_1)
#else
    if (pdu->version == SNMP_VERSION_1 || pdu->version == SNMP_VERSION_2c)
#endif
#endif
    {
        pdu_community = (const char *) pdu->community;
        if (!pdu_community)
            pdu_community = "";
        if (snmp_get_do_debugging()) {
            char           *buf;
            if (pdu->community) {
                buf = (char *) malloc(1 + pdu->community_len);
                memcpy(buf, pdu->community, pdu->community_len);
                buf[pdu->community_len] = '\0';
            } else {
                DEBUGMSGTL(("mibII/vacm_vars", "NULL community"));
                buf = strdup("NULL");
            }

            DEBUGMSGTL(("mibII/vacm_vars",
                        "vacm_in_view: ver=%ld, community=%s\n",
                        pdu->version, buf));
            free(buf);
        }

        /*
         * Okay, if this PDU was received from a UDP or a TCP transport then
         * ask the transport abstraction layer to map its source address and
         * community string to a security name for us.  
         */

        if (0) {
#ifdef NETSNMP_TRANSPORT_UDP_DOMAIN
        } else if (pdu->tDomain == netsnmpUDPDomain
#ifdef NETSNMP_TRANSPORT_TCP_DOMAIN
            || pdu->tDomain == netsnmp_snmpTCPDomain
#endif
            ) {
            if (!netsnmp_udp_getSecName(pdu->transport_data,
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
#ifdef NETSNMP_TRANSPORT_UDPIPV6_DOMAIN
        } else if (pdu->tDomain == netsnmp_UDPIPv6Domain
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

    } else
#endif /* support for community based SNMP */
      if (find_sec_mod(pdu->securityModel)) {
        /*
         * any legal defined v3 security model 
         */
        DEBUGMSG(("mibII/vacm_vars",
                  "vacm_in_view: ver=%ld, model=%d, secName=%s\n",
                  pdu->version, pdu->securityModel, pdu->securityName));
        sn = pdu->securityName;
        contextName = pdu->contextName;
    } else {
        sn = NULL;
    }
