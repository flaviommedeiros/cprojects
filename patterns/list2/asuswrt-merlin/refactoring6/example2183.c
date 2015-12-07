if (persistent_available_p (relevant->host, relevant->port,
#ifdef HAVE_SSL
                                  relevant->scheme == SCHEME_HTTPS,
#else
                                  0,
#endif
                                  &host_lookup_failed))
        {
          int family = socket_family (pconn.socket, ENDPOINT_PEER);
          sock = pconn.socket;
          using_ssl = pconn.ssl;
#if ENABLE_IPV6
          if (family == AF_INET6)
             logprintf (LOG_VERBOSE, _("Reusing existing connection to [%s]:%d.\n"),
                        quotearg_style (escape_quoting_style, pconn.host),
                         pconn.port);
          else
#endif
             logprintf (LOG_VERBOSE, _("Reusing existing connection to %s:%d.\n"),
                        quotearg_style (escape_quoting_style, pconn.host),
                        pconn.port);
          DEBUGP (("Reusing fd %d.\n", sock));
          if (pconn.authorized)
            /* If the connection is already authorized, the "Basic"
               authorization added by code above is unnecessary and
               only hurts us.  */
            request_remove_header (req, "Authorization");
        }
      else if (host_lookup_failed)
        {
          request_free (req);
          logprintf(LOG_NOTQUIET,
                    _("%s: unable to resolve host address %s\n"),
                    exec_name, quote (relevant->host));
          return HOSTERR;
        }
      else if (sock != -1)
        {
          sock = -1;
        }
