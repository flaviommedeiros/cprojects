#ifndef DISABLE_MD5
if (!strcmp(auth_proto, "MD5")) {
    session.securityAuthProto = 
      snmp_duplicate_objid(usmHMACMD5AuthProtocol,
			   USM_AUTH_PROTO_MD5_LEN);
    session.securityAuthProtoLen = USM_AUTH_PROTO_MD5_LEN;
  } else
#endif
    if (!strcmp(auth_proto, "SHA")) {
      session.securityAuthProto = 
	snmp_duplicate_objid(usmHMACSHA1AuthProtocol,
			     USM_AUTH_PROTO_SHA_LEN);
      session.securityAuthProtoLen = USM_AUTH_PROTO_SHA_LEN;
    } else if (!strcmp(auth_proto, "DEFAULT")) {
      const oid* a = get_default_authtype(&session.securityAuthProtoLen);
      session.securityAuthProto
        = snmp_duplicate_objid(a, session.securityAuthProtoLen);
    } else {
      if (verbose)
	printf("error:snmp_new_v3_session:Unsupported authentication protocol(%s)\n", auth_proto);
      goto end;
    }
