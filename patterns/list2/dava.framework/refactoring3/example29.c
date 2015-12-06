switch (cur->type) {
        case XML_DOCUMENT_FRAG_NODE:
        case XML_ELEMENT_NODE:{
                xmlBufferPtr buffer;
                xmlChar *ret;

                buffer = xmlBufferCreateSize(64);
                if (buffer == NULL)
                    return (NULL);
		xmlNodeBufGetContent(buffer, cur);
                ret = buffer->content;
                buffer->content = NULL;
                xmlBufferFree(buffer);
                return (ret);
            }
        case XML_ATTRIBUTE_NODE:
	    return(xmlGetPropNodeValueInternal((xmlAttrPtr) cur));
        case XML_COMMENT_NODE:
        case XML_PI_NODE:
            if (cur->content != NULL)
                return (xmlStrdup(cur->content));
            return (NULL);
        case XML_ENTITY_REF_NODE:{
                xmlEntityPtr ent;
                xmlBufferPtr buffer;
                xmlChar *ret;

                /* lookup entity declaration */
                ent = xmlGetDocEntity(cur->doc, cur->name);
                if (ent == NULL)
                    return (NULL);

                buffer = xmlBufferCreate();
                if (buffer == NULL)
                    return (NULL);

                xmlNodeBufGetContent(buffer, cur);

                ret = buffer->content;
                buffer->content = NULL;
                xmlBufferFree(buffer);
                return (ret);
            }
        case XML_ENTITY_NODE:
        case XML_DOCUMENT_TYPE_NODE:
        case XML_NOTATION_NODE:
        case XML_DTD_NODE:
        case XML_XINCLUDE_START:
        case XML_XINCLUDE_END:
            return (NULL);
        case XML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
        case XML_DOCB_DOCUMENT_NODE:
#endif
        case XML_HTML_DOCUMENT_NODE: {
	    xmlBufferPtr buffer;
	    xmlChar *ret;

	    buffer = xmlBufferCreate();
	    if (buffer == NULL)
		return (NULL);

	    xmlNodeBufGetContent(buffer, (xmlNodePtr) cur);

	    ret = buffer->content;
	    buffer->content = NULL;
	    xmlBufferFree(buffer);
	    return (ret);
	}
        case XML_NAMESPACE_DECL: {
	    xmlChar *tmp;

	    tmp = xmlStrdup(((xmlNsPtr) cur)->href);
            return (tmp);
	}
        case XML_ELEMENT_DECL:
            /* TODO !!! */
            return (NULL);
        case XML_ATTRIBUTE_DECL:
            /* TODO !!! */
            return (NULL);
        case XML_ENTITY_DECL:
            /* TODO !!! */
            return (NULL);
        case XML_CDATA_SECTION_NODE:
        case XML_TEXT_NODE:
            if (cur->content != NULL)
                return (xmlStrdup(cur->content));
            return (NULL);
    }
