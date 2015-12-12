struct t_url_constant url_netrc[] =
{
#if LIBCURL_VERSION_NUM >= 0x070908 /* 7.9.8 */
    URL_DEF_CONST(_NETRC, IGNORED),
    URL_DEF_CONST(_NETRC, OPTIONAL),
    URL_DEF_CONST(_NETRC, REQUIRED),
#endif
    { NULL, 0 },
};
