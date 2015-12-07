#if defined(NETSNMP_DISABLE_SNMPV2C)
if (session->version == SNMP_VERSION_1)
#else
    if (session->version == SNMP_VERSION_1 ||
	session->version == SNMP_VERSION_2c)
#endif
#endif
    {
        if (Cpsz == NULL) {
            Cpsz = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID, 
					 NETSNMP_DS_LIB_COMMUNITY);
	    if (Cpsz == NULL) {
                if (netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID,
                                           NETSNMP_DS_LIB_IGNORE_NO_COMMUNITY)){
                    DEBUGMSGTL(("snmp_parse_args",
                                "ignoring that the community string is not present\n"));
                    session->community = NULL;
                    session->community_len = 0;
                } else {
                    fprintf(stderr, "No community name specified.\n");
                    return (NETSNMP_PARSE_ARGS_ERROR_USAGE);
                }
	    }
	} else {
            session->community = (unsigned char *)Cpsz;
            session->community_len = strlen(Cpsz);
        }
    }
