#ifdef LIBXML_HTML_ENABLED
if (options & XML_PARSE_HTML) {
		htmlDocDumpMemory(doc, (xmlChar **) &base, &size);
	    } else
#endif
	    xmlDocDumpMemory(doc, (xmlChar **) &base, &size);
