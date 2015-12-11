#ifndef CURL_DISABLE_HTTP
if(easy->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)
                multistate(easy, CURLM_STATE_WAITPROXYCONNECT);
              else
#endif
                multistate(easy, CURLM_STATE_WAITCONNECT);
