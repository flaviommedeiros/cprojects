struct t_url_constant url_ssl_version[] =
{
#if LIBCURL_VERSION_NUM >= 0x070902 /* 7.9.2 */
    URL_DEF_CONST(_SSLVERSION, DEFAULT),
    URL_DEF_CONST(_SSLVERSION, TLSv1),
    URL_DEF_CONST(_SSLVERSION, SSLv2),
    URL_DEF_CONST(_SSLVERSION, SSLv3),
#endif
    { NULL, 0 },
};
