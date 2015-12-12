struct t_url_constant url_header[] =
{
#if LIBCURL_VERSION_NUM >= 0x072500 /* 7.37.0 */
    URL_DEF_CONST(HEADER, UNIFIED),
    URL_DEF_CONST(HEADER, SEPARATE),
#endif
    { NULL, 0 },
};
