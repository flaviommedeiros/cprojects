#ifdef USE_TLS_SRP
if(data->set.ssl.authtype == CURL_TLSAUTH_SRP) {
      infof(data, "Set version TLSv1 for SRP authorisation\n");
      req_method = TLSv1_client_method() ;
    }
    else
#endif
    /* we try to figure out version */
    req_method = SSLv23_client_method();
