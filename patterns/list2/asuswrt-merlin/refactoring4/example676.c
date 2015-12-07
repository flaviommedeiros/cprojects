#if defined(NETSNMP_DISABLE_SNMPV2C)
if (pdu->version == SNMP_VERSION_1)
#else
        if (pdu->version == SNMP_VERSION_1 || pdu->version == SNMP_VERSION_2c)
#endif
#endif
        {
            snmp_increment_statistic(STAT_SNMPINBADCOMMUNITYUSES);
        }
