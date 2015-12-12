static const AVOption options[] = {
    {"dpi", "set the image resolution (in dpi)", OFFSET(dpi), AV_OPT_TYPE_INT, {.i64 = 72}, 1, 0x10000, AV_OPT_FLAG_VIDEO_PARAM|AV_OPT_FLAG_ENCODING_PARAM},
    { "compression_algo", NULL, OFFSET(compr), AV_OPT_TYPE_INT,   { .i64 = TIFF_PACKBITS }, TIFF_RAW, TIFF_DEFLATE, VE, "compression_algo" },
    { "packbits",         NULL, 0,             AV_OPT_TYPE_CONST, { .i64 = TIFF_PACKBITS }, 0,        0,            VE, "compression_algo" },
    { "raw",              NULL, 0,             AV_OPT_TYPE_CONST, { .i64 = TIFF_RAW      }, 0,        0,            VE, "compression_algo" },
    { "lzw",              NULL, 0,             AV_OPT_TYPE_CONST, { .i64 = TIFF_LZW      }, 0,        0,            VE, "compression_algo" },
#if CONFIG_ZLIB
    { "deflate",          NULL, 0,             AV_OPT_TYPE_CONST, { .i64 = TIFF_DEFLATE  }, 0,        0,            VE, "compression_algo" },
#endif
    { NULL },
};
