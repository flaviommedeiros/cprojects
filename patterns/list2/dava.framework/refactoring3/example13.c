switch (contextNode->type) {
	    case XML_ELEMENT_NODE:
	    case XML_XINCLUDE_START:
	    case XML_DOCUMENT_FRAG_NODE:
	    case XML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
	    case XML_DOCB_DOCUMENT_NODE:
#endif
	    case XML_HTML_DOCUMENT_NODE:	    
		return(contextNode);
	    default:
		return(NULL);
	}
