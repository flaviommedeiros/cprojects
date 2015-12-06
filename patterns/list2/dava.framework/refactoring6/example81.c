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
