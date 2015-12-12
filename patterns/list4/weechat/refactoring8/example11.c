struct t_url_constant url_use_ssl[] =
{
#if LIBCURL_VERSION_NUM >= 0x071100 /* 7.17.0 */
    URL_DEF_CONST(USESSL, NONE),
    URL_DEF_CONST(USESSL, TRY),
    URL_DEF_CONST(USESSL, CONTROL),
    URL_DEF_CONST(USESSL, ALL),
#endif
    { NULL, 0 },
};
