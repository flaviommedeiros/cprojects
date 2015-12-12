struct t_url_constant url_authtype[] =
{
#if LIBCURL_VERSION_NUM >= 0x071504 /* 7.21.4 */
    URL_DEF_CONST(_TLSAUTH, NONE),
    URL_DEF_CONST(_TLSAUTH, SRP),
#endif
    { NULL, 0 },
};
