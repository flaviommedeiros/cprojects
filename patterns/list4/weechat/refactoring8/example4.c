struct t_url_constant url_postredir[] =
{
#if LIBCURL_VERSION_NUM >= 0x071301 /* 7.19.1 */
    URL_DEF_CONST(_REDIR, POST_301),
    URL_DEF_CONST(_REDIR, POST_302),
#endif
    { NULL, 0 },
};
