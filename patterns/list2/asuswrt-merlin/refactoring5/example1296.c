#ifdef LIBXML_HTML_ENABLED
if (doc->type == XML_HTML_DOCUMENT_NODE)
        __htmlParseContent(ctxt);
    else
#endif
	xmlParseContent(ctxt);
