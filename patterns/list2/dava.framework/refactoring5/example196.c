#ifdef HAVE_ZLIB_H
if (ctxt->compression > 0) 
	    len = xmlZMemBuffAppend(ctxt->doc_buff, buffer, len);

	else
#endif
	    len = xmlOutputBufferWrite(ctxt->doc_buff, len, buffer);
