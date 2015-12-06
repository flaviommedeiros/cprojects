if ((oldstate == XML_TEXTREADER_ELEMENT) &&
            (reader->node->type == XML_ELEMENT_NODE) &&
	    (reader->node->children == NULL) &&
	    ((reader->node->extra & NODE_IS_EMPTY) == 0)
#ifdef LIBXML_XINCLUDE_ENABLED
	    && (reader->in_xinclude <= 0)
#endif
	) {
	    reader->state = XML_TEXTREADER_END;
	    goto node_found;
	}
