switch (set->nodeTab[i]->type) {
		    case XML_TEXT_NODE:
		    case XML_CDATA_SECTION_NODE:
		    case XML_ELEMENT_NODE:
		    case XML_ENTITY_REF_NODE:
		    case XML_ENTITY_NODE:
		    case XML_PI_NODE:
		    case XML_COMMENT_NODE:
		    case XML_DOCUMENT_NODE:
		    case XML_HTML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
		    case XML_DOCB_DOCUMENT_NODE:
#endif
		    case XML_XINCLUDE_END:
			break;
		    case XML_XINCLUDE_START: {
	                xmlNodePtr tmp, cur = set->nodeTab[i];

			cur = cur->next;
			while (cur != NULL) {
			    switch(cur->type) {
				case XML_TEXT_NODE:
				case XML_CDATA_SECTION_NODE:
				case XML_ELEMENT_NODE:
				case XML_ENTITY_REF_NODE:
				case XML_ENTITY_NODE:
				case XML_PI_NODE:
				case XML_COMMENT_NODE:
				    tmp = xmlXIncludeCopyNode(ctxt, target,
							      source, cur);
				    if (last == NULL) {
					list = last = tmp;
				    } else {
					xmlAddNextSibling(last, tmp);
					last = tmp;
				    }
				    cur = cur->next;
				    continue;
				default:
				    break;
			    }
			    break;
			}
			continue;
		    }
		    case XML_ATTRIBUTE_NODE:
		    case XML_NAMESPACE_DECL:
		    case XML_DOCUMENT_TYPE_NODE:
		    case XML_DOCUMENT_FRAG_NODE:
		    case XML_NOTATION_NODE:
		    case XML_DTD_NODE:
		    case XML_ELEMENT_DECL:
		    case XML_ATTRIBUTE_DECL:
		    case XML_ENTITY_DECL:
			continue; /* for */
		}
