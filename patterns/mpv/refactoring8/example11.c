static const struct sd_functions *const sd_list[] = {
#if HAVE_LIBASS
    &sd_ass,
#endif
    &sd_lavc,
    &sd_movtext,
    &sd_srt,
    &sd_lavf_srt,
    &sd_microdvd,
    &sd_lavc_conv,
    NULL
};
