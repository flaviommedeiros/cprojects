if ((reader->preserves == 0) &&
#ifdef LIBXML_XINCLUDE_ENABLED
        (reader->in_xinclude == 0) &&
#endif
	(reader->entNr == 0) &&
        (reader->node->last != NULL) &&
        ((reader->node->last->extra & NODE_IS_PRESERVED) == 0)) {
	xmlNodePtr tmp = reader->node->last;
	xmlUnlinkNode(tmp);
	xmlTextReaderFreeNode(reader, tmp);
    }
