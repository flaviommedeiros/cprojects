return search_from_environment(list,
                                               NULL,
                                               ".local/bin",
                                               "PATH",
                                               true,
                                               "/usr/local/sbin",
                                               "/usr/local/bin",
                                               "/usr/sbin",
                                               "/usr/bin",
#ifdef HAVE_SPLIT_USR
                                               "/sbin",
                                               "/bin",
#endif
                                               NULL);
