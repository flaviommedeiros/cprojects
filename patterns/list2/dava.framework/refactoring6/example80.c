if ((reader->node == NULL) ||
	(reader->node->type == XML_DOCUMENT_NODE) ||
#ifdef LIBXML_DOCB_ENABLED
	(reader->node->type == XML_DOCB_DOCUMENT_NODE) ||
#endif
	(reader->node->type == XML_HTML_DOCUMENT_NODE)) {
	if (reader->mode != XML_TEXTREADER_DONE) {
	    val = xmlParseChunk(reader->ctxt, "", 0, 1);
	    reader->mode = XML_TEXTREADER_DONE;
	    if (val != 0)
	        return(-1);
	}
	reader->node = NULL;
	reader->depth = -1;

	/*
	 * Cleanup of the old node
	 */
	if ((reader->preserves == 0) &&
#ifdef LIBXML_XINCLUDE_ENABLED
	    (reader->in_xinclude == 0) &&
#endif
	    (reader->entNr == 0) &&
	    (oldnode->type != XML_DTD_NODE) &&
	    ((oldnode->extra & NODE_IS_PRESERVED) == 0) &&
	    (reader->entNr == 0)) {
	    xmlUnlinkNode(oldnode);
	    xmlTextReaderFreeNode(reader, oldnode);
	}

	goto node_end;
    }
