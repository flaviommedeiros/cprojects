struct t_url_constant url_ip_resolve[] =
{
#if LIBCURL_VERSION_NUM >= 0x070A08 /* 7.10.8 */
    URL_DEF_CONST(_IPRESOLVE, WHATEVER),
    URL_DEF_CONST(_IPRESOLVE, V4),
    URL_DEF_CONST(_IPRESOLVE, V6),
#endif
    { NULL, 0 },
};
