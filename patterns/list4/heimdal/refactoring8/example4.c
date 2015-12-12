struct getargs args[] = {
    { "credential",	0,   arg_string, rk_UNCONST(&credential),
      "remove one credential", "principal" },
    { "cache",		'c', arg_string, rk_UNCONST(&cache), "cache to destroy", "cache" },
    { "all",		'A', arg_flag, &all_flag, "destroy all caches", NULL },
#ifndef NO_AFS
    { "unlog",		0,   arg_negative_flag, &unlog_flag,
      "do not destroy tokens", NULL },
#endif
    { "delete-v4",	0,   arg_negative_flag, &dest_tkt_flag,
      "do not destroy v4 tickets", NULL },
    { "version", 	0,   arg_flag, &version_flag, NULL, NULL },
    { "help",		'h', arg_flag, &help_flag, NULL, NULL}
};
