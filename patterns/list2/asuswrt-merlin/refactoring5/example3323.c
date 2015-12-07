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
           * incoming data from this header in case we are gonna use Digest. */
          dig = Curl_input_digest(conn, (bool)(httpcode == 407), start);

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
