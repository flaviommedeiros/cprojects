#ifndef CURL_DISABLE_CRYPTO_AUTH
if((imapc->authmechs & SASL_MECH_DIGEST_MD5) &&
     (imapc->prefmech & SASL_MECH_DIGEST_MD5)) {
    *mech = SASL_MECH_STRING_DIGEST_MD5;
    *state1 = IMAP_AUTHENTICATE_DIGESTMD5;
    imapc->authused = SASL_MECH_DIGEST_MD5;
  }
  else if((imapc->authmechs & SASL_MECH_CRAM_MD5) &&
          (imapc->prefmech & SASL_MECH_CRAM_MD5)) {
    *mech = SASL_MECH_STRING_CRAM_MD5;
    *state1 = IMAP_AUTHENTICATE_CRAMMD5;
    imapc->authused = SASL_MECH_CRAM_MD5;
  }
  else
#endif
#ifdef USE_NTLM
    if((imapc->authmechs & SASL_MECH_NTLM) &&
       (imapc->prefmech & SASL_MECH_NTLM)) {
    *mech = SASL_MECH_STRING_NTLM;
    *state1 = IMAP_AUTHENTICATE_NTLM;
    *state2 = IMAP_AUTHENTICATE_NTLM_TYPE2MSG;
    imapc->authused = SASL_MECH_NTLM;

    if(imapc->ir_supported || data->set.sasl_ir)
      result = Curl_sasl_create_ntlm_type1_message(conn->user, conn->passwd,
                                                   &conn->ntlm,
                                                   initresp, len);
  }
  else
#endif
  if(((imapc->authmechs & SASL_MECH_XOAUTH2) &&
      (imapc->prefmech & SASL_MECH_XOAUTH2) &&
      (imapc->prefmech != SASL_AUTH_ANY)) || conn->xoauth2_bearer) {
    *mech = SASL_MECH_STRING_XOAUTH2;
    *state1 = IMAP_AUTHENTICATE_XOAUTH2;
    *state2 = IMAP_AUTHENTICATE_FINAL;
    imapc->authused = SASL_MECH_XOAUTH2;

    if(imapc->ir_supported || data->set.sasl_ir)
      result = Curl_sasl_create_xoauth2_message(data, conn->user,
                                                conn->xoauth2_bearer,
                                                initresp, len);
  }
  else if((imapc->authmechs & SASL_MECH_LOGIN) &&
          (imapc->prefmech & SASL_MECH_LOGIN)) {
    *mech = SASL_MECH_STRING_LOGIN;
    *state1 = IMAP_AUTHENTICATE_LOGIN;
    *state2 = IMAP_AUTHENTICATE_LOGIN_PASSWD;
    imapc->authused = SASL_MECH_LOGIN;

    if(imapc->ir_supported || data->set.sasl_ir)
      result = Curl_sasl_create_login_message(data, conn->user, initresp, len);
  }
  else if((imapc->authmechs & SASL_MECH_PLAIN) &&
          (imapc->prefmech & SASL_MECH_PLAIN)) {
    *mech = SASL_MECH_STRING_PLAIN;
    *state1 = IMAP_AUTHENTICATE_PLAIN;
    *state2 = IMAP_AUTHENTICATE_FINAL;
    imapc->authused = SASL_MECH_PLAIN;

    if(imapc->ir_supported || data->set.sasl_ir)
      result = Curl_sasl_create_plain_message(data, conn->user, conn->passwd,
                                              initresp, len);
  }
