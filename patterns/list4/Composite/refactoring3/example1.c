switch (cstate->resp_type) { 

  case CHAP_DIGEST_MD5:
    MD5Init(&mdContext);
    MD5Update(&mdContext, &cstate->resp_id, 1);
    MD5Update(&mdContext, (u_char*)secret, secret_len);
    MD5Update(&mdContext, rchallenge, rchallenge_len);
    MD5Final(hash, &mdContext);
    BCOPY(hash, cstate->response, MD5_SIGNATURE_SIZE);
    cstate->resp_length = MD5_SIGNATURE_SIZE;
    break;
  
#ifdef CHAPMS
  case CHAP_MICROSOFT:
    ChapMS(cstate, rchallenge, rchallenge_len, secret, secret_len);
    break;
#endif

  default:
    CHAPDEBUG((LOG_INFO, "unknown digest type %d\n", cstate->resp_type));
    return;
  }
