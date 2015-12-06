switch (cur->type) {
	case XML_ELEMENT_NODE:
	    xmlGenericError(xmlGenericErrorContext, "%s ", cur->name);
	    break;
	case XML_TEXT_NODE:
	    xmlGenericError(xmlGenericErrorContext, "text ");
	    break;
	case XML_CDATA_SECTION_NODE:
	    xmlGenericError(xmlGenericErrorContext, "cdata ");
	    break;
	case XML_ENTITY_REF_NODE:
	    xmlGenericError(xmlGenericErrorContext, "&%s; ", cur->name);
	    break;
	case XML_PI_NODE:
	    xmlGenericError(xmlGenericErrorContext, "pi(%s) ", cur->name);
	    break;
	case XML_COMMENT_NODE:
	    xmlGenericError(xmlGenericErrorContext, "comment ");
	    break;
	case XML_ATTRIBUTE_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?attr? ");
	    break;
	case XML_ENTITY_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?ent? ");
	    break;
	case XML_DOCUMENT_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?doc? ");
	    break;
	case XML_DOCUMENT_TYPE_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?doctype? ");
	    break;
	case XML_DOCUMENT_FRAG_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?frag? ");
	    break;
	case XML_NOTATION_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?nota? ");
	    break;
	case XML_HTML_DOCUMENT_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?html? ");
	    break;
#ifdef LIBXML_DOCB_ENABLED
	case XML_DOCB_DOCUMENT_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?docb? ");
	    break;
#endif
	case XML_DTD_NODE:
	    xmlGenericError(xmlGenericErrorContext, "?dtd? ");
	    break;
	case XML_ELEMENT_DECL:
	    xmlGenericError(xmlGenericErrorContext, "?edecl? ");
	    break;
	case XML_ATTRIBUTE_DECL:
	    xmlGenericError(xmlGenericErrorContext, "?adecl? ");
	    break;
	case XML_ENTITY_DECL:
	    xmlGenericError(xmlGenericErrorContext, "?entdecl? ");
	    break;
	case XML_NAMESPACE_DECL:
	    xmlGenericError(xmlGenericErrorContext, "?nsdecl? ");
	    break;
	case XML_XINCLUDE_START:
	    xmlGenericError(xmlGenericErrorContext, "incstart ");
	    break;
	case XML_XINCLUDE_END:
	    xmlGenericError(xmlGenericErrorContext, "incend ");
	    break;
    }
