#ifndef CURL_DISABLE_SMTP
if(conn->handler->protocol & CURLPROTO_SMTP) {
        result = Curl_smtp_escape_eob(conn, nread);
        if(result)
          return result;
      }
      else
#endif /* CURL_DISABLE_SMTP */

      /* convert LF to CRLF if so asked */
      if((!sending_http_headers) &&
#ifdef CURL_DO_LINEEND_CONV
        /* always convert if we're FTPing in ASCII mode */
         ((data->set.crlf) || (data->set.prefer_ascii))) {
#else
         (data->set.crlf)) {
#endif
        if(data->state.scratch == NULL)
          data->state.scratch = malloc(2*BUFSIZE);
        if(data->state.scratch == NULL) {
          failf (data, "Failed to alloc scratch buffer!");
          return CURLE_OUT_OF_MEMORY;
        }
        /*
         * ASCII/EBCDIC Note: This is presumably a text (not binary)
         * transfer so the data should already be in ASCII.
         * That means the hex values for ASCII CR (0x0d) & LF (0x0a)
         * must be used instead of the escape sequences \r & \n.
         */
        for(i = 0, si = 0; i < nread; i++, si++) {
          if(data->req.upload_fromhere[i] == 0x0a) {
            data->state.scratch[si++] = 0x0d;
            data->state.scratch[si] = 0x0a;
            if(!data->set.crlf) {
              /* we're here only because FTP is in ASCII mode...
                 bump infilesize for the LF we just added */
              data->set.infilesize++;
            }
          }
          else
            data->state.scratch[si] = data->req.upload_fromhere[i];
        }
        if(si != nread) {
          /* only perform the special operation if we really did replace
             anything */
          nread = si;

          /* upload from the new (replaced) buffer instead */
          data->req.upload_fromhere = data->state.scratch;

          /* set the new amount too */
          data->req.upload_present = nread;
        }
      }
