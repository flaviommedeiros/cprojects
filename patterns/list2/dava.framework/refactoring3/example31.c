switch (cur->type) {
        case XML_DOCUMENT_FRAG_NODE:
        case XML_ELEMENT_NODE:
        case XML_ATTRIBUTE_NODE:
	    if (cur->children != NULL) xmlFreeNodeList(cur->children);
	    cur->children = xmlStringLenGetNodeList(cur->doc, content, len);
	    UPDATE_LAST_CHILD_AND_PARENT(cur)
	    break;
        case XML_TEXT_NODE:
        case XML_CDATA_SECTION_NODE:
        case XML_ENTITY_REF_NODE:
        case XML_ENTITY_NODE:
        case XML_PI_NODE:
        case XML_COMMENT_NODE:
        case XML_NOTATION_NODE:
	    if ((cur->content != NULL) &&
	        (cur->content != (xmlChar *) &(cur->properties))) {
	        if (!((cur->doc != NULL) && (cur->doc->dict != NULL) &&
		    (xmlDictOwns(cur->doc->dict, cur->content))))
		    xmlFree(cur->content);
	    }
	    if (cur->children != NULL) xmlFreeNodeList(cur->children);
	    cur->children = cur->last = NULL;
	    if (content != NULL) {
		cur->content = xmlStrndup(content, len);
	    } else
		cur->content = NULL;
	    cur->properties = NULL;
	    cur->nsDef = NULL;
	    break;
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
	    /* TODO !!! */
	    break;
        case XML_ATTRIBUTE_DECL:
	    /* TODO !!! */
	    break;
        case XML_ENTITY_DECL:
	    /* TODO !!! */
	    break;
    }