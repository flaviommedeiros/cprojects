static const AVOption buffer_options[] = {
    { "width",         NULL,                     OFFSET(w),                AV_OPT_TYPE_INT,      { .i64 = 0 }, 0, INT_MAX, V },
    { "video_size",    NULL,                     OFFSET(w),                AV_OPT_TYPE_IMAGE_SIZE,                .flags = V },
    { "height",        NULL,                     OFFSET(h),                AV_OPT_TYPE_INT,      { .i64 = 0 }, 0, INT_MAX, V },
    { "pix_fmt",       NULL,                     OFFSET(pix_fmt),          AV_OPT_TYPE_PIXEL_FMT, { .i64 = AV_PIX_FMT_NONE }, .min = AV_PIX_FMT_NONE, .max = INT_MAX, .flags = V },
#if FF_API_OLD_FILTER_OPTS
    /* those 4 are for compatibility with the old option passing system where each filter
     * did its own parsing */
    { "time_base_num", "deprecated, do not use", OFFSET(time_base.num),    AV_OPT_TYPE_INT,      { .i64 = 0 }, 0, INT_MAX, V },
    { "time_base_den", "deprecated, do not use", OFFSET(time_base.den),    AV_OPT_TYPE_INT,      { .i64 = 0 }, 0, INT_MAX, V },
    { "sar_num",       "deprecated, do not use", OFFSET(pixel_aspect.num), AV_OPT_TYPE_INT,      { .i64 = 0 }, 0, INT_MAX, V },
    { "sar_den",       "deprecated, do not use", OFFSET(pixel_aspect.den), AV_OPT_TYPE_INT,      { .i64 = 0 }, 0, INT_MAX, V },
#endif
    { "sar",           "sample aspect ratio",    OFFSET(pixel_aspect),     AV_OPT_TYPE_RATIONAL, { .dbl = 1 }, 0, DBL_MAX, V },
    { "pixel_aspect",  "sample aspect ratio",    OFFSET(pixel_aspect),     AV_OPT_TYPE_RATIONAL, { .dbl = 1 }, 0, DBL_MAX, V },
    { "time_base",     NULL,                     OFFSET(time_base),        AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, 0, DBL_MAX, V },
    { "frame_rate",    NULL,                     OFFSET(frame_rate),       AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, 0, DBL_MAX, V },
    { "sws_param",     NULL,                     OFFSET(sws_param),        AV_OPT_TYPE_STRING,                    .flags = V },
    { NULL },
};
