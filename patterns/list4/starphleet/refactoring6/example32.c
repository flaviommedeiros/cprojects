if (conf->params_source == NULL
#if (NGX_HTTP_CACHE)
        && (conf->upstream.cache == NULL)
#endif
       )
    {
        conf->headers_hash.buckets = (void *) 1;
        return NGX_OK;
    }
