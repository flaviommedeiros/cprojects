if (err == 0
        || err == NGX_ECONNRESET
#if (NGX_WIN32)
        || err == NGX_ECONNABORTED
#else
        || err == NGX_EPIPE
#endif
        || err == NGX_ENOTCONN
        || err == NGX_ETIMEDOUT
        || err == NGX_ECONNREFUSED
        || err == NGX_ENETDOWN
        || err == NGX_ENETUNREACH
        || err == NGX_EHOSTDOWN
        || err == NGX_EHOSTUNREACH)
    {
        switch (c->log_error) {

        case NGX_ERROR_IGNORE_EINVAL:
        case NGX_ERROR_IGNORE_ECONNRESET:
        case NGX_ERROR_INFO:
            level = NGX_LOG_INFO;
            break;

        default:
            level = NGX_LOG_ERR;
        }

    } else {
        level = NGX_LOG_ALERT;
    }
