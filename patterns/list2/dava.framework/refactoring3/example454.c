switch (cur->type) {
        case XML_ELEMENT_NODE:
            ret = xmlC14NProcessElementNode(ctx, cur, visible);
            break;
        case XML_CDATA_SECTION_NODE:
        case XML_TEXT_NODE:
            /*
             * Text Nodes
             * the string value, except all ampersands are replaced 
             * by &amp;, all open angle brackets (<) are replaced by &lt;, all closing 
             * angle brackets (>) are replaced by &gt;, and all #xD characters are 
             * replaced by &#xD;.
             */
            /* cdata sections are processed as text nodes */
            /* todo: verify that cdata sections are included in XPath nodes set */
            if ((visible) && (cur->content != NULL)) {
                xmlChar *buffer;

                buffer = xmlC11NNormalizeText(cur->content);
                if (buffer != NULL) {
                    xmlOutputBufferWriteString(ctx->buf,
                                               (const char *) buffer);
                    xmlFree(buffer);
                } else {
                    xmlC14NErrInternal("normalizing text node");
                    return (-1);
                }
            }
            break;
        case XML_PI_NODE:
            /* 
             * Processing Instruction (PI) Nodes- 
             * The opening PI symbol (<?), the PI target name of the node, 
             * a leading space and the string value if it is not empty, and 
             * the closing PI symbol (?>). If the string value is empty, 
             * then the leading space is not added. Also, a trailing #xA is 
             * rendered after the closing PI symbol for PI children of the 
             * root node with a lesser document order than the document 
             * element, and a leading #xA is rendered before the opening PI 
             * symbol of PI children of the root node with a greater document 
             * order than the document element.
             */
            if (visible) {
                if (ctx->pos == XMLC14N_AFTER_DOCUMENT_ELEMENT) {
                    xmlOutputBufferWriteString(ctx->buf, "\x0A<?");
                } else {
                    xmlOutputBufferWriteString(ctx->buf, "<?");
                }

                xmlOutputBufferWriteString(ctx->buf,
                                           (const char *) cur->name);
                if ((cur->content != NULL) && (*(cur->content) != '\0')) {
                    xmlChar *buffer;

                    xmlOutputBufferWriteString(ctx->buf, " ");

                    /* todo: do we need to normalize pi? */
                    buffer = xmlC11NNormalizePI(cur->content);
                    if (buffer != NULL) {
                        xmlOutputBufferWriteString(ctx->buf,
                                                   (const char *) buffer);
                        xmlFree(buffer);
                    } else {
                        xmlC14NErrInternal("normalizing pi node");
                        return (-1);
                    }
                }

                if (ctx->pos == XMLC14N_BEFORE_DOCUMENT_ELEMENT) {
                    xmlOutputBufferWriteString(ctx->buf, "?>\x0A");
                } else {
                    xmlOutputBufferWriteString(ctx->buf, "?>");
                }
            }
            break;
        case XML_COMMENT_NODE:
            /*
             * Comment Nodes
             * Nothing if generating canonical XML without  comments. For 
             * canonical XML with comments, generate the opening comment 
             * symbol (<!--), the string value of the node, and the 
             * closing comment symbol (-->). Also, a trailing #xA is rendered 
             * after the closing comment symbol for comment children of the 
             * root node with a lesser document order than the document 
             * element, and a leading #xA is rendered before the opening 
             * comment symbol of comment children of the root node with a 
             * greater document order than the document element. (Comment 
             * children of the root node represent comments outside of the 
             * top-level document element and outside of the document type 
             * declaration).
             */
            if (visible && ctx->with_comments) {
                if (ctx->pos == XMLC14N_AFTER_DOCUMENT_ELEMENT) {
                    xmlOutputBufferWriteString(ctx->buf, "\x0A<!--");
                } else {
                    xmlOutputBufferWriteString(ctx->buf, "<!--");
                }

                if (cur->content != NULL) {
                    xmlChar *buffer;

                    /* todo: do we need to normalize comment? */
                    buffer = xmlC11NNormalizeComment(cur->content);
                    if (buffer != NULL) {
                        xmlOutputBufferWriteString(ctx->buf,
                                                   (const char *) buffer);
                        xmlFree(buffer);
                    } else {
                        xmlC14NErrInternal("normalizing comment node");
                        return (-1);
                    }
                }

                if (ctx->pos == XMLC14N_BEFORE_DOCUMENT_ELEMENT) {
                    xmlOutputBufferWriteString(ctx->buf, "-->\x0A");
                } else {
                    xmlOutputBufferWriteString(ctx->buf, "-->");
                }
            }
            break;
        case XML_DOCUMENT_NODE:
        case XML_DOCUMENT_FRAG_NODE:   /* should be processed as document? */
#ifdef LIBXML_DOCB_ENABLED
        case XML_DOCB_DOCUMENT_NODE:   /* should be processed as document? */
#endif
#ifdef LIBXML_HTML_ENABLED
        case XML_HTML_DOCUMENT_NODE:   /* should be processed as document? */
#endif
            if (cur->children != NULL) {
                ctx->pos = XMLC14N_BEFORE_DOCUMENT_ELEMENT;
                ctx->parent_is_doc = 1;
                ret = xmlC14NProcessNodeList(ctx, cur->children);
            }
            break;

        case XML_ATTRIBUTE_NODE:
            xmlC14NErrInvalidNode("XML_ATTRIBUTE_NODE", "processing node");
            return (-1);
        case XML_NAMESPACE_DECL:
            xmlC14NErrInvalidNode("XML_NAMESPACE_DECL", "processing node");
            return (-1);
        case XML_ENTITY_REF_NODE:
            xmlC14NErrInvalidNode("XML_ENTITY_REF_NODE", "processing node");
            return (-1);
        case XML_ENTITY_NODE:
            xmlC14NErrInvalidNode("XML_ENTITY_NODE", "processing node");
            return (-1);

        case XML_DOCUMENT_TYPE_NODE:
        case XML_NOTATION_NODE:
        case XML_DTD_NODE:
        case XML_ELEMENT_DECL:
        case XML_ATTRIBUTE_DECL:
        case XML_ENTITY_DECL:
#ifdef LIBXML_XINCLUDE_ENABLED
        case XML_XINCLUDE_START:
        case XML_XINCLUDE_END:
#endif
            /* 
             * should be ignored according to "W3C Canonical XML" 
             */
            break;
        default:
            xmlC14NErrUnknownNode(cur->type, "processing node");
            return (-1);
    }
