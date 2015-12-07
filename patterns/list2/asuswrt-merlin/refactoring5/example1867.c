#ifdef USE_NTLM
if(authstatus->picked == CURLAUTH_NTLM) {
    auth="NTLM";
    result = Curl_output_ntlm(conn, proxy);
    if(result)
      return result;
  }
  else
#endif
#ifndef CURL_DISABLE_CRYPTO_AUTH
  if(authstatus->picked == CURLAUTH_DIGEST) {
    auth="Digest";
    result = Curl_output_digest(conn,
                                proxy,
                                (const unsigned char *)request,
                                (const unsigned char *)path);
    if(result)
      return result;
  }
  else
#endif
  if(authstatus->picked == CURLAUTH_BASIC) {
    /* Basic */
    if((proxy && conn->bits.proxy_user_passwd &&
       !Curl_checkheaders(data, "Proxy-authorization:")) ||
       (!proxy && conn->bits.user_passwd &&
       !Curl_checkheaders(data, "Authorization:"))) {
      auth="Basic";
      result = http_output_basic(conn, proxy);
      if(result)
        return result;
    }
    /* NOTE: this function should set 'done' TRUE, as the other auth
       functions work that way */
    authstatus->done = TRUE;
  }
