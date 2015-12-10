switch(smtpc->state) {
    case SMTP_SERVERGREET:
      result = smtp_state_servergreet_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_EHLO:
      result = smtp_state_ehlo_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_HELO:
      result = smtp_state_helo_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_STARTTLS:
      result = smtp_state_starttls_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_PLAIN:
      result = smtp_state_auth_plain_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_LOGIN:
      result = smtp_state_auth_login_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_LOGIN_PASSWD:
      result = smtp_state_auth_login_password_resp(conn, smtpcode,
                                                   smtpc->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case SMTP_AUTH_CRAMMD5:
      result = smtp_state_auth_cram_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_DIGESTMD5:
      result = smtp_state_auth_digest_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_DIGESTMD5_RESP:
      result = smtp_state_auth_digest_resp_resp(conn, smtpcode, smtpc->state);
      break;
#endif

#ifdef USE_NTLM
    case SMTP_AUTH_NTLM:
      result = smtp_state_auth_ntlm_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_NTLM_TYPE2MSG:
      result = smtp_state_auth_ntlm_type2msg_resp(conn, smtpcode,
                                                  smtpc->state);
      break;
#endif

#if defined(USE_KERBEROS5)
    case SMTP_AUTH_GSSAPI:
      result = smtp_state_auth_gssapi_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_GSSAPI_TOKEN:
      result = smtp_state_auth_gssapi_token_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_GSSAPI_NO_DATA:
      result = smtp_state_auth_gssapi_no_data_resp(conn, smtpcode,
                                                   smtpc->state);
      break;
#endif

    case SMTP_AUTH_XOAUTH2:
      result = smtp_state_auth_xoauth2_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_CANCEL:
      result = smtp_state_auth_cancel_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_AUTH_FINAL:
      result = smtp_state_auth_final_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_COMMAND:
      result = smtp_state_command_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_MAIL:
      result = smtp_state_mail_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_RCPT:
      result = smtp_state_rcpt_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_DATA:
      result = smtp_state_data_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_POSTDATA:
      result = smtp_state_postdata_resp(conn, smtpcode, smtpc->state);
      break;

    case SMTP_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, SMTP_STOP);
      break;
    }
