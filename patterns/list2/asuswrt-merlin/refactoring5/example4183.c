#ifdef LIBXML_HTML_ENABLED
if (options & XML_PARSE_HTML)
		htmlParseChunk(ctxt, base + cur, 1024, 0);
	    else
#endif
	    xmlParseChunk(ctxt, base + cur, 1024, 0);
