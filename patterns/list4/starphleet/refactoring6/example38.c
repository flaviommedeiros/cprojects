if (ctx->tree
#if (NGX_HAVE_INET6)
                || ctx->tree6
#endif
               )
            {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "the \"ranges\" directive must be "
                                   "the first directive inside \"geo\" block");
                goto failed;
            }
