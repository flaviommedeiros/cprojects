if (options->show_ciphers || options->show_digests || options->show_engines
#ifdef ENABLE_SSL
      || options->show_tls_ciphers
#endif
    )
    {
      if (options->show_ciphers)
	show_available_ciphers ();
      if (options->show_digests)
	show_available_digests ();
      if (options->show_engines)
	show_available_engines ();
#ifdef ENABLE_SSL
      if (options->show_tls_ciphers)
	show_available_tls_ciphers (options->cipher_list);
#endif
      return true;
    }
