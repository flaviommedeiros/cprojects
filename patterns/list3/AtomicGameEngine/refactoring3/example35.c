switch(ssl_ver) {
#ifdef SSL2_VERSION_MAJOR /* removed in recent versions */
  case SSL2_VERSION_MAJOR:
    verstr = "SSLv2";
    break;
#endif
#ifdef SSL3_VERSION
  case SSL3_VERSION:
    verstr = "SSLv3";
    break;
#endif
  case TLS1_VERSION:
    verstr = "TLSv1.0";
    break;
#ifdef TLS1_1_VERSION
  case TLS1_1_VERSION:
    verstr = "TLSv1.1";
    break;
#endif
#ifdef TLS1_2_VERSION
  case TLS1_2_VERSION:
    verstr = "TLSv1.2";
    break;
#endif
  default:
    snprintf(unknown, sizeof(unknown), "(%x)", ssl_ver);
    verstr = unknown;
    break;
  }
