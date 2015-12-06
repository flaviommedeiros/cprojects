switch (cur->type) {
        case XML_DOCUMENT_FRAG_NODE:
        case XML_ELEMENT_NODE: {
	    xmlNodePtr last, newNode, tmp;

	    last = cur->last;
	    newNode = xmlNewTextLen(content, len);
	    if (newNode != NULL) {
		tmp = xmlAddChild(cur, newNode);
		if (tmp != newNode)
		    return;
	        if ((last != NULL) && (last->next == newNode)) {
		    xmlTextMerge(last, newNode);
		}
	    }
	    break;
	}
        case XML_ATTRIBUTE_NODE:
	    break;
        case XML_TEXT_NODE:
        case XML_CDATA_SECTION_NODE:
        case XML_ENTITY_REF_NODE:
        case XML_ENTITY_NODE:
        case XML_PI_NODE:
        case XML_COMMENT_NODE:
        case XML_NOTATION_NODE:
	    if (content != NULL) {
	        if ((cur->content == (xmlChar *) &(cur->properties)) ||
		    ((cur->doc != NULL) && (cur->doc->dict != NULL) &&
			    xmlDictOwns(cur->doc->dict, cur->content))) {
		    cur->content = xmlStrncatNew(cur->content, content, len);
		    cur->properties = NULL;
		    cur->nsDef = NULL;
		    break;
		}
		cur->content = xmlStrncat(cur->content, content, len);
            }
        case XML_DOCUMENT_NODE:
        case XML_DTD_NODE:
        case XML_HTML_DOCUMENT_NODE:
        case XML_DOCUMENT_TYPE_NODE:
	case XML_NAMESPACE_DECL:
	case XML_XINCLUDE_START:
	case XML_XINCLUDE_END:
#ifdef LIBXML_DOCB_ENABLED
	case XML_DOCB_DOCUMENT_NODE:
#endif
	    break;
        case XML_ELEMENT_DECL:
        case XML_ATTRIBUTE_DECL:
        case XML_ENTITY_DECL:
	    break;
    }
