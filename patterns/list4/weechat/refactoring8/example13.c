struct t_url_constant url_ssl_options[] =
{
#if LIBCURL_VERSION_NUM >= 0x071900 /* 7.25.0 */
    URL_DEF_CONST(SSLOPT, ALLOW_BEAST),
#endif
    { NULL, 0 },
};
