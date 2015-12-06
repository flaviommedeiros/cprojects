switch (node->type) {
        case XML_ELEMENT_NODE:
        case XML_ATTRIBUTE_NODE:
	    if ((node->ns == NULL) ||
		(node->ns->prefix == NULL))
		return(xmlStrdup(node->name));

	    ret = xmlStrdup(node->ns->prefix);
	    ret = xmlStrcat(ret, BAD_CAST ":");
	    ret = xmlStrcat(ret, node->name);
	    return(ret);
        case XML_TEXT_NODE:
	    return(xmlStrdup(BAD_CAST "#text"));
        case XML_CDATA_SECTION_NODE:
	    return(xmlStrdup(BAD_CAST "#cdata-section"));
        case XML_ENTITY_NODE:
        case XML_ENTITY_REF_NODE:
	    return(xmlStrdup(node->name));
        case XML_PI_NODE:
	    return(xmlStrdup(node->name));
        case XML_COMMENT_NODE:
	    return(xmlStrdup(BAD_CAST "#comment"));
        case XML_DOCUMENT_NODE:
        case XML_HTML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
        case XML_DOCB_DOCUMENT_NODE:
#endif
	    return(xmlStrdup(BAD_CAST "#document"));
        case XML_DOCUMENT_FRAG_NODE:
	    return(xmlStrdup(BAD_CAST "#document-fragment"));
        case XML_NOTATION_NODE:
	    return(xmlStrdup(node->name));
        case XML_DOCUMENT_TYPE_NODE:
        case XML_DTD_NODE:
	    return(xmlStrdup(node->name));
        case XML_NAMESPACE_DECL: {
	    xmlNsPtr ns = (xmlNsPtr) node;

	    ret = xmlStrdup(BAD_CAST "xmlns");
	    if (ns->prefix == NULL)
		return(ret);
	    ret = xmlStrcat(ret, BAD_CAST ":");
	    ret = xmlStrcat(ret, ns->prefix);
	    return(ret);
	}

        case XML_ELEMENT_DECL:
        case XML_ATTRIBUTE_DECL:
        case XML_ENTITY_DECL:
        case XML_XINCLUDE_START:
        case XML_XINCLUDE_END:
	    return(NULL);
    }
