if ((s1 == OPENVPN_PLUGIN_FUNC_SUCCESS
#ifdef PLUGIN_DEF_AUTH
       || s1 == OPENVPN_PLUGIN_FUNC_DEFERRED
#endif
       ) && s2
#ifdef MANAGEMENT_DEF_AUTH
       && man_def_auth != KMDA_ERROR
#endif
      && tls_lock_username (multi, up->username))
    {
      ks->authenticated = true;
#ifdef PLUGIN_DEF_AUTH
      if (s1 == OPENVPN_PLUGIN_FUNC_DEFERRED)
	ks->auth_deferred = true;
#endif
#ifdef MANAGEMENT_DEF_AUTH
      if (man_def_auth != KMDA_UNDEF)
	ks->auth_deferred = true;
#endif
      if ((session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME))
	set_common_name (session, up->username);
#ifdef ENABLE_DEF_AUTH
      msg (D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s",
	   ks->auth_deferred ? "deferred" : "succeeded",
	   up->username,
	   (session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
#else
      msg (D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s",
	   "succeeded",
	   up->username,
	   (session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
#endif
    }
  else
    {
      msg (D_TLS_ERRORS, "TLS Auth Error: Auth Username/Password verification failed for peer");
    }
