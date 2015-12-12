switch(session->next_crypto->kex_type){
        case SSH_KEX_DH_GROUP1_SHA1:
        case SSH_KEX_DH_GROUP14_SHA1:
          rc = ssh_client_dh_init(session);
          break;
#ifdef HAVE_ECDH
        case SSH_KEX_ECDH_SHA2_NISTP256:
          rc = ssh_client_ecdh_init(session);
          break;
#endif
#ifdef HAVE_CURVE25519
        case SSH_KEX_CURVE25519_SHA256_LIBSSH_ORG:
          rc = ssh_client_curve25519_init(session);
          break;
#endif
        default:
          rc = SSH_ERROR;
      }
