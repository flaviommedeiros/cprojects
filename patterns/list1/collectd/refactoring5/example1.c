#ifdef ASN_NULL
if (vl->type == ASN_NULL)
      INFO ("snmp plugin: OID \"%s\" is undefined (type ASN_NULL)",
          oid_buffer);
    else
#endif
      WARNING ("snmp plugin: I don't know the ASN type #%i "
               "(OID: \"%s\", data block \"%s\", host block \"%s\")",
          (int) vl->type, oid_buffer,
          (data_name != NULL) ? data_name : "UNKNOWN",
          (host_name != NULL) ? host_name : "UNKNOWN");
