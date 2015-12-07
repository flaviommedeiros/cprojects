#ifdef LIBXML_HTML_ENABLED
if (options & XML_PARSE_HTML) {
	htmlSAXParseFile(filename, NULL, emptySAXHandler, NULL);
	ret = 0;
    } else
#endif
    ret = xmlSAXUserParseFile(emptySAXHandler, NULL, filename);
