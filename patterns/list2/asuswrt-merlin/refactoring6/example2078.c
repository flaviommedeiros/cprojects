if ((drop_err && (ii < pdu->errindex))
#if TEMPORARILY_DISABLED
        /*
         * SNMPv3 engineID probes are allowed to be empty.
         * See the comment in snmp_api.c for further details 
         */
        || copied == 0
#endif
        ) {
        snmp_free_pdu(newpdu);
        return 0;
    }
