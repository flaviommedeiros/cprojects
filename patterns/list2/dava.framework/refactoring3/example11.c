switch (ctxt->context->node->type) {
            case XML_ELEMENT_NODE:
            case XML_TEXT_NODE:
            case XML_CDATA_SECTION_NODE:
            case XML_ENTITY_REF_NODE:
            case XML_ENTITY_NODE:
            case XML_PI_NODE:
            case XML_COMMENT_NODE:
            case XML_NOTATION_NODE:
            case XML_DTD_NODE:
		return(ctxt->context->node->children);
            case XML_DOCUMENT_NODE:
            case XML_DOCUMENT_TYPE_NODE:
            case XML_DOCUMENT_FRAG_NODE:
            case XML_HTML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
	    case XML_DOCB_DOCUMENT_NODE:
#endif
		return(((xmlDocPtr) ctxt->context->node)->children);
	    case XML_ELEMENT_DECL:
	    case XML_ATTRIBUTE_DECL:
	    case XML_ENTITY_DECL:
            case XML_ATTRIBUTE_NODE:
	    case XML_NAMESPACE_DECL:
	    case XML_XINCLUDE_START:
	    case XML_XINCLUDE_END:
		return(NULL);
	}
