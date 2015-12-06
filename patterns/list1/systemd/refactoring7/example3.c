return search_from_environment(list,
                                               NULL,
                                               ".local/lib",
                                               NULL,
                                               false,
                                               "/usr/local/lib",
                                               "/usr/lib",
#ifdef HAVE_SPLIT_USR
                                               "/lib",
#endif
                                               NULL);
