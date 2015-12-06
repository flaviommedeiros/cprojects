switch (ctxt->context->node->type) {
            case XML_ELEMENT_NODE:
            case XML_TEXT_NODE:
            case XML_CDATA_SECTION_NODE:
            case XML_ENTITY_REF_NODE:
            case XML_ENTITY_NODE:
            case XML_PI_NODE:
            case XML_COMMENT_NODE:
	    case XML_DTD_NODE:
	    case XML_ELEMENT_DECL:
	    case XML_ATTRIBUTE_DECL:
	    case XML_ENTITY_DECL:
            case XML_NOTATION_NODE:
	    case XML_XINCLUDE_START:
	    case XML_XINCLUDE_END:
		if (ctxt->context->node->parent == NULL)
		    return((xmlNodePtr) ctxt->context->doc);
		if ((ctxt->context->node->parent->type == XML_ELEMENT_NODE) &&
		    ((ctxt->context->node->parent->name[0] == ' ') ||
		     (xmlStrEqual(ctxt->context->node->parent->name,
				 BAD_CAST "fake node libxslt"))))
		    return(NULL);
		return(ctxt->context->node->parent);
            case XML_ATTRIBUTE_NODE: {
		xmlAttrPtr tmp = (xmlAttrPtr) ctxt->context->node;

		return(tmp->parent);
	    }
            case XML_DOCUMENT_NODE:
            case XML_DOCUMENT_TYPE_NODE:
            case XML_DOCUMENT_FRAG_NODE:
            case XML_HTML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
	    case XML_DOCB_DOCUMENT_NODE:
#endif
                return(NULL);
	    case XML_NAMESPACE_DECL: {
		xmlNsPtr ns = (xmlNsPtr) ctxt->context->node;

		if ((ns->next != NULL) &&
		    (ns->next->type != XML_NAMESPACE_DECL))
		    return((xmlNodePtr) ns->next);
		/* Bad, how did that namespace end up here ? */
                return(NULL);
	    }
	}
