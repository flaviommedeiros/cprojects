if ( template_pdu->command == SNMP_MSG_INFORM
#ifdef USING_AGENTX_PROTOCOL_MODULE
         || template_pdu->command == AGENTX_MSG_NOTIFY
#endif
       ) {
        result =
            snmp_async_send(sess, pdu, &handle_inform_response, NULL);
        
    } else {
        if ((sess->version == SNMP_VERSION_3) &&
                (pdu->command == SNMP_MSG_TRAP2) &&
                (sess->securityEngineIDLen == 0)) {
            u_char          tmp[SPRINT_MAX_LEN];

            int len = snmpv3_get_engineID(tmp, sizeof(tmp));
            memdup(&pdu->securityEngineID, tmp, len);
            pdu->securityEngineIDLen = len;
        }

        result = snmp_send(sess, pdu);
    }
