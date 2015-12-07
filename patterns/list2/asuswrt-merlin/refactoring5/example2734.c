#ifdef LIBXML_SCHEMAS_ENABLED
if (wxschemas != NULL) {
        int ret;
	xmlSchemaValidCtxtPtr vctxt;

	vctxt = xmlSchemaNewValidCtxt(wxschemas);
	xmlSchemaSetValidErrors(vctxt,
		(xmlSchemaValidityErrorFunc) fprintf,
		(xmlSchemaValidityWarningFunc) fprintf,
		stderr);

	ret = xmlSchemaValidateStream(vctxt, buf, 0, handler,
	                              (void *)user_data);
	if (repeat == 0) {
	    if (ret == 0) {
		fprintf(stderr, "%s validates\n", filename);
	    } else if (ret > 0) {
		fprintf(stderr, "%s fails to validate\n", filename);
		progresult = XMLLINT_ERR_VALID;
	    } else {
		fprintf(stderr, "%s validation generated an internal error\n",
		       filename);
		progresult = XMLLINT_ERR_VALID;
	    }
	}
	xmlSchemaFreeValidCtxt(vctxt);
    } else
#endif
    {
	/*
	 * Create the parser context amd hook the input
	 */
	ctxt = xmlNewParserCtxt();
	if (ctxt == NULL) {
	    xmlFreeParserInputBuffer(buf);
	    goto error;
	}
	old_sax = ctxt->sax;
	ctxt->sax = handler;
	ctxt->userData = (void *) user_data;
	inputStream = xmlNewIOInputStream(ctxt, buf, XML_CHAR_ENCODING_NONE);
	if (inputStream == NULL) {
	    xmlFreeParserInputBuffer(buf);
	    goto error;
	}
	inputPush(ctxt, inputStream);

	/* do the parsing */
	xmlParseDocument(ctxt);

	if (ctxt->myDoc != NULL) {
	    fprintf(stderr, "SAX generated a doc !\n");
	    xmlFreeDoc(ctxt->myDoc);
	    ctxt->myDoc = NULL;
	}
    }
