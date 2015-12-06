#ifdef LIBXML_HTML_ENABLED
if (is_xhtml)
		xhtmlNodeDumpOutput(ctxt, child);
	    else
#endif
		xmlNodeDumpOutputInternal(ctxt, child);
