if ((schematron != NULL) && (sax == 0)
#ifdef LIBXML_READER_ENABLED
        && (stream == 0)
#endif /* LIBXML_READER_ENABLED */
	) {
	xmlSchematronParserCtxtPtr ctxt;

        /* forces loading the DTDs */
        xmlLoadExtDtdDefaultValue |= 1;
	options |= XML_PARSE_DTDLOAD;
	if (timing) {
	    startTimer();
	}
	ctxt = xmlSchematronNewParserCtxt(schematron);
#if 0
	xmlSchematronSetParserErrors(ctxt,
		(xmlSchematronValidityErrorFunc) fprintf,
		(xmlSchematronValidityWarningFunc) fprintf,
		stderr);
#endif
	wxschematron = xmlSchematronParse(ctxt);
	if (wxschematron == NULL) {
	    xmlGenericError(xmlGenericErrorContext,
		    "Schematron schema %s failed to compile\n", schematron);
            progresult = XMLLINT_ERR_SCHEMACOMP;
	    schematron = NULL;
	}
	xmlSchematronFreeParserCtxt(ctxt);
	if (timing) {
	    endTimer("Compiling the schemas");
	}
    }
