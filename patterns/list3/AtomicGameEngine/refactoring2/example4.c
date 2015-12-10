#ifdef HAVE_GSSAPI
if(!conn->sec_complete)
#endif
            if(data->set.verbose)
              Curl_debug(data, CURLINFO_HEADER_IN,
                         pp->linestart_resp, (size_t)perline, conn);
