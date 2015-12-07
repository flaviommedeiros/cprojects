if (proxy
#ifdef HAVE_SSL
        /* When using SSL over proxy, CONNECT establishes a direct
           connection to the HTTPS server.  Therefore use the same
           argument as when talking to the server directly. */
        && u->scheme != SCHEME_HTTPS
#endif
        )
      meth_arg = xstrdup (u->url);
    else
      meth_arg = url_full_path (u);
