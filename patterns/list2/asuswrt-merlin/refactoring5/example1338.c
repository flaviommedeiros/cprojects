#ifndef NETSNMP_DISABLE_SNMPV2C
if (!strcmp( line, "2"  ) || !strcasecmp( line, "2c" ))
        netsnmp_ds_set_int(NETSNMP_DS_APPLICATION_ID,
                           NETSNMP_DS_AGENT_INTERNAL_VERSION, SNMP_VERSION_2c);
    else 
#endif
         if (!strcmp( line, "3" ))
        netsnmp_ds_set_int(NETSNMP_DS_APPLICATION_ID,
                           NETSNMP_DS_AGENT_INTERNAL_VERSION, SNMP_VERSION_3);
    else {
	netsnmp_config_error("Unknown version: %s", line);
    }
