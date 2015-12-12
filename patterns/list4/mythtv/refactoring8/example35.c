static const AVOption setsar_options[] = {
    { "sar",   "set sample (pixel) aspect ratio", OFFSET(ratio_expr), AV_OPT_TYPE_STRING, { .str = "0" }, .flags = FLAGS },
    { "ratio", "set sample (pixel) aspect ratio", OFFSET(ratio_expr), AV_OPT_TYPE_STRING, { .str = "0" }, .flags = FLAGS },
    { "r",     "set sample (pixel) aspect ratio", OFFSET(ratio_expr), AV_OPT_TYPE_STRING, { .str = "0" }, .flags = FLAGS },
#if FF_API_OLD_FILTER_OPTS
    { "sar_den", NULL, OFFSET(aspect_den), AV_OPT_TYPE_FLOAT, { .dbl = 0 }, 0, FLT_MAX, FLAGS },
#endif
    { "max",   "set max value for nominator or denominator in the ratio", OFFSET(max), AV_OPT_TYPE_INT, {.i64=100}, 1, INT_MAX, FLAGS },
    { NULL }
};
