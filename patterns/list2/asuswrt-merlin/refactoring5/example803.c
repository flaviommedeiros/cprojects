#ifndef CURL_DISABLE_CRYPTO_AUTH
if(smtpc->authmechs & SMTP_AUTH_CRAM_MD5) {
      mech = "CRAM-MD5";
      state1 = SMTP_AUTHCRAM;
    }
    else
#endif
    if(smtpc->authmechs & SMTP_AUTH_PLAIN) {
      mech = "PLAIN";
      state1 = SMTP_AUTHPLAIN;
      state2 = SMTP_AUTH;
      l = smtp_auth_plain_data(conn, &initresp);
    }
    else if(smtpc->authmechs & SMTP_AUTH_LOGIN) {
      mech = "LOGIN";
      state1 = SMTP_AUTHLOGIN;
      state2 = SMTP_AUTHPASSWD;
      l = smtp_auth_login_user(conn, &initresp);
    }
    else {
      infof(conn->data, "No known auth mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;      /* Other mechanisms not supported. */
    }
