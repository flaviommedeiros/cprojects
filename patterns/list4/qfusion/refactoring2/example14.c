#if PA_CHECK_VERSION(0,9,16)
if(!pa_stream_begin_write ||
               pa_stream_begin_write(data->stream, &buf, &newlen) < 0)
#endif
            {
                buf = pa_xmalloc(newlen);
                free_func = pa_xfree;
            }
