static ngx_conf_enum_t  ngx_http_core_aio[] = {
    { ngx_string("off"), NGX_HTTP_AIO_OFF  },
    { ngx_string("on"), NGX_HTTP_AIO_ON },
#if (NGX_HAVE_AIO_SENDFILE)
    { ngx_string("sendfile"), NGX_HTTP_AIO_SENDFILE },
#endif
    { ngx_null_string, 0 }
};
