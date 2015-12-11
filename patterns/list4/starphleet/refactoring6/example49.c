if ((err == NGX_ECONNRESET
#if (NGX_WIN32)
         || err == NGX_ECONNABORTED
#endif
        ) && c->log_error == NGX_ERROR_IGNORE_ECONNRESET)
    {
        return 0;
    }
