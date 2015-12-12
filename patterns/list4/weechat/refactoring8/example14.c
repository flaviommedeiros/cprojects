struct t_url_constant url_gssapi_delegation[] =
{
#if LIBCURL_VERSION_NUM >= 0x071600 /* 7.22.0 */
    URL_DEF_CONST(GSSAPI_DELEGATION, NONE),
    URL_DEF_CONST(GSSAPI_DELEGATION, POLICY_FLAG),
    URL_DEF_CONST(GSSAPI_DELEGATION, FLAG),
#endif
    { NULL, 0 },
};
