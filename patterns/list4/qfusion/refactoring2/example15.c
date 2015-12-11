#if defined(__DJGPP__) && (DJGPP_MINOR == 4)
if(!(rc == -1 && *conn->host.name))
#endif
        {
          failf(data, "<url> malformed");
          return CURLE_URL_MALFORMAT;
        }
