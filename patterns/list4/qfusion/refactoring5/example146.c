#ifdef USE_HTTP_NEGOTIATE
if(checkprefix("GSS-Negotiate", start) ||
       checkprefix("Negotiate", start)) {
      int neg;
      *availp |= CURLAUTH_GSSNEGOTIATE;
      authp->avail |= CURLAUTH_GSSNEGOTIATE;

      if(authp->picked == CURLAUTH_GSSNEGOTIATE) {
        if(data->state.negotiate.state == GSS_AUTHSENT) {
          /* if we sent GSS authentication in the outgoing request and we get
             this back, we're in trouble */
          infof(data, "Authentication problem. Ignoring this.\n");
          data->state.authproblem = TRUE;
        }
        else {
          neg = Curl_input_negotiate(conn, (bool)(httpcode == 407), start);
          if(neg == 0) {
            DEBUGASSERT(!data->req.newurl);
            data->req.newurl = strdup(data->change.url);
            if(!data->req.newurl)
              return CURLE_OUT_OF_MEMORY;
            data->state.authproblem = FALSE;
            /* we received GSS auth info and we dealt with it fine */
            data->state.negotiate.state = GSS_AUTHRECV;
          }
          else
            data->state.authproblem = TRUE;
        }
      }
    }
    else
#endif
#ifdef USE_NTLM
      /* NTLM support requires the SSL crypto libs */
      if(checkprefix("NTLM", start)) {
        *availp |= CURLAUTH_NTLM;
        authp->avail |= CURLAUTH_NTLM;
        if(authp->picked == CURLAUTH_NTLM ||
           authp->picked == CURLAUTH_NTLM_WB) {
          /* NTLM authentication is picked and activated */
          CURLcode ntlm =
            Curl_input_ntlm(conn, (httpcode == 407)?TRUE:FALSE, start);
          if(CURLE_OK == ntlm) {
            data->state.authproblem = FALSE;
#ifdef NTLM_WB_ENABLED
            if(authp->picked == CURLAUTH_NTLM_WB) {
              *availp &= ~CURLAUTH_NTLM;
              authp->avail &= ~CURLAUTH_NTLM;
              *availp |= CURLAUTH_NTLM_WB;
              authp->avail |= CURLAUTH_NTLM_WB;

              /* Get the challenge-message which will be passed to
               * ntlm_auth for generating the type 3 message later */
              while(*start && ISSPACE(*start))
                start++;
              if(checkprefix("NTLM", start)) {
                start += strlen("NTLM");
                while(*start && ISSPACE(*start))
                  start++;
                if(*start)
                  if((conn->challenge_header = strdup(start)) == NULL)
                    return CURLE_OUT_OF_MEMORY;
              }
            }
#endif
          }
          else {
            infof(data, "Authentication problem. Ignoring this.\n");
            data->state.authproblem = TRUE;
          }
        }
      }
      else
#endif
#ifndef CURL_DISABLE_CRYPTO_AUTH
        if(checkprefix("Digest", start)) {
          if((authp->avail & CURLAUTH_DIGEST) != 0) {
            infof(data, "Ignoring duplicate digest auth header.\n");
          }
          else {
            CURLdigest dig;
            *availp |= CURLAUTH_DIGEST;
            authp->avail |= CURLAUTH_DIGEST;

            /* We call this function on input Digest headers even if Digest
             * authentication isn't activated yet, as we need to store the
             * incoming data from this header in case we are gonna use
             * Digest. */
            dig = Curl_input_digest(conn, (httpcode == 407)?TRUE:FALSE, start);

            if(CURLDIGEST_FINE != dig) {
              infof(data, "Authentication problem. Ignoring this.\n");
              data->state.authproblem = TRUE;
            }
          }
        }
        else
#endif
          if(checkprefix("Basic", start)) {
            *availp |= CURLAUTH_BASIC;
            authp->avail |= CURLAUTH_BASIC;
            if(authp->picked == CURLAUTH_BASIC) {
              /* We asked for Basic authentication but got a 40X back
                 anyway, which basically means our name+password isn't
                 valid. */
              authp->avail = CURLAUTH_NONE;
              infof(data, "Authentication problem. Ignoring this.\n");
              data->state.authproblem = TRUE;
            }
          }
