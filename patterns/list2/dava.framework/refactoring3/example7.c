switch (node->type) {
        case XML_ELEMENT_NODE:
        case XML_ATTRIBUTE_NODE:
	    xmlCtxtCheckName(ctxt, node->name);
	    break;
        case XML_TEXT_NODE:
	    if ((node->name == xmlStringText) ||
	        (node->name == xmlStringTextNoenc))
		break;
	    /* some case of entity substitution can lead to this */
	    if ((ctxt->dict != NULL) &&
	        (node->name == xmlDictLookup(ctxt->dict, BAD_CAST "nbktext",
		                             7)))
		break;

	    xmlDebugErr3(ctxt, XML_CHECK_WRONG_NAME,
			 "Text node has wrong name '%s'",
			 (const char *) node->name);
	    break;
        case XML_COMMENT_NODE:
	    if (node->name == xmlStringComment)
		break;
	    xmlDebugErr3(ctxt, XML_CHECK_WRONG_NAME,
			 "Comment node has wrong name '%s'",
			 (const char *) node->name);
	    break;
        case XML_PI_NODE:
	    xmlCtxtCheckName(ctxt, node->name);
	    break;
        case XML_CDATA_SECTION_NODE:
	    if (node->name == NULL)
		break;
	    xmlDebugErr3(ctxt, XML_CHECK_NAME_NOT_NULL,
			 "CData section has non NULL name '%s'",
			 (const char *) node->name);
	    break;
        case XML_ENTITY_REF_NODE:
        case XML_ENTITY_NODE:
        case XML_DOCUMENT_TYPE_NODE:
        case XML_DOCUMENT_FRAG_NODE:
        case XML_NOTATION_NODE:
        case XML_DTD_NODE:
        case XML_ELEMENT_DECL:
        case XML_ATTRIBUTE_DECL:
        case XML_ENTITY_DECL:
        case XML_NAMESPACE_DECL:
        case XML_XINCLUDE_START:
        case XML_XINCLUDE_END:
#ifdef LIBXML_DOCB_ENABLED
        case XML_DOCB_DOCUMENT_NODE:
#endif
        case XML_DOCUMENT_NODE:
        case XML_HTML_DOCUMENT_NODE:
	    break;
    }
