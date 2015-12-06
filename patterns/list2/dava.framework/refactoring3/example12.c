switch (cur->type) {
            case XML_ELEMENT_NODE:
	    case XML_DOCUMENT_FRAG_NODE:
	    case XML_ENTITY_REF_NODE: /* URGENT TODO: entify-refs as well? */
            case XML_ENTITY_NODE:
		cur = cur->children;
		if (cur != NULL) {
		    if (cur->type == XML_ELEMENT_NODE)
			return(cur);
		    do {
			cur = cur->next;
		    } while ((cur != NULL) &&
			(cur->type != XML_ELEMENT_NODE));
		    return(cur);
		}
		return(NULL);
            case XML_DOCUMENT_NODE:
            case XML_HTML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
	    case XML_DOCB_DOCUMENT_NODE:
#endif
		return(xmlDocGetRootElement((xmlDocPtr) cur));
	    default:
		return(NULL);
	}
