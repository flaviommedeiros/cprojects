if (conf->rules == NULL
#if (NGX_HAVE_INET6)
        && conf->rules6 == NULL
#endif
#if (NGX_HAVE_UNIX_DOMAIN)
        && conf->rules_un == NULL
#endif
    ) {
        conf->rules = prev->rules;
#if (NGX_HAVE_INET6)
        conf->rules6 = prev->rules6;
#endif
#if (NGX_HAVE_UNIX_DOMAIN)
        conf->rules_un = prev->rules_un;
#endif
    }
