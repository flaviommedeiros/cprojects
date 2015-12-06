switch (cur->type) {
            case XML_ELEMENT_NODE:
		if ((cur->ns != NULL) && (cur->ns->prefix != NULL)) {
		    if (size - len < xmlStrlen(cur->ns->prefix) + 10) {
			if ((size - len > 4) && (buf[len - 1] != '.'))
			    strcat(buf, " ...");
			return;
		    }
		    strcat(buf, (char *) cur->ns->prefix);
		    strcat(buf, ":");
		}
                if (size - len < xmlStrlen(cur->name) + 10) {
		    if ((size - len > 4) && (buf[len - 1] != '.'))
			strcat(buf, " ...");
		    return;
		}
	        strcat(buf, (char *) cur->name);
		if (cur->next != NULL)
		    strcat(buf, " ");
		break;
            case XML_TEXT_NODE:
		if (xmlIsBlankNode(cur))
		    break;
            case XML_CDATA_SECTION_NODE:
            case XML_ENTITY_REF_NODE:
	        strcat(buf, "CDATA");
		if (cur->next != NULL)
		    strcat(buf, " ");
		break;
            case XML_ATTRIBUTE_NODE:
            case XML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
	    case XML_DOCB_DOCUMENT_NODE:
#endif
	    case XML_HTML_DOCUMENT_NODE:
            case XML_DOCUMENT_TYPE_NODE:
            case XML_DOCUMENT_FRAG_NODE:
            case XML_NOTATION_NODE:
	    case XML_NAMESPACE_DECL:
	        strcat(buf, "???");
		if (cur->next != NULL)
		    strcat(buf, " ");
		break;
            case XML_ENTITY_NODE:
            case XML_PI_NODE:
            case XML_DTD_NODE:
            case XML_COMMENT_NODE:
	    case XML_ELEMENT_DECL:
	    case XML_ATTRIBUTE_DECL:
	    case XML_ENTITY_DECL:
	    case XML_XINCLUDE_START:
	    case XML_XINCLUDE_END:
		break;
	}
