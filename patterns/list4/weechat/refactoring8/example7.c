struct t_url_constant url_ftp_file_method[] =
{
#if LIBCURL_VERSION_NUM >= 0x070F03 /* 7.15.3 */
    URL_DEF_CONST(FTPMETHOD, MULTICWD),
    URL_DEF_CONST(FTPMETHOD, NOCWD),
    URL_DEF_CONST(FTPMETHOD, SINGLECWD),
#endif
    { NULL, 0 },
};
