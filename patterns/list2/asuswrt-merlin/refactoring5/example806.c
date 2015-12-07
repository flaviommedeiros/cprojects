#ifndef CURL_DISABLE_HTTP
if(easy->easy_conn->bits.tunnel_connecting)
                multistate(easy, CURLM_STATE_WAITPROXYCONNECT);
              else
#endif
                multistate(easy, CURLM_STATE_WAITCONNECT);
