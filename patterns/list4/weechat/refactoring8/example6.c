struct t_url_constant url_ftp_auth[] =
{
#if LIBCURL_VERSION_NUM >= 0x070C02 /* 7.12.2 */
    URL_DEF_CONST(FTPAUTH, DEFAULT),
    URL_DEF_CONST(FTPAUTH, SSL),
    URL_DEF_CONST(FTPAUTH, TLS),
#endif
    { NULL, 0 },
};
