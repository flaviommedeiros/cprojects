switch(pop3c->state) {
    case POP3_SERVERGREET:
      result = pop3_state_servergreet_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_CAPA:
      result = pop3_state_capa_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_STARTTLS:
      result = pop3_state_starttls_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_PLAIN:
      result = pop3_state_auth_plain_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_LOGIN:
      result = pop3_state_auth_login_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_LOGIN_PASSWD:
      result = pop3_state_auth_login_password_resp(conn, pop3code,
                                                   pop3c->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case POP3_AUTH_CRAMMD5:
      result = pop3_state_auth_cram_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_DIGESTMD5:
      result = pop3_state_auth_digest_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_DIGESTMD5_RESP:
      result = pop3_state_auth_digest_resp_resp(conn, pop3code, pop3c->state);
      break;
#endif

#ifdef USE_NTLM
    case POP3_AUTH_NTLM:
      result = pop3_state_auth_ntlm_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_NTLM_TYPE2MSG:
      result = pop3_state_auth_ntlm_type2msg_resp(conn, pop3code,
                                                  pop3c->state);
      break;
#endif

#if defined(USE_KERBEROS5)
    case POP3_AUTH_GSSAPI:
      result = pop3_state_auth_gssapi_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_GSSAPI_TOKEN:
      result = pop3_state_auth_gssapi_token_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_GSSAPI_NO_DATA:
      result = pop3_state_auth_gssapi_no_data_resp(conn, pop3code,
                                                   pop3c->state);
      break;
#endif

    case POP3_AUTH_XOAUTH2:
      result = pop3_state_auth_xoauth2_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_CANCEL:
      result = pop3_state_auth_cancel_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_FINAL:
      result = pop3_state_auth_final_resp(conn, pop3code, pop3c->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case POP3_APOP:
      result = pop3_state_apop_resp(conn, pop3code, pop3c->state);
      break;
#endif

    case POP3_USER:
      result = pop3_state_user_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_PASS:
      result = pop3_state_pass_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_COMMAND:
      result = pop3_state_command_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, POP3_STOP);
      break;
    }
