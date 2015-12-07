if ((relaxng != NULL) && (sax == 0)
#ifdef LIBXML_READER_ENABLED
        && (stream == 0)
#endif /* LIBXML_READER_ENABLED */
	) {
	xmlRelaxNGParserCtxtPtr ctxt;

        /* forces loading the DTDs */
        xmlLoadExtDtdDefaultValue |= 1;
	options |= XML_PARSE_DTDLOAD;
	if (timing) {
	    startTimer();
	}
	ctxt = xmlRelaxNGNewParserCtxt(relaxng);
	xmlRelaxNGSetParserErrors(ctxt,
		(xmlRelaxNGValidityErrorFunc) fprintf,
		(xmlRelaxNGValidityWarningFunc) fprintf,
		stderr);
	relaxngschemas = xmlRelaxNGParse(ctxt);
	if (relaxngschemas == NULL) {
	    xmlGenericError(xmlGenericErrorContext,
		    "Relax-NG schema %s failed to compile\n", relaxng);
            progresult = XMLLINT_ERR_SCHEMACOMP;
	    relaxng = NULL;
	}
	xmlRelaxNGFreeParserCtxt(ctxt);
	if (timing) {
	    endTimer("Compiling the schemas");
	}
    } else if ((schema != NULL)
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
