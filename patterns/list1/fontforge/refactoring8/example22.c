static char *default_ext_list[] = {
    "ttf",
    "otf",
    "ttc",
    "cid",
    "pfb",
    "pfa",
    "bdf",
#ifdef TEST_FREETYPE
#else
    "sfd",
    "svg",
    "pt3",
#endif
    NULL
};
