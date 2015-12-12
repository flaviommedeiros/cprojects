struct t_url_constant url_time_condition[] =
{
#if LIBCURL_VERSION_NUM >= 0x070907 /* 7.9.7 */
    URL_DEF_CONST(_TIMECOND, NONE),
    URL_DEF_CONST(_TIMECOND, IFMODSINCE),
    URL_DEF_CONST(_TIMECOND, IFUNMODSINCE),
    URL_DEF_CONST(_TIMECOND, LASTMOD),
#endif
    { NULL, 0 },
};
