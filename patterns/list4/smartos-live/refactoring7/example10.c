return date_toLocaleHelper(cx, obj, argc, argv, rval,
#if defined(_WIN32) && !defined(__MWERKS__)
                                   "%#x"
#else
                                   "%x"
#endif
                                   );
