#ifdef HAVE_ZLIB_H
if ((compression > 0) && (compression <= 9)) {

        ctxt->compression = compression;
        ctxt->doc_buff = xmlCreateZMemBuff(compression);
    } else
#endif
    {
        /*  Any character conversions should have been done before this  */

        ctxt->doc_buff = xmlAllocOutputBufferInternal(NULL);
    }
