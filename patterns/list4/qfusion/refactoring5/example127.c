#ifdef __VMS
if(is_vms_shell()) {
          /* VMS DCL shell behavior */
          if(!config->showerror) {
            vms_show = VMSSTS_HIDE;
          }
        }
        else
#endif
        {
          if((res!=CURLE_OK) && config->showerror) {
            fprintf(config->errors, "curl: (%d) %s\n", res,
                    errorbuffer[0]? errorbuffer:
                    curl_easy_strerror((CURLcode)res));
            if(CURLE_SSL_CACERT == res) {
              fprintf(config->errors, "%s%s",
                      CURL_CA_CERT_ERRORMSG1,
                      CURL_CA_CERT_ERRORMSG2 );
            }
          }
        }
