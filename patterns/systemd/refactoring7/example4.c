return search_from_environment(list,
                                               NULL,
                                               ".local/lib/" LIB_ARCH_TUPLE,
                                               "LD_LIBRARY_PATH",
                                               true,
                                               LIBDIR,
#ifdef HAVE_SPLIT_USR
                                               ROOTLIBDIR,
#endif
                                               NULL);
