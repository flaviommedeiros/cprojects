#ifdef USE_NTLM
if((smtpc->authmechs & SASL_MECH_NTLM) &&
     (smtpc->prefmech & SASL_MECH_NTLM)) {
    mech = "NTLM";
    state1 = SMTP_AUTH_NTLM;
    state2 = SMTP_AUTH_NTLM_TYPE2MSG;
    smtpc->authused = SASL_MECH_NTLM;

    if(data->set.sasl_ir)
      result = Curl_sasl_create_ntlm_type1_message(conn->user, conn->passwd,
                                                   &conn->ntlm,
                                                   &initresp, &len);
    }
  else
#endif
  if((smtpc->authmechs & SASL_MECH_LOGIN) &&
     (smtpc->prefmech & SASL_MECH_LOGIN)) {
    mech = "LOGIN";
    state1 = SMTP_AUTH_LOGIN;
    state2 = SMTP_AUTH_LOGIN_PASSWD;
    smtpc->authused = SASL_MECH_LOGIN;

    if(data->set.sasl_ir)
      result = Curl_sasl_create_login_message(conn->data, conn->user,
                                              &initresp, &len);
  }
  else if((smtpc->authmechs & SASL_MECH_PLAIN) &&
          (smtpc->prefmech & SASL_MECH_PLAIN)) {
    mech = "PLAIN";
    state1 = SMTP_AUTH_PLAIN;
    state2 = SMTP_AUTH_FINAL;
    smtpc->authused = SASL_MECH_PLAIN;

    if(data->set.sasl_ir)
      result = Curl_sasl_create_plain_message(conn->data, conn->user,
                                              conn->passwd, &initresp, &len);
  }
