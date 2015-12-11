if (conf->headers_set_hash.buckets
#if (NGX_HTTP_CACHE)
        && ((conf->upstream.cache == NULL) == (prev->upstream.cache == NULL))
#endif
       )
    {
        return NGX_OK;
    }
