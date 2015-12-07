#ifdef LIBXML_HTML_ENABLED
if (options & XML_PARSE_HTML) {
	htmlSAXParseFile(filename, NULL, debugHTMLSAXHandler, NULL);
	ret = 0;
    } else
#endif
    if (options & XML_PARSE_SAX1) {
	ret = xmlSAXUserParseFile(debugSAXHandler, NULL, filename);
    } else {
	ret = xmlSAXUserParseFile(debugSAX2Handler, NULL, filename);
    }
