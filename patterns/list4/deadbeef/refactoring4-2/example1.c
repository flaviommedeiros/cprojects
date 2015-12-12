#ifdef HAVE_OGG_STREAM_FLUSH_FILL
while (ogg_stream_flush_fill(os, &og, MAXPAYLOAD))
#else
    while (ogg_stream_flush(os, &og))
#endif
        if (!write_page(out, &og))
            return OGGEDIT_WRITE_ERROR;
