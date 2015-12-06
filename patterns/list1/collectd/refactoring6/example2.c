if ((vl->type == ASN_INTEGER)
      || (vl->type == ASN_UINTEGER)
      || (vl->type == ASN_COUNTER)
#ifdef ASN_TIMETICKS
      || (vl->type == ASN_TIMETICKS)
#endif
      || (vl->type == ASN_GAUGE))
  {
    tmp_unsigned = (uint32_t) *vl->val.integer;
    tmp_signed = (int32_t) *vl->val.integer;

    if (vl->type == ASN_INTEGER)
      prefer_signed = 1;

    DEBUG ("snmp plugin: Parsed int32 value is %"PRIu64".", tmp_unsigned);
  }
  else if (vl->type == ASN_COUNTER64)
  {
    tmp_unsigned = (uint32_t) vl->val.counter64->high;
    tmp_unsigned = tmp_unsigned << 32;
    tmp_unsigned += (uint32_t) vl->val.counter64->low;
    tmp_signed = (int64_t) tmp_unsigned;
    DEBUG ("snmp plugin: Parsed int64 value is %"PRIu64".", tmp_unsigned);
  }
  else if (vl->type == ASN_OCTET_STR)
  {
    /* We'll handle this later.. */
  }
  else
  {
    char oid_buffer[1024];

    memset (oid_buffer, 0, sizeof (oid_buffer));
    snprint_objid (oid_buffer, sizeof (oid_buffer) - 1,
        vl->name, vl->name_length);

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

    defined = 0;
  }
