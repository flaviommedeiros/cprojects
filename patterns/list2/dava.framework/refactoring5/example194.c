#ifdef HAVE_ZLIB_H
if (ctxt->compression > 0) {
	    xmlFreeZMemBuff(ctxt->doc_buff);
	}
	else
#endif
	{
	    xmlOutputBufferClose(ctxt->doc_buff);
	}
