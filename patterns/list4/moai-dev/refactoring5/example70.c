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
#define CURL_CA_CERT_ERRORMSG1 \
"More details here: http://curl.haxx.se/docs/sslcerts.html\n\n" \
"curl performs SSL certificate verification by default, using a \"bundle\"\n" \
" of Certificate Authority (CA) public keys (CA certs). If the default\n" \
" bundle file isn't adequate, you can specify an alternate file\n" \
" using the --cacert option.\n"

#define CURL_CA_CERT_ERRORMSG2 \
"If this HTTPS server uses a certificate signed by a CA represented in\n" \
" the bundle, the certificate verification probably failed due to a\n" \
" problem with the certificate (it might be expired, or the name might\n" \
" not match the domain name in the URL).\n" \
"If you'd like to turn off curl's verification of the certificate, use\n" \
" the -k (or --insecure) option.\n"

              fprintf(config->errors, "%s%s",
                      CURL_CA_CERT_ERRORMSG1,
                      CURL_CA_CERT_ERRORMSG2 );
            }
          }
        }
