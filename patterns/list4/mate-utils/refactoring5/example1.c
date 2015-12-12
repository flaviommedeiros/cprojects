#ifdef ENABLE_IPV6
if (_gdict_has_ipv6 ())
    {
      struct addrinfo hints, *res;

      GDICT_NOTE (DICT, "Hostname '%s' look-up (using IPv6)", priv->hostname);

      memset (&hints, 0, sizeof (hints));
      hints.ai_socktype = SOCK_STREAM;

      if (getaddrinfo (priv->hostname, NULL, &hints, &(priv->host6info)) == 0)
        {
          for (res = priv->host6info; res; res = res->ai_next)
            if (res->ai_family == AF_INET6 || res->ai_family == AF_INET)
              break;

          if (!res)
            {
              g_set_error (error, GDICT_CLIENT_CONTEXT_ERROR,
                           GDICT_CLIENT_CONTEXT_ERROR_LOOKUP,
                           _("Lookup failed for hostname '%s': no suitable resources found"),
                           priv->hostname);

              return FALSE;
            }
          else
	    {
	      if (res->ai_family == AF_INET6)
	        memcpy (&((struct sockaddr_in6 *) &priv->sockaddr)->sin6_addr,
	                &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr,
	                sizeof (struct in6_addr));

	      if (res->ai_family == AF_INET)
		memcpy (&((struct sockaddr_in *) &priv->sockaddr)->sin_addr,
		        &((struct sockaddr_in *) res->ai_addr)->sin_addr,
		        sizeof (struct in_addr));

	      priv->sockaddr.ss_family = res->ai_family;

	      GDICT_NOTE (DICT, "Hostname '%s' found (using IPv6)",
                          priv->hostname);

	      priv->last_lookup = time (NULL);

	      return TRUE;
	    }
        }
      else
        {
          g_set_error (error, GDICT_CLIENT_CONTEXT_ERROR,
                       GDICT_CLIENT_CONTEXT_ERROR_LOOKUP,
                       _("Lookup failed for host '%s': %s"),
                       priv->hostname,
                       gai_strerror (errno));

          return FALSE;
        }
    }
  else
    {
#endif /* ENABLE_IPV6 */
      /* if we don't support IPv6, fallback to usual IPv4 lookup */

      GDICT_NOTE (DICT, "Hostname '%s' look-up (using IPv4)", priv->hostname);

      ((struct sockaddr_in *) &priv->sockaddr)->sin_family = AF_INET;

      priv->hostinfo = gethostbyname (priv->hostname);
      if (priv->hostinfo)
        {
          memcpy (&((struct sockaddr_in *) &(priv->sockaddr))->sin_addr,
                  priv->hostinfo->h_addr,
                  priv->hostinfo->h_length);

          GDICT_NOTE (DICT, "Hostname '%s' found (using IPv4)",
		      priv->hostname);

	  priv->last_lookup = time (NULL);

          return TRUE;
        }
      else
        {
          g_set_error (error, GDICT_CLIENT_CONTEXT_ERROR,
                       GDICT_CLIENT_CONTEXT_ERROR_LOOKUP,
                       _("Lookup failed for host '%s': host not found"),
                       priv->hostname);

          return FALSE;
        }
#ifdef ENABLE_IPV6
    }
