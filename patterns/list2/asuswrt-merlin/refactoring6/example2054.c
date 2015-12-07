if ((cur->type == XML_DOCUMENT_NODE) ||
#ifdef LIBXML_DOCB_ENABLED
	(cur->type == XML_DOCB_DOCUMENT_NODE) ||
#endif
	(cur->type == XML_HTML_DOCUMENT_NODE)) {
	xmlFreeDoc((xmlDocPtr) cur);
	return;
    }
