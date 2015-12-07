if ((reader->preserves == 0) &&
#ifdef LIBXML_XINCLUDE_ENABLED
	    (reader->in_xinclude == 0) &&
#endif
	    (reader->entNr == 0) &&
	    (reader->node->prev != NULL) &&
            (reader->node->prev->type != XML_DTD_NODE) &&
	    (reader->entNr == 0)) {
	    xmlNodePtr tmp = reader->node->prev;
	    if ((tmp->extra & NODE_IS_PRESERVED) == 0) {
		xmlUnlinkNode(tmp);
		xmlTextReaderFreeNode(reader, tmp);
	    }
	}
