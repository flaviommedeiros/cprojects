#ifdef LIBXML_HTML_ENABLED
if (options & XML_PARSE_HTML)
	ctxt = htmlCreatePushParserCtxt(NULL, NULL, base + cur, 4, filename,
	                                XML_CHAR_ENCODING_NONE);
    else
#endif
    ctxt = xmlCreatePushParserCtxt(NULL, NULL, base + cur, 4, filename);
