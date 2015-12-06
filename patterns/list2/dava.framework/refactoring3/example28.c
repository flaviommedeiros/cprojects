switch (cur->type) {
        case XML_CDATA_SECTION_NODE:
        case XML_TEXT_NODE:
	    xmlBufferCat(buffer, cur->content);
            break;
        case XML_DOCUMENT_FRAG_NODE:
        case XML_ELEMENT_NODE:{
                xmlNodePtr tmp = cur;

                while (tmp != NULL) {
                    switch (tmp->type) {
                        case XML_CDATA_SECTION_NODE:
                        case XML_TEXT_NODE:
                            if (tmp->content != NULL)
                                xmlBufferCat(buffer, tmp->content);
                            break;
                        case XML_ENTITY_REF_NODE:
                            xmlNodeBufGetContent(buffer, tmp);
                            break;
                        default:
                            break;
                    }
                    /*
                     * Skip to next node
                     */
                    if (tmp->children != NULL) {
                        if (tmp->children->type != XML_ENTITY_DECL) {
                            tmp = tmp->children;
                            continue;
                        }
                    }
                    if (tmp == cur)
                        break;

                    if (tmp->next != NULL) {
                        tmp = tmp->next;
                        continue;
                    }

                    do {
                        tmp = tmp->parent;
                        if (tmp == NULL)
                            break;
                        if (tmp == cur) {
                            tmp = NULL;
                            break;
                        }
                        if (tmp->next != NULL) {
                            tmp = tmp->next;
                            break;
                        }
                    } while (tmp != NULL);
                }
		break;
            }
        case XML_ATTRIBUTE_NODE:{
                xmlAttrPtr attr = (xmlAttrPtr) cur;
		xmlNodePtr tmp = attr->children;

		while (tmp != NULL) {
		    if (tmp->type == XML_TEXT_NODE)
		        xmlBufferCat(buffer, tmp->content);
		    else
		        xmlNodeBufGetContent(buffer, tmp);
		    tmp = tmp->next;
		}
                break;
            }
        case XML_COMMENT_NODE:
        case XML_PI_NODE:
	    xmlBufferCat(buffer, cur->content);
            break;
        case XML_ENTITY_REF_NODE:{
                xmlEntityPtr ent;
                xmlNodePtr tmp;

                /* lookup entity declaration */
                ent = xmlGetDocEntity(cur->doc, cur->name);
                if (ent == NULL)
                    return(-1);

                /* an entity content can be any "well balanced chunk",
                 * i.e. the result of the content [43] production:
                 * http://www.w3.org/TR/REC-xml#NT-content
                 * -> we iterate through child nodes and recursive call
                 * xmlNodeGetContent() which handles all possible node types */
                tmp = ent->children;
                while (tmp) {
		    xmlNodeBufGetContent(buffer, tmp);
                    tmp = tmp->next;
                }
		break;
            }
        case XML_ENTITY_NODE:
        case XML_DOCUMENT_TYPE_NODE:
        case XML_NOTATION_NODE:
        case XML_DTD_NODE:
        case XML_XINCLUDE_START:
        case XML_XINCLUDE_END:
            break;
        case XML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
        case XML_DOCB_DOCUMENT_NODE:
#endif
        case XML_HTML_DOCUMENT_NODE:
	    cur = cur->children;
	    while (cur!= NULL) {
		if ((cur->type == XML_ELEMENT_NODE) ||
		    (cur->type == XML_TEXT_NODE) ||
		    (cur->type == XML_CDATA_SECTION_NODE)) {
		    xmlNodeBufGetContent(buffer, cur);
		}
		cur = cur->next;
	    }
	    break;
        case XML_NAMESPACE_DECL:
	    xmlBufferCat(buffer, ((xmlNsPtr) cur)->href);
	    break;
        case XML_ELEMENT_DECL:
        case XML_ATTRIBUTE_DECL:
        case XML_ENTITY_DECL:
            break;
    }
