switch(data->set.ssl.version) {
  case CURL_SSLVERSION_SSLv3:
#ifdef USE_TLS_SRP
    if(data->set.ssl.authtype == CURL_TLSAUTH_SRP) {
      infof(data, "Set version TLSv1.x for SRP authorisation\n");
    }
#endif
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_TLSv1;
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
    ctx_options |= SSL_OP_NO_TLSv1_1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
#endif
    break;

  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
    break;

  case CURL_SSLVERSION_TLSv1_0:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
    ctx_options |= SSL_OP_NO_TLSv1_1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
#endif
    break;

#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
  case CURL_SSLVERSION_TLSv1_1:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
    ctx_options |= SSL_OP_NO_TLSv1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
    break;

  case CURL_SSLVERSION_TLSv1_2:
    ctx_options |= SSL_OP_NO_SSLv2;
    ctx_options |= SSL_OP_NO_SSLv3;
    ctx_options |= SSL_OP_NO_TLSv1;
    ctx_options |= SSL_OP_NO_TLSv1_1;
    break;
#endif

#ifndef OPENSSL_NO_SSL2
  case CURL_SSLVERSION_SSLv2:
    ctx_options |= SSL_OP_NO_SSLv3;
    ctx_options |= SSL_OP_NO_TLSv1;
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
    ctx_options |= SSL_OP_NO_TLSv1_1;
    ctx_options |= SSL_OP_NO_TLSv1_2;
#endif
    break;
#endif

  default:
    failf(data, "Unsupported SSL protocol version");
    return CURLE_SSL_CONNECT_ERROR;
  }
