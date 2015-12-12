struct t_url_constant url_http_version[] =
{
#if LIBCURL_VERSION_NUM >= 0x070901 /* 7.9.1 */
    URL_DEF_CONST(_HTTP_VERSION, NONE),
    URL_DEF_CONST(_HTTP_VERSION, 1_0),
    URL_DEF_CONST(_HTTP_VERSION, 1_1),
#endif
    { NULL, 0 },
};
