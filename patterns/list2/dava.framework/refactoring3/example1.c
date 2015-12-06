switch (node->type) {
        case XML_ELEMENT_NODE:
	    if ((reader->state == XML_TEXTREADER_END) ||
		(reader->state == XML_TEXTREADER_BACKTRACK))
		return(XML_READER_TYPE_END_ELEMENT);
	    return(XML_READER_TYPE_ELEMENT);
        case XML_NAMESPACE_DECL:
        case XML_ATTRIBUTE_NODE:
	    return(XML_READER_TYPE_ATTRIBUTE);
        case XML_TEXT_NODE:
	    if (xmlIsBlankNode(reader->node)) {
		if (xmlNodeGetSpacePreserve(reader->node))
		    return(XML_READER_TYPE_SIGNIFICANT_WHITESPACE);
		else
		    return(XML_READER_TYPE_WHITESPACE);
	    } else {
		return(XML_READER_TYPE_TEXT);
	    }
        case XML_CDATA_SECTION_NODE:
	    return(XML_READER_TYPE_CDATA);
        case XML_ENTITY_REF_NODE:
	    return(XML_READER_TYPE_ENTITY_REFERENCE);
        case XML_ENTITY_NODE:
	    return(XML_READER_TYPE_ENTITY);
        case XML_PI_NODE:
	    return(XML_READER_TYPE_PROCESSING_INSTRUCTION);
        case XML_COMMENT_NODE:
	    return(XML_READER_TYPE_COMMENT);
        case XML_DOCUMENT_NODE:
        case XML_HTML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
        case XML_DOCB_DOCUMENT_NODE:
#endif
	    return(XML_READER_TYPE_DOCUMENT);
        case XML_DOCUMENT_FRAG_NODE:
	    return(XML_READER_TYPE_DOCUMENT_FRAGMENT);
        case XML_NOTATION_NODE:
	    return(XML_READER_TYPE_NOTATION);
        case XML_DOCUMENT_TYPE_NODE:
        case XML_DTD_NODE:
	    return(XML_READER_TYPE_DOCUMENT_TYPE);

        case XML_ELEMENT_DECL:
        case XML_ATTRIBUTE_DECL:
        case XML_ENTITY_DECL:
        case XML_XINCLUDE_START:
        case XML_XINCLUDE_END:
	    return(XML_READER_TYPE_NONE);
    }
