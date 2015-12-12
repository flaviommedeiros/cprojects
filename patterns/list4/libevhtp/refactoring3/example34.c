switch (cfg->scache_type) {
        case evhtp_ssl_scache_type_disabled:
            cache_mode = SSL_SESS_CACHE_OFF;
            break;
#ifdef EVHTP_ENABLE_FUTURE_STUFF
        case evhtp_ssl_scache_type_user:
            cache_mode = SSL_SESS_CACHE_SERVER |
                         SSL_SESS_CACHE_NO_INTERNAL |
                         SSL_SESS_CACHE_NO_INTERNAL_LOOKUP;

            init_cb    = cfg->scache_init;
            add_cb     = cfg->scache_add;
            get_cb     = cfg->scache_get;
            del_cb     = cfg->scache_del;
            break;
        case evhtp_ssl_scache_type_builtin:
            cache_mode = SSL_SESS_CACHE_SERVER |
                         SSL_SESS_CACHE_NO_INTERNAL |
                         SSL_SESS_CACHE_NO_INTERNAL_LOOKUP;

            init_cb    = _evhtp_ssl_builtin_init;
            add_cb     = _evhtp_ssl_builtin_add;
            get_cb     = _evhtp_ssl_builtin_get;
            del_cb     = _evhtp_ssl_builtin_del;
            break;
#endif
        case evhtp_ssl_scache_type_internal:
        default:
            cache_mode = SSL_SESS_CACHE_SERVER;
            break;
    }
