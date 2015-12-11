switch(imapc->state) {
    case IMAP_SERVERGREET:
      result = imap_state_servergreet_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_CAPABILITY:
      result = imap_state_capability_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_STARTTLS:
      result = imap_state_starttls_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_PLAIN:
      result = imap_state_auth_plain_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_LOGIN:
      result = imap_state_auth_login_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_LOGIN_PASSWD:
      result = imap_state_auth_login_password_resp(conn, imapcode,
                                                   imapc->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case IMAP_AUTHENTICATE_CRAMMD5:
      result = imap_state_auth_cram_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_DIGESTMD5:
      result = imap_state_auth_digest_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_DIGESTMD5_RESP:
      result = imap_state_auth_digest_resp_resp(conn, imapcode, imapc->state);
      break;
#endif

#ifdef USE_NTLM
    case IMAP_AUTHENTICATE_NTLM:
      result = imap_state_auth_ntlm_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_AUTHENTICATE_NTLM_TYPE2MSG:
      result = imap_state_auth_ntlm_type2msg_resp(conn, imapcode,
                                                  imapc->state);
      break;
#endif

    case IMAP_AUTHENTICATE_FINAL:
      result = imap_state_auth_final_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LOGIN:
      result = imap_state_login_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LIST:
      result = imap_state_list_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_SELECT:
      result = imap_state_select_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_FETCH:
      result = imap_state_fetch_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_FETCH_FINAL:
      result = imap_state_fetch_final_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_APPEND:
      result = imap_state_append_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_APPEND_FINAL:
      result = imap_state_append_final_resp(conn, imapcode, imapc->state);
      break;

    case IMAP_LOGOUT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, IMAP_STOP);
      break;
    }
