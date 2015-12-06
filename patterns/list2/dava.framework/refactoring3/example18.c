switch (cur->type) {
			    case XML_DOCUMENT_NODE:
			    case XML_HTML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
			    case XML_DOCB_DOCUMENT_NODE:
#endif
			    case XML_ELEMENT_NODE:
			    case XML_ATTRIBUTE_NODE:
			    case XML_PI_NODE:
			    case XML_COMMENT_NODE:
			    case XML_CDATA_SECTION_NODE:
			    case XML_TEXT_NODE:
			    case XML_NAMESPACE_DECL:
				XP_TEST_HIT
				break;
			    default:
				break;
			}
