if ((reader->node != NULL) &&
	(reader->node->type == XML_ENTITY_REF_NODE) &&
	(reader->ctxt != NULL) && (reader->ctxt->replaceEntities == 1)) {
	/*
	 * Case where the underlying tree is not availble, lookup the entity
	 * and walk it.
	 */
	if ((reader->node->children == NULL) && (reader->ctxt->sax != NULL) &&
	    (reader->ctxt->sax->getEntity != NULL)) {
	    reader->node->children = (xmlNodePtr)
		reader->ctxt->sax->getEntity(reader->ctxt, reader->node->name);
	}

	if ((reader->node->children != NULL) &&
	    (reader->node->children->type == XML_ENTITY_DECL) &&
	    (reader->node->children->children != NULL)) {
	    xmlTextReaderEntPush(reader, reader->node);
	    reader->node = reader->node->children->children;
	}
#ifdef LIBXML_REGEXP_ENABLED
    } else if ((reader->node != NULL) &&
	       (reader->node->type == XML_ENTITY_REF_NODE) &&
	       (reader->ctxt != NULL) && (reader->validate)) {
	xmlTextReaderValidateEntity(reader);
#endif /* LIBXML_REGEXP_ENABLED */
    }
#endif
