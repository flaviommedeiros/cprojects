#ifdef LIBXML_SAX1_ENABLED
if (ctxt->sax != (xmlSAXHandlerPtr) &xmlDefaultSAXHandler)
#endif /* LIBXML_SAX1_ENABLED */
	xmlFree(ctxt->sax);
