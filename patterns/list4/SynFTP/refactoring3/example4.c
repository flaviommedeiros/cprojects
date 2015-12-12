switch(session->next_crypto->kex_type){
    case SSH_KEX_DH_GROUP1_SHA1:
    case SSH_KEX_DH_GROUP14_SHA1:
      rc=ssh_client_dh_reply(session, packet);
      break;
#ifdef HAVE_ECDH
    case SSH_KEX_ECDH_SHA2_NISTP256:
      rc = ssh_client_ecdh_reply(session, packet);
      break;
#endif
#ifdef HAVE_CURVE25519
    case SSH_KEX_CURVE25519_SHA256_LIBSSH_ORG:
      rc = ssh_client_curve25519_reply(session, packet);
      break;
#endif
    default:
      ssh_set_error(session,SSH_FATAL,"Wrong kex type in ssh_packet_dh_reply");
      goto error;
  }
