static const BaseFilesystem table[] = {
        { "bin",      0, "usr/bin\0",                  NULL },
        { "lib",      0, "usr/lib\0",                  NULL },
        { "root",  0755, NULL,                         NULL, true },
        { "sbin",     0, "usr/sbin\0",                 NULL },
        { "usr",   0755, NULL,                         NULL },
        { "var",   0755, NULL,                         NULL },
        { "etc",   0755, NULL,                         NULL },
#if defined(__i386__) || defined(__x86_64__)
        { "lib64",    0, "usr/lib/x86_64-linux-gnu\0"
                         "usr/lib64\0",                "ld-linux-x86-64.so.2" },
#endif
};
