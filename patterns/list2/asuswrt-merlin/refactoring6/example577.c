if ((schema != NULL)
#ifdef LIBXML_READER_ENABLED
		&& (stream == 0)
#endif
	) {
	xmlSchemaParserCtxtPtr ctxt;

	if (timing) {
	    startTimer();
	}
	ctxt = xmlSchemaNewParserCtxt(schema);
	xmlSchemaSetParserErrors(ctxt,
		(xmlSchemaValidityErrorFunc) fprintf,
		(xmlSchemaValidityWarningFunc) fprintf,
		stderr);
	wxschemas = xmlSchemaParse(ctxt);
	if (wxschemas == NULL) {
	    xmlGenericError(xmlGenericErrorContext,
		    "WXS schema %s failed to compile\n", schema);
            progresult = XMLLINT_ERR_SCHEMACOMP;
	    schema = NULL;
	}
	xmlSchemaFreeParserCtxt(ctxt);
	if (timing) {
	    endTimer("Compiling the schemas");
	}
    }
