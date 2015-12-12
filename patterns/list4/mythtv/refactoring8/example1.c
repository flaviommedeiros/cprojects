static const char * const jar_paths[] = {
#ifdef _WIN32
        "" BDJ_JARFILE,
#else
        "/usr/share/java/" BDJ_JARFILE,
        "/usr/share/libbluray/lib/" BDJ_JARFILE,
#endif
    };
