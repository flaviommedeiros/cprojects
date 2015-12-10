#ifndef CURL_DISABLE_HTTP
if(data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)
            multistate(data, CURLM_STATE_WAITPROXYCONNECT);
          else
#endif
            multistate(data, CURLM_STATE_PROTOCONNECT);
