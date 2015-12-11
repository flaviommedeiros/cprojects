if (prev->headers_hash.buckets
#if (NGX_HTTP_CACHE)
            && ((conf->upstream.cache == NULL)
                == (prev->upstream.cache == NULL))
#endif
           )
        {
            conf->flushes = prev->flushes;
            conf->params_len = prev->params_len;
            conf->params = prev->params;
            conf->headers_hash = prev->headers_hash;
            conf->header_params = prev->header_params;

            return NGX_OK;
        }
