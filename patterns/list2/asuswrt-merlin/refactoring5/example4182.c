#ifdef LIBXML_HTML_ENABLED
if (options & XML_PARSE_HTML)
		htmlParseChunk(ctxt, base + cur, size - cur, 1);
	    else
#endif
	    xmlParseChunk(ctxt, base + cur, size - cur, 1);
