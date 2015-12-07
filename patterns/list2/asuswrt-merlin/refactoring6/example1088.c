if (options->inetd == INETD_NOWAIT
#if defined(ENABLE_CRYPTO) && defined(ENABLE_SSL)
      && !(options->tls_server || options->tls_client)
#endif
      )
    msg (M_USAGE, "--inetd nowait can only be used in TLS mode");
