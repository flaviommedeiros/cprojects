#ifndef DISABLE_DES
if (!strcmp(priv_proto, "DES")) {
    session.securityPrivProto =
      snmp_duplicate_objid(usmDESPrivProtocol,
			   USM_PRIV_PROTO_DES_LEN);
    session.securityPrivProtoLen = USM_PRIV_PROTO_DES_LEN;
  } else
#endif
    if (!strncmp(priv_proto, "AES", 3)) {
      session.securityPrivProto =
	snmp_duplicate_objid(usmAESPrivProtocol,
			     USM_PRIV_PROTO_AES_LEN);
      session.securityPrivProtoLen = USM_PRIV_PROTO_AES_LEN;
    } else if (!strcmp(priv_proto, "DEFAULT")) {
      const oid *p = get_default_privtype(&session.securityPrivProtoLen);
      session.securityPrivProto
        = snmp_duplicate_objid(p, session.securityPrivProtoLen);
    } else {
      if (verbose)
	printf("error:snmp_new_v3_session:Unsupported privacy protocol(%s)\n", priv_proto);
      goto end;
    }
