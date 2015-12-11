const GOptionEntry
    options[] = {
        { "uri",               'u', 0, G_OPTION_ARG_STRING,       &uri,
            "Uri to load at startup (equivalent to 'uzbl <uri>' after uzbl has launched)", "URI" },
        { "verbose",           'v', 0, G_OPTION_ARG_NONE,         &verbose,
            "Whether to print all messages or just errors.",                                                 NULL },
        { "named",             'n', 0, G_OPTION_ARG_STRING,       &uzbl.state.instance_name,
            "Name of the current instance (defaults to Xorg window id or random for GtkSocket mode)",        "NAME" },
        { "config",            'c', 0, G_OPTION_ARG_STRING,       &config_file,
            "Path to config file or '-' for stdin",                                                          "FILE" },
        /* TODO: explain the difference between these two options */
        { "xembed-socket",     's', 0, G_OPTION_ARG_INT,          &uzbl.state.xembed_socket_id,
            "Xembed socket ID, this window should embed itself",                                             "SOCKET" },
        { "connect-socket",     0,  0, G_OPTION_ARG_STRING_ARRAY, &connect_socket_names,
            "Connect to server socket for event managing",                                                   "CSOCKET" },
        { "print-events",      'p', 0, G_OPTION_ARG_NONE,         &print_events,
            "Whether to print events to stdout.",                                                            NULL },
        { "geometry",          'g', 0, G_OPTION_ARG_STRING,       &geometry,
            "Set window geometry (format: 'WIDTHxHEIGHT+-X+-Y' or 'maximized')",                             "GEOMETRY" },
        { "version",           'V', 0, G_OPTION_ARG_NONE,         &print_version,
            "Print the version and exit",                                                                    NULL },
        { "bug-info",          'B', 0, G_OPTION_ARG_NONE,         &bug_info,
            "Print information for a bug report and exit",                                                   NULL },
#ifdef USE_WEBKIT2
        { "web-extensions-dir", 0,  0, G_OPTION_ARG_STRING,       &uzbl.state.web_extensions_directory,
            "Directory that will be searched for webkit extensions",                                         "DIR" },
#endif
        { NULL,      0, 0, 0, NULL, NULL, NULL }
    };
