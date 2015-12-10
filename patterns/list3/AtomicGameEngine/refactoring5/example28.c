#ifdef USE_SPNEGO
if(checkprefix("Negotiate", auth)) {
      int neg;
      *availp |= CURLAUTH_NEGOTIATE;
      authp->avail |= CURLAUTH_NEGOTIATE;

      if(authp->picked == CURLAUTH_NEGOTIATE) {
        if(negdata->state == GSS_AUTHSENT || negdata->state == GSS_AUTHNONE) {
          neg = Curl_input_negotiate(conn, proxy, auth);
          if(neg == 0) {
            DEBUGASSERT(!data->req.newurl);
            data->req.newurl = strdup(data->change.url);
            if(!data->req.newurl)
              return CURLE_OUT_OF_MEMORY;
            data->state.authproblem = FALSE;
            /* we received a GSS auth token and we dealt with it fine */
            negdata->state = GSS_AUTHRECV;
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
      if(checkprefix("NTLM", auth)) {
        *availp |= CURLAUTH_NTLM;
        authp->avail |= CURLAUTH_NTLM;
        if(authp->picked == CURLAUTH_NTLM ||
           authp->picked == CURLAUTH_NTLM_WB) {
          /* NTLM authentication is picked and activated */
          CURLcode result = Curl_input_ntlm(conn, proxy, auth);
          if(!result) {
            data->state.authproblem = FALSE;
#ifdef NTLM_WB_ENABLED
            if(authp->picked == CURLAUTH_NTLM_WB) {
              *availp &= ~CURLAUTH_NTLM;
              authp->avail &= ~CURLAUTH_NTLM;
              *availp |= CURLAUTH_NTLM_WB;
              authp->avail |= CURLAUTH_NTLM_WB;

              /* Get the challenge-message which will be passed to
               * ntlm_auth for generating the type 3 message later */
              while(*auth && ISSPACE(*auth))
                auth++;
              if(checkprefix("NTLM", auth)) {
                auth += strlen("NTLM");
                while(*auth && ISSPACE(*auth))
                  auth++;
                if(*auth)
                  if((conn->challenge_header = strdup(auth)) == NULL)
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
        if(checkprefix("Digest", auth)) {
          if((authp->avail & CURLAUTH_DIGEST) != 0) {
            infof(data, "Ignoring duplicate digest auth header.\n");
          }
          else {
            CURLcode result;
            *availp |= CURLAUTH_DIGEST;
            authp->avail |= CURLAUTH_DIGEST;

            /* We call this function on input Digest headers even if Digest
             * authentication isn't activated yet, as we need to store the
             * incoming data from this header in case we are gonna use
             * Digest. */
            result = Curl_input_digest(conn, proxy, auth);
            if(result) {
              infof(data, "Authentication problem. Ignoring this.\n");
              data->state.authproblem = TRUE;
            }
          }
        }
        else
#endif
          if(checkprefix("Basic", auth)) {
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
