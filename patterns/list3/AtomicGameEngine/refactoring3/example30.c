switch(option) {
  case CURLOPT_DNS_CACHE_TIMEOUT:
    data->set.dns_cache_timeout = va_arg(param, long);
    break;
  case CURLOPT_DNS_USE_GLOBAL_CACHE:
    /* remember we want this enabled */
    arg = va_arg(param, long);
    data->set.global_dns_cache = (0 != arg)?TRUE:FALSE;
    break;
  case CURLOPT_SSL_CIPHER_LIST:
    /* set a list of cipher we want to use in the SSL connection */
    result = setstropt(&data->set.str[STRING_SSL_CIPHER_LIST],
                       va_arg(param, char *));
    break;

  case CURLOPT_RANDOM_FILE:
    /*
     * This is the path name to a file that contains random data to seed
     * the random SSL stuff with. The file is only used for reading.
     */
    result = setstropt(&data->set.str[STRING_SSL_RANDOM_FILE],
                       va_arg(param, char *));
    break;
  case CURLOPT_EGDSOCKET:
    /*
     * The Entropy Gathering Daemon socket pathname
     */
    result = setstropt(&data->set.str[STRING_SSL_EGDSOCKET],
                       va_arg(param, char *));
    break;
  case CURLOPT_MAXCONNECTS:
    /*
     * Set the absolute number of maximum simultaneous alive connection that
     * libcurl is allowed to have.
     */
    data->set.maxconnects = va_arg(param, long);
    break;
  case CURLOPT_FORBID_REUSE:
    /*
     * When this transfer is done, it must not be left to be reused by a
     * subsequent transfer but shall be closed immediately.
     */
    data->set.reuse_forbid = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_FRESH_CONNECT:
    /*
     * This transfer shall not use a previously cached connection but
     * should be made with a fresh new connect!
     */
    data->set.reuse_fresh = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_VERBOSE:
    /*
     * Verbose means infof() calls that give a lot of information about
     * the connection and transfer procedures as well as internal choices.
     */
    data->set.verbose = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_HEADER:
    /*
     * Set to include the header in the general data output stream.
     */
    data->set.include_header = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_NOPROGRESS:
    /*
     * Shut off the internal supported progress meter
     */
    data->set.hide_progress = (0 != va_arg(param, long))?TRUE:FALSE;
    if(data->set.hide_progress)
      data->progress.flags |= PGRS_HIDE;
    else
      data->progress.flags &= ~PGRS_HIDE;
    break;
  case CURLOPT_NOBODY:
    /*
     * Do not include the body part in the output data stream.
     */
    data->set.opt_no_body = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_FAILONERROR:
    /*
     * Don't output the >=400 error code HTML-page, but instead only
     * return error.
     */
    data->set.http_fail_on_error = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_UPLOAD:
  case CURLOPT_PUT:
    /*
     * We want to sent data to the remote host. If this is HTTP, that equals
     * using the PUT request.
     */
    data->set.upload = (0 != va_arg(param, long))?TRUE:FALSE;
    if(data->set.upload) {
      /* If this is HTTP, PUT is what's needed to "upload" */
      data->set.httpreq = HTTPREQ_PUT;
      data->set.opt_no_body = FALSE; /* this is implied */
    }
    else
      /* In HTTP, the opposite of upload is GET (unless NOBODY is true as
         then this can be changed to HEAD later on) */
      data->set.httpreq = HTTPREQ_GET;
    break;
  case CURLOPT_FILETIME:
    /*
     * Try to get the file time of the remote document. The time will
     * later (possibly) become available using curl_easy_getinfo().
     */
    data->set.get_filetime = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_FTP_CREATE_MISSING_DIRS:
    /*
     * An FTP option that modifies an upload to create missing directories on
     * the server.
     */
    switch(va_arg(param, long)) {
    case 0:
      data->set.ftp_create_missing_dirs = 0;
      break;
    case 1:
      data->set.ftp_create_missing_dirs = 1;
      break;
    case 2:
      data->set.ftp_create_missing_dirs = 2;
      break;
    default:
      /* reserve other values for future use */
      result = CURLE_UNKNOWN_OPTION;
      break;
    }
    break;
  case CURLOPT_SERVER_RESPONSE_TIMEOUT:
    /*
     * Option that specifies how quickly an server response must be obtained
     * before it is considered failure. For pingpong protocols.
     */
    data->set.server_response_timeout = va_arg( param , long ) * 1000;
    break;
  case CURLOPT_TFTP_BLKSIZE:
    /*
     * TFTP option that specifies the block size to use for data transmission
     */
    data->set.tftp_blksize = va_arg(param, long);
    break;
  case CURLOPT_DIRLISTONLY:
    /*
     * An option that changes the command to one that asks for a list
     * only, no file info details.
     */
    data->set.ftp_list_only = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_APPEND:
    /*
     * We want to upload and append to an existing file.
     */
    data->set.ftp_append = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_FTP_FILEMETHOD:
    /*
     * How do access files over FTP.
     */
    data->set.ftp_filemethod = (curl_ftpfile)va_arg(param, long);
    break;
  case CURLOPT_NETRC:
    /*
     * Parse the $HOME/.netrc file
     */
    data->set.use_netrc = (enum CURL_NETRC_OPTION)va_arg(param, long);
    break;
  case CURLOPT_NETRC_FILE:
    /*
     * Use this file instead of the $HOME/.netrc file
     */
    result = setstropt(&data->set.str[STRING_NETRC_FILE],
                       va_arg(param, char *));
    break;
  case CURLOPT_TRANSFERTEXT:
    /*
     * This option was previously named 'FTPASCII'. Renamed to work with
     * more protocols than merely FTP.
     *
     * Transfer using ASCII (instead of BINARY).
     */
    data->set.prefer_ascii = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_TIMECONDITION:
    /*
     * Set HTTP time condition. This must be one of the defines in the
     * curl/curl.h header file.
     */
    data->set.timecondition = (curl_TimeCond)va_arg(param, long);
    break;
  case CURLOPT_TIMEVALUE:
    /*
     * This is the value to compare with the remote document with the
     * method set with CURLOPT_TIMECONDITION
     */
    data->set.timevalue = (time_t)va_arg(param, long);
    break;
  case CURLOPT_SSLVERSION:
    /*
     * Set explicit SSL version to try to connect with, as some SSL
     * implementations are lame.
     */
    data->set.ssl.version = va_arg(param, long);
    break;

#ifndef CURL_DISABLE_HTTP
  case CURLOPT_AUTOREFERER:
    /*
     * Switch on automatic referer that gets set if curl follows locations.
     */
    data->set.http_auto_referer = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_ACCEPT_ENCODING:
    /*
     * String to use at the value of Accept-Encoding header.
     *
     * If the encoding is set to "" we use an Accept-Encoding header that
     * encompasses all the encodings we support.
     * If the encoding is set to NULL we don't send an Accept-Encoding header
     * and ignore an received Content-Encoding header.
     *
     */
    argptr = va_arg(param, char *);
    result = setstropt(&data->set.str[STRING_ENCODING],
                       (argptr && !*argptr)?
                       (char *) ALL_CONTENT_ENCODINGS: argptr);
    break;

  case CURLOPT_TRANSFER_ENCODING:
    data->set.http_transfer_encoding = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FOLLOWLOCATION:
    /*
     * Follow Location: header hints on a HTTP-server.
     */
    data->set.http_follow_location = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_UNRESTRICTED_AUTH:
    /*
     * Send authentication (user+password) when following locations, even when
     * hostname changed.
     */
    data->set.http_disable_hostname_check_before_authentication =
      (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_MAXREDIRS:
    /*
     * The maximum amount of hops you allow curl to follow Location:
     * headers. This should mostly be used to detect never-ending loops.
     */
    data->set.maxredirs = va_arg(param, long);
    break;

  case CURLOPT_POSTREDIR:
  {
    /*
     * Set the behaviour of POST when redirecting
     * CURL_REDIR_GET_ALL - POST is changed to GET after 301 and 302
     * CURL_REDIR_POST_301 - POST is kept as POST after 301
     * CURL_REDIR_POST_302 - POST is kept as POST after 302
     * CURL_REDIR_POST_303 - POST is kept as POST after 303
     * CURL_REDIR_POST_ALL - POST is kept as POST after 301, 302 and 303
     * other - POST is kept as POST after 301 and 302
     */
    int postRedir = curlx_sltosi(va_arg(param, long));
    data->set.keep_post = postRedir & CURL_REDIR_POST_ALL;
  }
  break;

  case CURLOPT_POST:
    /* Does this option serve a purpose anymore? Yes it does, when
       CURLOPT_POSTFIELDS isn't used and the POST data is read off the
       callback! */
    if(va_arg(param, long)) {
      data->set.httpreq = HTTPREQ_POST;
      data->set.opt_no_body = FALSE; /* this is implied */
    }
    else
      data->set.httpreq = HTTPREQ_GET;
    break;

  case CURLOPT_COPYPOSTFIELDS:
    /*
     * A string with POST data. Makes curl HTTP POST. Even if it is NULL.
     * If needed, CURLOPT_POSTFIELDSIZE must have been set prior to
     *  CURLOPT_COPYPOSTFIELDS and not altered later.
     */
    argptr = va_arg(param, char *);

    if(!argptr || data->set.postfieldsize == -1)
      result = setstropt(&data->set.str[STRING_COPYPOSTFIELDS], argptr);
    else {
      /*
       *  Check that requested length does not overflow the size_t type.
       */

      if((data->set.postfieldsize < 0) ||
         ((sizeof(curl_off_t) != sizeof(size_t)) &&
          (data->set.postfieldsize > (curl_off_t)((size_t)-1))))
        result = CURLE_OUT_OF_MEMORY;
      else {
        char * p;

        (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);

        /* Allocate even when size == 0. This satisfies the need of possible
           later address compare to detect the COPYPOSTFIELDS mode, and
           to mark that postfields is used rather than read function or
           form data.
        */
        p = malloc((size_t)(data->set.postfieldsize?
                            data->set.postfieldsize:1));

        if(!p)
          result = CURLE_OUT_OF_MEMORY;
        else {
          if(data->set.postfieldsize)
            memcpy(p, argptr, (size_t)data->set.postfieldsize);

          data->set.str[STRING_COPYPOSTFIELDS] = p;
        }
      }
    }

    data->set.postfields = data->set.str[STRING_COPYPOSTFIELDS];
    data->set.httpreq = HTTPREQ_POST;
    break;

  case CURLOPT_POSTFIELDS:
    /*
     * Like above, but use static data instead of copying it.
     */
    data->set.postfields = va_arg(param, void *);
    /* Release old copied data. */
    (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
    data->set.httpreq = HTTPREQ_POST;
    break;

  case CURLOPT_POSTFIELDSIZE:
    /*
     * The size of the POSTFIELD data to prevent libcurl to do strlen() to
     * figure it out. Enables binary posts.
     */
    bigsize = va_arg(param, long);

    if(data->set.postfieldsize < bigsize &&
       data->set.postfields == data->set.str[STRING_COPYPOSTFIELDS]) {
      /* Previous CURLOPT_COPYPOSTFIELDS is no longer valid. */
      (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
      data->set.postfields = NULL;
    }

    data->set.postfieldsize = bigsize;
    break;

  case CURLOPT_POSTFIELDSIZE_LARGE:
    /*
     * The size of the POSTFIELD data to prevent libcurl to do strlen() to
     * figure it out. Enables binary posts.
     */
    bigsize = va_arg(param, curl_off_t);

    if(data->set.postfieldsize < bigsize &&
       data->set.postfields == data->set.str[STRING_COPYPOSTFIELDS]) {
      /* Previous CURLOPT_COPYPOSTFIELDS is no longer valid. */
      (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
      data->set.postfields = NULL;
    }

    data->set.postfieldsize = bigsize;
    break;

  case CURLOPT_HTTPPOST:
    /*
     * Set to make us do HTTP POST
     */
    data->set.httppost = va_arg(param, struct curl_httppost *);
    data->set.httpreq = HTTPREQ_POST_FORM;
    data->set.opt_no_body = FALSE; /* this is implied */
    break;

  case CURLOPT_REFERER:
    /*
     * String to set in the HTTP Referer: field.
     */
    if(data->change.referer_alloc) {
      Curl_safefree(data->change.referer);
      data->change.referer_alloc = FALSE;
    }
    result = setstropt(&data->set.str[STRING_SET_REFERER],
                       va_arg(param, char *));
    data->change.referer = data->set.str[STRING_SET_REFERER];
    break;

  case CURLOPT_USERAGENT:
    /*
     * String to use in the HTTP User-Agent field
     */
    result = setstropt(&data->set.str[STRING_USERAGENT],
                       va_arg(param, char *));
    break;

  case CURLOPT_HTTPHEADER:
    /*
     * Set a list with HTTP headers to use (or replace internals with)
     */
    data->set.headers = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_PROXYHEADER:
    /*
     * Set a list with proxy headers to use (or replace internals with)
     *
     * Since CURLOPT_HTTPHEADER was the only way to set HTTP headers for a
     * long time we remain doing it this way until CURLOPT_PROXYHEADER is
     * used. As soon as this option has been used, if set to anything but
     * NULL, custom headers for proxies are only picked from this list.
     *
     * Set this option to NULL to restore the previous behavior.
     */
    data->set.proxyheaders = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_HEADEROPT:
    /*
     * Set header option.
     */
    arg = va_arg(param, long);
    data->set.sep_headers = (arg & CURLHEADER_SEPARATE)? TRUE: FALSE;
    break;

  case CURLOPT_HTTP200ALIASES:
    /*
     * Set a list of aliases for HTTP 200 in response header
     */
    data->set.http200aliases = va_arg(param, struct curl_slist *);
    break;

#if !defined(CURL_DISABLE_COOKIES)
  case CURLOPT_COOKIE:
    /*
     * Cookie string to send to the remote server in the request.
     */
    result = setstropt(&data->set.str[STRING_COOKIE],
                       va_arg(param, char *));
    break;

  case CURLOPT_COOKIEFILE:
    /*
     * Set cookie file to read and parse. Can be used multiple times.
     */
    argptr = (char *)va_arg(param, void *);
    if(argptr) {
      struct curl_slist *cl;
      /* append the cookie file name to the list of file names, and deal with
         them later */
      cl = curl_slist_append(data->change.cookielist, argptr);
      if(!cl) {
        curl_slist_free_all(data->change.cookielist);
        data->change.cookielist = NULL;
        return CURLE_OUT_OF_MEMORY;
      }
      data->change.cookielist = cl; /* store the list for later use */
    }
    break;

  case CURLOPT_COOKIEJAR:
    /*
     * Set cookie file name to dump all cookies to when we're done.
     */
  {
    struct CookieInfo *newcookies;
    result = setstropt(&data->set.str[STRING_COOKIEJAR],
                       va_arg(param, char *));

    /*
     * Activate the cookie parser. This may or may not already
     * have been made.
     */
    newcookies = Curl_cookie_init(data, NULL, data->cookies,
                                  data->set.cookiesession);
    if(!newcookies)
      result = CURLE_OUT_OF_MEMORY;
    data->cookies = newcookies;
  }
    break;

  case CURLOPT_COOKIESESSION:
    /*
     * Set this option to TRUE to start a new "cookie session". It will
     * prevent the forthcoming read-cookies-from-file actions to accept
     * cookies that are marked as being session cookies, as they belong to a
     * previous session.
     *
     * In the original Netscape cookie spec, "session cookies" are cookies
     * with no expire date set. RFC2109 describes the same action if no
     * 'Max-Age' is set and RFC2965 includes the RFC2109 description and adds
     * a 'Discard' action that can enforce the discard even for cookies that
     * have a Max-Age.
     *
     * We run mostly with the original cookie spec, as hardly anyone implements
     * anything else.
     */
    data->set.cookiesession = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_COOKIELIST:
    argptr = va_arg(param, char *);

    if(argptr == NULL)
      break;

    if(Curl_raw_equal(argptr, "ALL")) {
      /* clear all cookies */
      Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
      Curl_cookie_clearall(data->cookies);
      Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
    }
    else if(Curl_raw_equal(argptr, "SESS")) {
      /* clear session cookies */
      Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
      Curl_cookie_clearsess(data->cookies);
      Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
    }
    else if(Curl_raw_equal(argptr, "FLUSH")) {
      /* flush cookies to file, takes care of the locking */
      Curl_flush_cookies(data, 0);
    }
    else if(Curl_raw_equal(argptr, "RELOAD")) {
      /* reload cookies from file */
      Curl_cookie_loadfiles(data);
      break;
    }
    else {
      if(!data->cookies)
        /* if cookie engine was not running, activate it */
        data->cookies = Curl_cookie_init(data, NULL, NULL, TRUE);

      argptr = strdup(argptr);
      if(!argptr || !data->cookies) {
        result = CURLE_OUT_OF_MEMORY;
        Curl_safefree(argptr);
      }
      else {
        Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);

        if(checkprefix("Set-Cookie:", argptr))
          /* HTTP Header format line */
          Curl_cookie_add(data, data->cookies, TRUE, argptr + 11, NULL, NULL);

        else
          /* Netscape format line */
          Curl_cookie_add(data, data->cookies, FALSE, argptr, NULL, NULL);

        Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
        free(argptr);
      }
    }

    break;
#endif /* CURL_DISABLE_COOKIES */

  case CURLOPT_HTTPGET:
    /*
     * Set to force us do HTTP GET
     */
    if(va_arg(param, long)) {
      data->set.httpreq = HTTPREQ_GET;
      data->set.upload = FALSE; /* switch off upload */
      data->set.opt_no_body = FALSE; /* this is implied */
    }
    break;

  case CURLOPT_HTTP_VERSION:
    /*
     * This sets a requested HTTP version to be used. The value is one of
     * the listed enums in curl/curl.h.
     */
    arg = va_arg(param, long);
#ifndef USE_NGHTTP2
    if(arg == CURL_HTTP_VERSION_2_0)
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif
    data->set.httpversion = arg;
    break;

  case CURLOPT_HTTPAUTH:
    /*
     * Set HTTP Authentication type BITMASK.
     */
  {
    int bitcheck;
    bool authbits;
    unsigned long auth = va_arg(param, unsigned long);

    if(auth == CURLAUTH_NONE) {
      data->set.httpauth = auth;
      break;
    }

    /* the DIGEST_IE bit is only used to set a special marker, for all the
       rest we need to handle it as normal DIGEST */
    data->state.authhost.iestyle = (auth & CURLAUTH_DIGEST_IE)?TRUE:FALSE;

    if(auth & CURLAUTH_DIGEST_IE) {
      auth |= CURLAUTH_DIGEST; /* set standard digest bit */
      auth &= ~CURLAUTH_DIGEST_IE; /* unset ie digest bit */
    }

    /* switch off bits we can't support */
#ifndef USE_NTLM
    auth &= ~CURLAUTH_NTLM;    /* no NTLM support */
    auth &= ~CURLAUTH_NTLM_WB; /* no NTLM_WB support */
#elif !defined(NTLM_WB_ENABLED)
    auth &= ~CURLAUTH_NTLM_WB; /* no NTLM_WB support */
#endif
#ifndef USE_SPNEGO
    auth &= ~CURLAUTH_NEGOTIATE; /* no Negotiate (SPNEGO) auth without
                                    GSS-API or SSPI */
#endif

    /* check if any auth bit lower than CURLAUTH_ONLY is still set */
    bitcheck = 0;
    authbits = FALSE;
    while(bitcheck < 31) {
      if(auth & (1UL << bitcheck++)) {
        authbits = TRUE;
        break;
      }
    }
    if(!authbits)
      return CURLE_NOT_BUILT_IN; /* no supported types left! */

    data->set.httpauth = auth;
  }
  break;

  case CURLOPT_EXPECT_100_TIMEOUT_MS:
    /*
     * Time to wait for a response to a HTTP request containing an
     * Expect: 100-continue header before sending the data anyway.
     */
    data->set.expect_100_timeout = va_arg(param, long);
    break;

#endif   /* CURL_DISABLE_HTTP */

  case CURLOPT_CUSTOMREQUEST:
    /*
     * Set a custom string to use as request
     */
    result = setstropt(&data->set.str[STRING_CUSTOMREQUEST],
                       va_arg(param, char *));

    /* we don't set
       data->set.httpreq = HTTPREQ_CUSTOM;
       here, we continue as if we were using the already set type
       and this just changes the actual request keyword */
    break;

#ifndef CURL_DISABLE_PROXY
  case CURLOPT_HTTPPROXYTUNNEL:
    /*
     * Tunnel operations through the proxy instead of normal proxy use
     */
    data->set.tunnel_thru_httpproxy = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_PROXYPORT:
    /*
     * Explicitly set HTTP proxy port number.
     */
    data->set.proxyport = va_arg(param, long);
    break;

  case CURLOPT_PROXYAUTH:
    /*
     * Set HTTP Authentication type BITMASK.
     */
  {
    int bitcheck;
    bool authbits;
    unsigned long auth = va_arg(param, unsigned long);

    if(auth == CURLAUTH_NONE) {
      data->set.proxyauth = auth;
      break;
    }

    /* the DIGEST_IE bit is only used to set a special marker, for all the
       rest we need to handle it as normal DIGEST */
    data->state.authproxy.iestyle = (auth & CURLAUTH_DIGEST_IE)?TRUE:FALSE;

    if(auth & CURLAUTH_DIGEST_IE) {
      auth |= CURLAUTH_DIGEST; /* set standard digest bit */
      auth &= ~CURLAUTH_DIGEST_IE; /* unset ie digest bit */
    }
    /* switch off bits we can't support */
#ifndef USE_NTLM
    auth &= ~CURLAUTH_NTLM;    /* no NTLM support */
    auth &= ~CURLAUTH_NTLM_WB; /* no NTLM_WB support */
#elif !defined(NTLM_WB_ENABLED)
    auth &= ~CURLAUTH_NTLM_WB; /* no NTLM_WB support */
#endif
#ifndef USE_SPNEGO
    auth &= ~CURLAUTH_NEGOTIATE; /* no Negotiate (SPNEGO) auth without
                                    GSS-API or SSPI */
#endif

    /* check if any auth bit lower than CURLAUTH_ONLY is still set */
    bitcheck = 0;
    authbits = FALSE;
    while(bitcheck < 31) {
      if(auth & (1UL << bitcheck++)) {
        authbits = TRUE;
        break;
      }
    }
    if(!authbits)
      return CURLE_NOT_BUILT_IN; /* no supported types left! */

    data->set.proxyauth = auth;
  }
  break;

  case CURLOPT_PROXY:
    /*
     * Set proxy server:port to use as HTTP proxy.
     *
     * If the proxy is set to "" we explicitly say that we don't want to use a
     * proxy (even though there might be environment variables saying so).
     *
     * Setting it to NULL, means no proxy but allows the environment variables
     * to decide for us.
     */
    result = setstropt(&data->set.str[STRING_PROXY],
                       va_arg(param, char *));
    break;

  case CURLOPT_PROXYTYPE:
    /*
     * Set proxy type. HTTP/HTTP_1_0/SOCKS4/SOCKS4a/SOCKS5/SOCKS5_HOSTNAME
     */
    data->set.proxytype = (curl_proxytype)va_arg(param, long);
    break;

  case CURLOPT_PROXY_TRANSFER_MODE:
    /*
     * set transfer mode (;type=<a|i>) when doing FTP via an HTTP proxy
     */
    switch (va_arg(param, long)) {
    case 0:
      data->set.proxy_transfer_mode = FALSE;
      break;
    case 1:
      data->set.proxy_transfer_mode = TRUE;
      break;
    default:
      /* reserve other values for future use */
      result = CURLE_UNKNOWN_OPTION;
      break;
    }
    break;
#endif   /* CURL_DISABLE_PROXY */

#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  case CURLOPT_SOCKS5_GSSAPI_SERVICE:
    /*
     * Set GSS-API service name
     */
    result = setstropt(&data->set.str[STRING_SOCKS5_GSSAPI_SERVICE],
                       va_arg(param, char *));
    break;

  case CURLOPT_SOCKS5_GSSAPI_NEC:
    /*
     * set flag for nec socks5 support
     */
    data->set.socks5_gssapi_nec = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
#endif

  case CURLOPT_HEADERDATA:
    /*
     * Custom pointer to pass the header write callback function
     */
    data->set.writeheader = (void *)va_arg(param, void *);
    break;
  case CURLOPT_ERRORBUFFER:
    /*
     * Error buffer provided by the caller to get the human readable
     * error string in.
     */
    data->set.errorbuffer = va_arg(param, char *);
    break;
  case CURLOPT_WRITEDATA:
    /*
     * FILE pointer to write to. Or possibly
     * used as argument to the write callback.
     */
    data->set.out = va_arg(param, void *);
    break;
  case CURLOPT_FTPPORT:
    /*
     * Use FTP PORT, this also specifies which IP address to use
     */
    result = setstropt(&data->set.str[STRING_FTPPORT],
                       va_arg(param, char *));
    data->set.ftp_use_port = (NULL != data->set.str[STRING_FTPPORT]) ?
                             TRUE:FALSE;
    break;

  case CURLOPT_FTP_USE_EPRT:
    data->set.ftp_use_eprt = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_USE_EPSV:
    data->set.ftp_use_epsv = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_USE_PRET:
    data->set.ftp_use_pret = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_SSL_CCC:
    data->set.ftp_ccc = (curl_ftpccc)va_arg(param, long);
    break;

  case CURLOPT_FTP_SKIP_PASV_IP:
    /*
     * Enable or disable FTP_SKIP_PASV_IP, which will disable/enable the
     * bypass of the IP address in PASV responses.
     */
    data->set.ftp_skip_ip = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_READDATA:
    /*
     * FILE pointer to read the file to be uploaded from. Or possibly
     * used as argument to the read callback.
     */
    data->set.in = va_arg(param, void *);
    break;
  case CURLOPT_INFILESIZE:
    /*
     * If known, this should inform curl about the file size of the
     * to-be-uploaded file.
     */
    data->set.filesize = va_arg(param, long);
    break;
  case CURLOPT_INFILESIZE_LARGE:
    /*
     * If known, this should inform curl about the file size of the
     * to-be-uploaded file.
     */
    data->set.filesize = va_arg(param, curl_off_t);
    break;
  case CURLOPT_LOW_SPEED_LIMIT:
    /*
     * The low speed limit that if transfers are below this for
     * CURLOPT_LOW_SPEED_TIME, the transfer is aborted.
     */
    data->set.low_speed_limit=va_arg(param, long);
    break;
  case CURLOPT_MAX_SEND_SPEED_LARGE:
    /*
     * When transfer uploads are faster then CURLOPT_MAX_SEND_SPEED_LARGE
     * bytes per second the transfer is throttled..
     */
    data->set.max_send_speed=va_arg(param, curl_off_t);
    break;
  case CURLOPT_MAX_RECV_SPEED_LARGE:
    /*
     * When receiving data faster than CURLOPT_MAX_RECV_SPEED_LARGE bytes per
     * second the transfer is throttled..
     */
    data->set.max_recv_speed=va_arg(param, curl_off_t);
    break;
  case CURLOPT_LOW_SPEED_TIME:
    /*
     * The low speed time that if transfers are below the set
     * CURLOPT_LOW_SPEED_LIMIT during this time, the transfer is aborted.
     */
    data->set.low_speed_time=va_arg(param, long);
    break;
  case CURLOPT_URL:
    /*
     * The URL to fetch.
     */
    if(data->change.url_alloc) {
      /* the already set URL is allocated, free it first! */
      Curl_safefree(data->change.url);
      data->change.url_alloc = FALSE;
    }
    result = setstropt(&data->set.str[STRING_SET_URL],
                       va_arg(param, char *));
    data->change.url = data->set.str[STRING_SET_URL];
    break;
  case CURLOPT_PORT:
    /*
     * The port number to use when getting the URL
     */
    data->set.use_port = va_arg(param, long);
    break;
  case CURLOPT_TIMEOUT:
    /*
     * The maximum time you allow curl to use for a single transfer
     * operation.
     */
    data->set.timeout = va_arg(param, long) * 1000L;
    break;

  case CURLOPT_TIMEOUT_MS:
    data->set.timeout = va_arg(param, long);
    break;

  case CURLOPT_CONNECTTIMEOUT:
    /*
     * The maximum time you allow curl to use to connect.
     */
    data->set.connecttimeout = va_arg(param, long) * 1000L;
    break;

  case CURLOPT_CONNECTTIMEOUT_MS:
    data->set.connecttimeout = va_arg(param, long);
    break;

  case CURLOPT_ACCEPTTIMEOUT_MS:
    /*
     * The maximum time you allow curl to wait for server connect
     */
    data->set.accepttimeout = va_arg(param, long);
    break;

  case CURLOPT_USERPWD:
    /*
     * user:password to use in the operation
     */
    result = setstropt_userpwd(va_arg(param, char *),
                               &data->set.str[STRING_USERNAME],
                               &data->set.str[STRING_PASSWORD]);
    break;

  case CURLOPT_USERNAME:
    /*
     * authentication user name to use in the operation
     */
    result = setstropt(&data->set.str[STRING_USERNAME],
                       va_arg(param, char *));
    break;

  case CURLOPT_PASSWORD:
    /*
     * authentication password to use in the operation
     */
    result = setstropt(&data->set.str[STRING_PASSWORD],
                       va_arg(param, char *));
    break;

  case CURLOPT_LOGIN_OPTIONS:
    /*
     * authentication options to use in the operation
     */
    result = setstropt(&data->set.str[STRING_OPTIONS],
                       va_arg(param, char *));
    break;

  case CURLOPT_XOAUTH2_BEARER:
    /*
     * XOAUTH2 bearer token to use in the operation
     */
    result = setstropt(&data->set.str[STRING_BEARER],
                       va_arg(param, char *));
    break;

  case CURLOPT_POSTQUOTE:
    /*
     * List of RAW FTP commands to use after a transfer
     */
    data->set.postquote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_PREQUOTE:
    /*
     * List of RAW FTP commands to use prior to RETR (Wesley Laxton)
     */
    data->set.prequote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_QUOTE:
    /*
     * List of RAW FTP commands to use before a transfer
     */
    data->set.quote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_RESOLVE:
    /*
     * List of NAME:[address] names to populate the DNS cache with
     * Prefix the NAME with dash (-) to _remove_ the name from the cache.
     *
     * Names added with this API will remain in the cache until explicitly
     * removed or the handle is cleaned up.
     *
     * This API can remove any name from the DNS cache, but only entries
     * that aren't actually in use right now will be pruned immediately.
     */
    data->set.resolve = va_arg(param, struct curl_slist *);
    data->change.resolve = data->set.resolve;
    break;
  case CURLOPT_PROGRESSFUNCTION:
    /*
     * Progress callback function
     */
    data->set.fprogress = va_arg(param, curl_progress_callback);
    if(data->set.fprogress)
      data->progress.callback = TRUE; /* no longer internal */
    else
      data->progress.callback = FALSE; /* NULL enforces internal */
    break;

  case CURLOPT_XFERINFOFUNCTION:
    /*
     * Transfer info callback function
     */
    data->set.fxferinfo = va_arg(param, curl_xferinfo_callback);
    if(data->set.fxferinfo)
      data->progress.callback = TRUE; /* no longer internal */
    else
      data->progress.callback = FALSE; /* NULL enforces internal */

    break;

  case CURLOPT_PROGRESSDATA:
    /*
     * Custom client data to pass to the progress callback
     */
    data->set.progress_client = va_arg(param, void *);
    break;

#ifndef CURL_DISABLE_PROXY
  case CURLOPT_PROXYUSERPWD:
    /*
     * user:password needed to use the proxy
     */
    result = setstropt_userpwd(va_arg(param, char *),
                               &data->set.str[STRING_PROXYUSERNAME],
                               &data->set.str[STRING_PROXYPASSWORD]);
    break;
  case CURLOPT_PROXYUSERNAME:
    /*
     * authentication user name to use in the operation
     */
    result = setstropt(&data->set.str[STRING_PROXYUSERNAME],
                       va_arg(param, char *));
    break;
  case CURLOPT_PROXYPASSWORD:
    /*
     * authentication password to use in the operation
     */
    result = setstropt(&data->set.str[STRING_PROXYPASSWORD],
                       va_arg(param, char *));
    break;
  case CURLOPT_NOPROXY:
    /*
     * proxy exception list
     */
    result = setstropt(&data->set.str[STRING_NOPROXY],
                       va_arg(param, char *));
    break;
#endif

  case CURLOPT_RANGE:
    /*
     * What range of the file you want to transfer
     */
    result = setstropt(&data->set.str[STRING_SET_RANGE],
                       va_arg(param, char *));
    break;
  case CURLOPT_RESUME_FROM:
    /*
     * Resume transfer at the give file position
     */
    data->set.set_resume_from = va_arg(param, long);
    break;
  case CURLOPT_RESUME_FROM_LARGE:
    /*
     * Resume transfer at the give file position
     */
    data->set.set_resume_from = va_arg(param, curl_off_t);
    break;
  case CURLOPT_DEBUGFUNCTION:
    /*
     * stderr write callback.
     */
    data->set.fdebug = va_arg(param, curl_debug_callback);
    /*
     * if the callback provided is NULL, it'll use the default callback
     */
    break;
  case CURLOPT_DEBUGDATA:
    /*
     * Set to a void * that should receive all error writes. This
     * defaults to CURLOPT_STDERR for normal operations.
     */
    data->set.debugdata = va_arg(param, void *);
    break;
  case CURLOPT_STDERR:
    /*
     * Set to a FILE * that should receive all error writes. This
     * defaults to stderr for normal operations.
     */
    data->set.err = va_arg(param, FILE *);
    if(!data->set.err)
      data->set.err = stderr;
    break;
  case CURLOPT_HEADERFUNCTION:
    /*
     * Set header write callback
     */
    data->set.fwrite_header = va_arg(param, curl_write_callback);
    break;
  case CURLOPT_WRITEFUNCTION:
    /*
     * Set data write callback
     */
    data->set.fwrite_func = va_arg(param, curl_write_callback);
    if(!data->set.fwrite_func) {
      data->set.is_fwrite_set = 0;
      /* When set to NULL, reset to our internal default function */
      data->set.fwrite_func = (curl_write_callback)fwrite;
    }
    else
      data->set.is_fwrite_set = 1;
    break;
  case CURLOPT_READFUNCTION:
    /*
     * Read data callback
     */
    data->set.fread_func = va_arg(param, curl_read_callback);
    if(!data->set.fread_func) {
      data->set.is_fread_set = 0;
      /* When set to NULL, reset to our internal default function */
      data->set.fread_func = (curl_read_callback)fread;
    }
    else
      data->set.is_fread_set = 1;
    break;
  case CURLOPT_SEEKFUNCTION:
    /*
     * Seek callback. Might be NULL.
     */
    data->set.seek_func = va_arg(param, curl_seek_callback);
    break;
  case CURLOPT_SEEKDATA:
    /*
     * Seek control callback. Might be NULL.
     */
    data->set.seek_client = va_arg(param, void *);
    break;
  case CURLOPT_CONV_FROM_NETWORK_FUNCTION:
    /*
     * "Convert from network encoding" callback
     */
    data->set.convfromnetwork = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_CONV_TO_NETWORK_FUNCTION:
    /*
     * "Convert to network encoding" callback
     */
    data->set.convtonetwork = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_CONV_FROM_UTF8_FUNCTION:
    /*
     * "Convert from UTF-8 encoding" callback
     */
    data->set.convfromutf8 = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_IOCTLFUNCTION:
    /*
     * I/O control callback. Might be NULL.
     */
    data->set.ioctl_func = va_arg(param, curl_ioctl_callback);
    break;
  case CURLOPT_IOCTLDATA:
    /*
     * I/O control data pointer. Might be NULL.
     */
    data->set.ioctl_client = va_arg(param, void *);
    break;
  case CURLOPT_SSLCERT:
    /*
     * String that holds file name of the SSL certificate to use
     */
    result = setstropt(&data->set.str[STRING_CERT],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSLCERTTYPE:
    /*
     * String that holds file type of the SSL certificate to use
     */
    result = setstropt(&data->set.str[STRING_CERT_TYPE],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSLKEY:
    /*
     * String that holds file name of the SSL key to use
     */
    result = setstropt(&data->set.str[STRING_KEY],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSLKEYTYPE:
    /*
     * String that holds file type of the SSL key to use
     */
    result = setstropt(&data->set.str[STRING_KEY_TYPE],
                       va_arg(param, char *));
    break;
  case CURLOPT_KEYPASSWD:
    /*
     * String that holds the SSL or SSH private key password.
     */
    result = setstropt(&data->set.str[STRING_KEY_PASSWD],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSLENGINE:
    /*
     * String that holds the SSL crypto engine.
     */
    argptr = va_arg(param, char *);
    if(argptr && argptr[0])
      result = Curl_ssl_set_engine(data, argptr);
    break;

  case CURLOPT_SSLENGINE_DEFAULT:
    /*
     * flag to set engine as default.
     */
    result = Curl_ssl_set_engine_default(data);
    break;
  case CURLOPT_CRLF:
    /*
     * Kludgy option to enable CRLF conversions. Subject for removal.
     */
    data->set.crlf = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_INTERFACE:
    /*
     * Set what interface or address/hostname to bind the socket to when
     * performing an operation and thus what from-IP your connection will use.
     */
    result = setstropt(&data->set.str[STRING_DEVICE],
                       va_arg(param, char *));
    break;
  case CURLOPT_LOCALPORT:
    /*
     * Set what local port to bind the socket to when performing an operation.
     */
    data->set.localport = curlx_sltous(va_arg(param, long));
    break;
  case CURLOPT_LOCALPORTRANGE:
    /*
     * Set number of local ports to try, starting with CURLOPT_LOCALPORT.
     */
    data->set.localportrange = curlx_sltosi(va_arg(param, long));
    break;
  case CURLOPT_KRBLEVEL:
    /*
     * A string that defines the kerberos security level.
     */
    result = setstropt(&data->set.str[STRING_KRB_LEVEL],
                       va_arg(param, char *));
    data->set.krb = (NULL != data->set.str[STRING_KRB_LEVEL])?TRUE:FALSE;
    break;
  case CURLOPT_GSSAPI_DELEGATION:
    /*
     * GSS-API credential delegation
     */
    data->set.gssapi_delegation = va_arg(param, long);
    break;
  case CURLOPT_SSL_VERIFYPEER:
    /*
     * Enable peer SSL verifying.
     */
    data->set.ssl.verifypeer = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_SSL_VERIFYHOST:
    /*
     * Enable verification of the host name in the peer certificate
     */
    arg = va_arg(param, long);

    /* Obviously people are not reading documentation and too many thought
       this argument took a boolean when it wasn't and misused it. We thus ban
       1 as a sensible input and we warn about its use. Then we only have the
       2 action internally stored as TRUE. */

    if(1 == arg) {
      failf(data, "CURLOPT_SSL_VERIFYHOST no longer supports 1 as value!");
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }

    data->set.ssl.verifyhost = (0 != arg)?TRUE:FALSE;
    break;
  case CURLOPT_SSL_CTX_FUNCTION:
#ifdef have_curlssl_ssl_ctx
    /*
     * Set a SSL_CTX callback
     */
    data->set.ssl.fsslctx = va_arg(param, curl_ssl_ctx_callback);
#else
    result = CURLE_NOT_BUILT_IN;
#endif
    break;
  case CURLOPT_SSL_CTX_DATA:
#ifdef have_curlssl_ssl_ctx
    /*
     * Set a SSL_CTX callback parameter pointer
     */
    data->set.ssl.fsslctxp = va_arg(param, void *);
#else
    result = CURLE_NOT_BUILT_IN;
#endif
    break;
  case CURLOPT_CERTINFO:
#ifdef have_curlssl_certinfo
    data->set.ssl.certinfo = (0 != va_arg(param, long))?TRUE:FALSE;
#else
    result = CURLE_NOT_BUILT_IN;
#endif
    break;
  case CURLOPT_PINNEDPUBLICKEY:
    /*
     * Set pinned public key for SSL connection.
     * Specify file name of the public key in DER format.
     */
    result = setstropt(&data->set.str[STRING_SSL_PINNEDPUBLICKEY],
                       va_arg(param, char *));
    break;
  case CURLOPT_CAINFO:
    /*
     * Set CA info for SSL connection. Specify file name of the CA certificate
     */
    result = setstropt(&data->set.str[STRING_SSL_CAFILE],
                       va_arg(param, char *));
    break;
  case CURLOPT_CAPATH:
#ifdef have_curlssl_ca_path /* not supported by all backends */
    /*
     * Set CA path info for SSL connection. Specify directory name of the CA
     * certificates which have been prepared using openssl c_rehash utility.
     */
    /* This does not work on windows. */
    result = setstropt(&data->set.str[STRING_SSL_CAPATH],
                       va_arg(param, char *));
#else
    result = CURLE_NOT_BUILT_IN;
#endif
    break;
  case CURLOPT_CRLFILE:
    /*
     * Set CRL file info for SSL connection. Specify file name of the CRL
     * to check certificates revocation
     */
    result = setstropt(&data->set.str[STRING_SSL_CRLFILE],
                       va_arg(param, char *));
    break;
  case CURLOPT_ISSUERCERT:
    /*
     * Set Issuer certificate file
     * to check certificates issuer
     */
    result = setstropt(&data->set.str[STRING_SSL_ISSUERCERT],
                       va_arg(param, char *));
    break;
  case CURLOPT_TELNETOPTIONS:
    /*
     * Set a linked list of telnet options
     */
    data->set.telnet_options = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_BUFFERSIZE:
    /*
     * The application kindly asks for a differently sized receive buffer.
     * If it seems reasonable, we'll use it.
     */
    data->set.buffer_size = va_arg(param, long);

    if((data->set.buffer_size> (BUFSIZE -1 )) ||
       (data->set.buffer_size < 1))
      data->set.buffer_size = 0; /* huge internal default */

    break;

  case CURLOPT_NOSIGNAL:
    /*
     * The application asks not to set any signal() or alarm() handlers,
     * even when using a timeout.
     */
    data->set.no_signal = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_SHARE:
  {
    struct Curl_share *set;
    set = va_arg(param, struct Curl_share *);

    /* disconnect from old share, if any */
    if(data->share) {
      Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);

      if(data->dns.hostcachetype == HCACHE_SHARED) {
        data->dns.hostcache = NULL;
        data->dns.hostcachetype = HCACHE_NONE;
      }

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
      if(data->share->cookies == data->cookies)
        data->cookies = NULL;
#endif

      if(data->share->sslsession == data->state.session)
        data->state.session = NULL;

      data->share->dirty--;

      Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);
      data->share = NULL;
    }

    /* use new share if it set */
    data->share = set;
    if(data->share) {

      Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);

      data->share->dirty++;

      if(data->share->hostcache) {
        /* use shared host cache */
        data->dns.hostcache = data->share->hostcache;
        data->dns.hostcachetype = HCACHE_SHARED;
      }
#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
      if(data->share->cookies) {
        /* use shared cookie list, first free own one if any */
        if(data->cookies)
          Curl_cookie_cleanup(data->cookies);
        /* enable cookies since we now use a share that uses cookies! */
        data->cookies = data->share->cookies;
      }
#endif   /* CURL_DISABLE_HTTP */
      if(data->share->sslsession) {
        data->set.ssl.max_ssl_sessions = data->share->max_ssl_sessions;
        data->state.session = data->share->sslsession;
      }
      Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);

    }
    /* check for host cache not needed,
     * it will be done by curl_easy_perform */
  }
  break;

  case CURLOPT_PRIVATE:
    /*
     * Set private data pointer.
     */
    data->set.private_data = va_arg(param, void *);
    break;

  case CURLOPT_MAXFILESIZE:
    /*
     * Set the maximum size of a file to download.
     */
    data->set.max_filesize = va_arg(param, long);
    break;

#ifdef USE_SSL
  case CURLOPT_USE_SSL:
    /*
     * Make transfers attempt to use SSL/TLS.
     */
    data->set.use_ssl = (curl_usessl)va_arg(param, long);
    break;

  case CURLOPT_SSL_OPTIONS:
    arg = va_arg(param, long);
    data->set.ssl_enable_beast = arg&CURLSSLOPT_ALLOW_BEAST?TRUE:FALSE;
    break;

#endif
  case CURLOPT_FTPSSLAUTH:
    /*
     * Set a specific auth for FTP-SSL transfers.
     */
    data->set.ftpsslauth = (curl_ftpauth)va_arg(param, long);
    break;

  case CURLOPT_IPRESOLVE:
    data->set.ipver = va_arg(param, long);
    break;

  case CURLOPT_MAXFILESIZE_LARGE:
    /*
     * Set the maximum size of a file to download.
     */
    data->set.max_filesize = va_arg(param, curl_off_t);
    break;

  case CURLOPT_TCP_NODELAY:
    /*
     * Enable or disable TCP_NODELAY, which will disable/enable the Nagle
     * algorithm
     */
    data->set.tcp_nodelay = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_ACCOUNT:
    result = setstropt(&data->set.str[STRING_FTP_ACCOUNT],
                       va_arg(param, char *));
    break;

  case CURLOPT_IGNORE_CONTENT_LENGTH:
    data->set.ignorecl = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_CONNECT_ONLY:
    /*
     * No data transfer, set up connection and let application use the socket
     */
    data->set.connect_only = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_FTP_ALTERNATIVE_TO_USER:
    result = setstropt(&data->set.str[STRING_FTP_ALTERNATIVE_TO_USER],
                       va_arg(param, char *));
    break;

  case CURLOPT_SOCKOPTFUNCTION:
    /*
     * socket callback function: called after socket() but before connect()
     */
    data->set.fsockopt = va_arg(param, curl_sockopt_callback);
    break;

  case CURLOPT_SOCKOPTDATA:
    /*
     * socket callback data pointer. Might be NULL.
     */
    data->set.sockopt_client = va_arg(param, void *);
    break;

  case CURLOPT_OPENSOCKETFUNCTION:
    /*
     * open/create socket callback function: called instead of socket(),
     * before connect()
     */
    data->set.fopensocket = va_arg(param, curl_opensocket_callback);
    break;

  case CURLOPT_OPENSOCKETDATA:
    /*
     * socket callback data pointer. Might be NULL.
     */
    data->set.opensocket_client = va_arg(param, void *);
    break;

  case CURLOPT_CLOSESOCKETFUNCTION:
    /*
     * close socket callback function: called instead of close()
     * when shutting down a connection
     */
    data->set.fclosesocket = va_arg(param, curl_closesocket_callback);
    break;

  case CURLOPT_CLOSESOCKETDATA:
    /*
     * socket callback data pointer. Might be NULL.
     */
    data->set.closesocket_client = va_arg(param, void *);
    break;

  case CURLOPT_SSL_SESSIONID_CACHE:
    data->set.ssl.sessionid = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

#ifdef USE_LIBSSH2
    /* we only include SSH options if explicitly built to support SSH */
  case CURLOPT_SSH_AUTH_TYPES:
    data->set.ssh_auth_types = va_arg(param, long);
    break;

  case CURLOPT_SSH_PUBLIC_KEYFILE:
    /*
     * Use this file instead of the $HOME/.ssh/id_dsa.pub file
     */
    result = setstropt(&data->set.str[STRING_SSH_PUBLIC_KEY],
                       va_arg(param, char *));
    break;

  case CURLOPT_SSH_PRIVATE_KEYFILE:
    /*
     * Use this file instead of the $HOME/.ssh/id_dsa file
     */
    result = setstropt(&data->set.str[STRING_SSH_PRIVATE_KEY],
                       va_arg(param, char *));
    break;
  case CURLOPT_SSH_HOST_PUBLIC_KEY_MD5:
    /*
     * Option to allow for the MD5 of the host public key to be checked
     * for validation purposes.
     */
    result = setstropt(&data->set.str[STRING_SSH_HOST_PUBLIC_KEY_MD5],
                       va_arg(param, char *));
    break;
#ifdef HAVE_LIBSSH2_KNOWNHOST_API
  case CURLOPT_SSH_KNOWNHOSTS:
    /*
     * Store the file name to read known hosts from.
     */
    result = setstropt(&data->set.str[STRING_SSH_KNOWNHOSTS],
                       va_arg(param, char *));
    break;

  case CURLOPT_SSH_KEYFUNCTION:
    /* setting to NULL is fine since the ssh.c functions themselves will
       then rever to use the internal default */
    data->set.ssh_keyfunc = va_arg(param, curl_sshkeycallback);
    break;

  case CURLOPT_SSH_KEYDATA:
    /*
     * Custom client data to pass to the SSH keyfunc callback
     */
    data->set.ssh_keyfunc_userp = va_arg(param, void *);
    break;
#endif /* HAVE_LIBSSH2_KNOWNHOST_API */

#endif /* USE_LIBSSH2 */

  case CURLOPT_HTTP_TRANSFER_DECODING:
    /*
     * disable libcurl transfer encoding is used
     */
    data->set.http_te_skip = (0 == va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_HTTP_CONTENT_DECODING:
    /*
     * raw data passed to the application when content encoding is used
     */
    data->set.http_ce_skip = (0 == va_arg(param, long))?TRUE:FALSE;
    break;

  case CURLOPT_NEW_FILE_PERMS:
    /*
     * Uses these permissions instead of 0644
     */
    data->set.new_file_perms = va_arg(param, long);
    break;

  case CURLOPT_NEW_DIRECTORY_PERMS:
    /*
     * Uses these permissions instead of 0755
     */
    data->set.new_directory_perms = va_arg(param, long);
    break;

  case CURLOPT_ADDRESS_SCOPE:
    /*
     * We always get longs when passed plain numericals, but for this value we
     * know that an unsigned int will always hold the value so we blindly
     * typecast to this type
     */
    data->set.scope_id = curlx_sltoui(va_arg(param, long));
    break;

  case CURLOPT_PROTOCOLS:
    /* set the bitmask for the protocols that are allowed to be used for the
       transfer, which thus helps the app which takes URLs from users or other
       external inputs and want to restrict what protocol(s) to deal
       with. Defaults to CURLPROTO_ALL. */
    data->set.allowed_protocols = va_arg(param, long);
    break;

  case CURLOPT_REDIR_PROTOCOLS:
    /* set the bitmask for the protocols that libcurl is allowed to follow to,
       as a subset of the CURLOPT_PROTOCOLS ones. That means the protocol needs
       to be set in both bitmasks to be allowed to get redirected to. Defaults
       to all protocols except FILE and SCP. */
    data->set.redir_protocols = va_arg(param, long);
    break;

  case CURLOPT_MAIL_FROM:
    /* Set the SMTP mail originator */
    result = setstropt(&data->set.str[STRING_MAIL_FROM],
                       va_arg(param, char *));
    break;

  case CURLOPT_MAIL_AUTH:
    /* Set the SMTP auth originator */
    result = setstropt(&data->set.str[STRING_MAIL_AUTH],
                       va_arg(param, char *));
    break;

  case CURLOPT_MAIL_RCPT:
    /* Set the list of mail recipients */
    data->set.mail_rcpt = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_SASL_IR:
    /* Enable/disable SASL initial response */
    data->set.sasl_ir = (0 != va_arg(param, long)) ? TRUE : FALSE;
    break;

  case CURLOPT_RTSP_REQUEST:
    {
      /*
       * Set the RTSP request method (OPTIONS, SETUP, PLAY, etc...)
       * Would this be better if the RTSPREQ_* were just moved into here?
       */
      long curl_rtspreq = va_arg(param, long);
      Curl_RtspReq rtspreq = RTSPREQ_NONE;
      switch(curl_rtspreq) {
        case CURL_RTSPREQ_OPTIONS:
          rtspreq = RTSPREQ_OPTIONS;
          break;

        case CURL_RTSPREQ_DESCRIBE:
          rtspreq = RTSPREQ_DESCRIBE;
          break;

        case CURL_RTSPREQ_ANNOUNCE:
          rtspreq = RTSPREQ_ANNOUNCE;
          break;

        case CURL_RTSPREQ_SETUP:
          rtspreq = RTSPREQ_SETUP;
          break;

        case CURL_RTSPREQ_PLAY:
          rtspreq = RTSPREQ_PLAY;
          break;

        case CURL_RTSPREQ_PAUSE:
          rtspreq = RTSPREQ_PAUSE;
          break;

        case CURL_RTSPREQ_TEARDOWN:
          rtspreq = RTSPREQ_TEARDOWN;
          break;

        case CURL_RTSPREQ_GET_PARAMETER:
          rtspreq = RTSPREQ_GET_PARAMETER;
          break;

        case CURL_RTSPREQ_SET_PARAMETER:
          rtspreq = RTSPREQ_SET_PARAMETER;
          break;

        case CURL_RTSPREQ_RECORD:
          rtspreq = RTSPREQ_RECORD;
          break;

        case CURL_RTSPREQ_RECEIVE:
          rtspreq = RTSPREQ_RECEIVE;
          break;
        default:
          rtspreq = RTSPREQ_NONE;
      }

      data->set.rtspreq = rtspreq;
    break;
    }


  case CURLOPT_RTSP_SESSION_ID:
    /*
     * Set the RTSP Session ID manually. Useful if the application is
     * resuming a previously established RTSP session
     */
    result = setstropt(&data->set.str[STRING_RTSP_SESSION_ID],
                       va_arg(param, char *));
    break;

  case CURLOPT_RTSP_STREAM_URI:
    /*
     * Set the Stream URI for the RTSP request. Unless the request is
     * for generic server options, the application will need to set this.
     */
    result = setstropt(&data->set.str[STRING_RTSP_STREAM_URI],
                       va_arg(param, char *));
    break;

  case CURLOPT_RTSP_TRANSPORT:
    /*
     * The content of the Transport: header for the RTSP request
     */
    result = setstropt(&data->set.str[STRING_RTSP_TRANSPORT],
                       va_arg(param, char *));
    break;

  case CURLOPT_RTSP_CLIENT_CSEQ:
    /*
     * Set the CSEQ number to issue for the next RTSP request. Useful if the
     * application is resuming a previously broken connection. The CSEQ
     * will increment from this new number henceforth.
     */
    data->state.rtsp_next_client_CSeq = va_arg(param, long);
    break;

  case CURLOPT_RTSP_SERVER_CSEQ:
    /* Same as the above, but for server-initiated requests */
    data->state.rtsp_next_client_CSeq = va_arg(param, long);
    break;

  case CURLOPT_INTERLEAVEDATA:
    data->set.rtp_out = va_arg(param, void *);
    break;
  case CURLOPT_INTERLEAVEFUNCTION:
    /* Set the user defined RTP write function */
    data->set.fwrite_rtp = va_arg(param, curl_write_callback);
    break;

  case CURLOPT_WILDCARDMATCH:
    data->set.wildcardmatch = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_CHUNK_BGN_FUNCTION:
    data->set.chunk_bgn = va_arg(param, curl_chunk_bgn_callback);
    break;
  case CURLOPT_CHUNK_END_FUNCTION:
    data->set.chunk_end = va_arg(param, curl_chunk_end_callback);
    break;
  case CURLOPT_FNMATCH_FUNCTION:
    data->set.fnmatch = va_arg(param, curl_fnmatch_callback);
    break;
  case CURLOPT_CHUNK_DATA:
    data->wildcard.customptr = va_arg(param, void *);
    break;
  case CURLOPT_FNMATCH_DATA:
    data->set.fnmatch_data = va_arg(param, void *);
    break;
#ifdef USE_TLS_SRP
  case CURLOPT_TLSAUTH_USERNAME:
    result = setstropt(&data->set.str[STRING_TLSAUTH_USERNAME],
                       va_arg(param, char *));
    if(data->set.str[STRING_TLSAUTH_USERNAME] && !data->set.ssl.authtype)
      data->set.ssl.authtype = CURL_TLSAUTH_SRP; /* default to SRP */
    break;
  case CURLOPT_TLSAUTH_PASSWORD:
    result = setstropt(&data->set.str[STRING_TLSAUTH_PASSWORD],
                       va_arg(param, char *));
    if(data->set.str[STRING_TLSAUTH_USERNAME] && !data->set.ssl.authtype)
      data->set.ssl.authtype = CURL_TLSAUTH_SRP; /* default to SRP */
    break;
  case CURLOPT_TLSAUTH_TYPE:
    if(strnequal((char *)va_arg(param, char *), "SRP", strlen("SRP")))
      data->set.ssl.authtype = CURL_TLSAUTH_SRP;
    else
      data->set.ssl.authtype = CURL_TLSAUTH_NONE;
    break;
#endif
  case CURLOPT_DNS_SERVERS:
    result = Curl_set_dns_servers(data, va_arg(param, char *));
    break;
  case CURLOPT_DNS_INTERFACE:
    result = Curl_set_dns_interface(data, va_arg(param, char *));
    break;
  case CURLOPT_DNS_LOCAL_IP4:
    result = Curl_set_dns_local_ip4(data, va_arg(param, char *));
    break;
  case CURLOPT_DNS_LOCAL_IP6:
    result = Curl_set_dns_local_ip6(data, va_arg(param, char *));
    break;

  case CURLOPT_TCP_KEEPALIVE:
    data->set.tcp_keepalive = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_TCP_KEEPIDLE:
    data->set.tcp_keepidle = va_arg(param, long);
    break;
  case CURLOPT_TCP_KEEPINTVL:
    data->set.tcp_keepintvl = va_arg(param, long);
    break;
  case CURLOPT_SSL_ENABLE_NPN:
    data->set.ssl_enable_npn = (0 != va_arg(param, long))?TRUE:FALSE;
    break;
  case CURLOPT_SSL_ENABLE_ALPN:
    data->set.ssl_enable_alpn = (0 != va_arg(param, long))?TRUE:FALSE;
    break;

#ifdef USE_UNIX_SOCKETS
  case CURLOPT_UNIX_SOCKET_PATH:
    result = setstropt(&data->set.str[STRING_UNIX_SOCKET_PATH],
                       va_arg(param, char *));
    break;
#endif

  default:
    /* unknown tag and its companion, just ignore: */
    result = CURLE_UNKNOWN_OPTION;
    break;
  }
