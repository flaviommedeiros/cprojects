switch(subletter) {
      case 'a': /* random-file */
        GetStr(&config->random_file, nextarg);
        break;
      case 'b': /* egd-file */
        GetStr(&config->egd_file, nextarg);
        break;
      case 'c': /* connect-timeout */
        err = str2udouble(&config->connecttimeout, nextarg);
        if(err)
          return err;
        break;
      case 'd': /* ciphers */
        GetStr(&config->cipher_list, nextarg);
        break;
      case 'e': /* --disable-epsv */
        config->disable_epsv = toggle;
        break;
      case 'E': /* --epsv */
        config->disable_epsv = (!toggle)?TRUE:FALSE;
        break;
#ifdef USE_ENVIRONMENT
      case 'f':
        config->writeenv = toggle;
        break;
#endif
      case 'g': /* --trace */
        GetStr(&config->trace_dump, nextarg);
        if(config->tracetype && (config->tracetype != TRACE_BIN))
          warnf(config, "--trace overrides an earlier trace/verbose option\n");
        config->tracetype = TRACE_BIN;
        break;
      case 'h': /* --trace-ascii */
        GetStr(&config->trace_dump, nextarg);
        if(config->tracetype && (config->tracetype != TRACE_ASCII))
          warnf(config,
                "--trace-ascii overrides an earlier trace/verbose option\n");
        config->tracetype = TRACE_ASCII;
        break;
      case 'i': /* --limit-rate */
      {
        /* We support G, M, K too */
        char *unit;
        curl_off_t value = curlx_strtoofft(nextarg, &unit, 0);

        if(!*unit)
          unit = (char *)"b";
        else if(strlen(unit) > 1)
          unit = (char *)"w"; /* unsupported */

        switch(*unit) {
        case 'G':
        case 'g':
          value *= 1024*1024*1024;
          break;
        case 'M':
        case 'm':
          value *= 1024*1024;
          break;
        case 'K':
        case 'k':
          value *= 1024;
          break;
        case 'b':
        case 'B':
          /* for plain bytes, leave as-is */
          break;
        default:
          warnf(config, "unsupported rate unit. Use G, M, K or B!\n");
          return PARAM_BAD_USE;
        }
        config->recvpersecond = value;
        config->sendpersecond = value;
      }
      break;

      case 'j': /* --compressed */
        if(toggle && !(curlinfo->features & CURL_VERSION_LIBZ))
          return PARAM_LIBCURL_DOESNT_SUPPORT;
        config->encoding = toggle;
        break;

      case 'J': /* --tr-encoding */
        config->tr_encoding = toggle;
        break;

      case 'k': /* --digest */
        if(toggle)
          config->authtype |= CURLAUTH_DIGEST;
        else
          config->authtype &= ~CURLAUTH_DIGEST;
        break;

      case 'l': /* --negotiate */
        if(toggle) {
          if(curlinfo->features & CURL_VERSION_GSSNEGOTIATE)
            config->authtype |= CURLAUTH_GSSNEGOTIATE;
          else
            return PARAM_LIBCURL_DOESNT_SUPPORT;
        }
        else
          config->authtype &= ~CURLAUTH_GSSNEGOTIATE;
        break;

      case 'm': /* --ntlm */
        if(toggle) {
          if(curlinfo->features & CURL_VERSION_NTLM)
            config->authtype |= CURLAUTH_NTLM;
          else
            return PARAM_LIBCURL_DOESNT_SUPPORT;
        }
        else
          config->authtype &= ~CURLAUTH_NTLM;
        break;

      case 'M': /* --ntlm-wb */
        if(toggle) {
          if(curlinfo->features & CURL_VERSION_NTLM_WB)
            config->authtype |= CURLAUTH_NTLM_WB;
          else
            return PARAM_LIBCURL_DOESNT_SUPPORT;
        }
        else
          config->authtype &= ~CURLAUTH_NTLM_WB;
        break;

      case 'n': /* --basic for completeness */
        if(toggle)
          config->authtype |= CURLAUTH_BASIC;
        else
          config->authtype &= ~CURLAUTH_BASIC;
        break;

      case 'o': /* --anyauth, let libcurl pick it */
        if(toggle)
          config->authtype = CURLAUTH_ANY;
        /* --no-anyauth simply doesn't touch it */
        break;

#ifdef USE_WATT32
      case 'p': /* --wdebug */
        dbug_init();
        break;
#endif
      case 'q': /* --ftp-create-dirs */
        config->ftp_create_dirs = toggle;
        break;

      case 'r': /* --create-dirs */
        config->create_dirs = TRUE;
        break;

      case 's': /* --max-redirs */
        /* specified max no of redirects (http(s)), this accepts -1 as a
           special condition */
        err = str2num(&config->maxredirs, nextarg);
        if(err)
          return err;
        if(config->maxredirs < -1)
          return PARAM_BAD_NUMERIC;
        break;

      case 't': /* --proxy-ntlm */
        if(curlinfo->features & CURL_VERSION_NTLM)
          config->proxyntlm = toggle;
        else
          return PARAM_LIBCURL_DOESNT_SUPPORT;
        break;

      case 'u': /* --crlf */
        /* LF -> CRLF conversion? */
        config->crlf = TRUE;
        break;

      case 'v': /* --stderr */
        if(strcmp(nextarg, "-")) {
          FILE *newfile = fopen(nextarg, "wt");
          if(!newfile)
            warnf(config, "Failed to open %s!\n", nextarg);
          else {
            if(config->errors_fopened)
              fclose(config->errors);
            config->errors = newfile;
            config->errors_fopened = TRUE;
          }
        }
        else
          config->errors = stdout;
        break;
      case 'w': /* --interface */
        /* interface */
        GetStr(&config->iface, nextarg);
        break;
      case 'x': /* --krb */
        /* kerberos level string */
        if(curlinfo->features & (CURL_VERSION_KERBEROS4 |
                                 CURL_VERSION_GSSNEGOTIATE))
          GetStr(&config->krblevel, nextarg);
        else
          return PARAM_LIBCURL_DOESNT_SUPPORT;
        break;
      case 'y': /* --max-filesize */
        err = str2offset(&config->max_filesize, nextarg);
        if(err)
          return err;
        break;
      case 'z': /* --disable-eprt */
        config->disable_eprt = toggle;
        break;
      case 'Z': /* --eprt */
        config->disable_eprt = (!toggle)?TRUE:FALSE;
        break;

      default: /* the URL! */
      {
        struct getout *url;
        if(config->url_get || ((config->url_get = config->url_list) != NULL)) {
          /* there's a node here, if it already is filled-in continue to find
             an "empty" node */
          while(config->url_get && (config->url_get->flags & GETOUT_URL))
            config->url_get = config->url_get->next;
        }

        /* now there might or might not be an available node to fill in! */

        if(config->url_get)
          /* existing node */
          url = config->url_get;
        else
          /* there was no free node, create one! */
          url = new_getout(config);

        if(!url)
          return PARAM_NO_MEM;
        else {
          /* fill in the URL */
          GetStr(&url->url, nextarg);
          url->flags |= GETOUT_URL;
        }
      }
      }
