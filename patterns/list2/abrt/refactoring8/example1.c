struct options program_options[] = {
        OPT__VERBOSE(&g_verbose),
#if AUTHENTICATED_AUTOREPORTING != 0
        OPT_BOOL  (  'a', "anonymous",   &anonymous,               _("Turns the authentication off")),
        OPT_STRING(  'u', "username",    &username,    "USERNAME", _("Red Hat Support user name")),
        OPT_STRING(  'p', "password",    &password,    "PASSWORD", _("Red Hat Support password, if not given, a prompt for it will be issued")),
        OPT_STRING(  'c', "certificate", &certificate, "SOURCE",   _("uReport SSL certificate paths or certificate type")),
#endif
        OPT_END()
    };
