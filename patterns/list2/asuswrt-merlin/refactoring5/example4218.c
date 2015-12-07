#ifdef HAVE_ZLIB_H
if ( ctxt->compression > 0 ) {
	content_lgth = xmlZMemBuffGetContent( ctxt->doc_buff, &http_content );
	content_encoding = (char *) "Content-Encoding: gzip";
    }
    else
#endif
    {
	/*  Pull the data out of the memory output buffer  */

	xmlOutputBufferPtr	dctxt = ctxt->doc_buff;
	http_content = (char *)dctxt->buffer->content;
	content_lgth = dctxt->buffer->use;
    }
