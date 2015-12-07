if ((pattern != NULL)
#ifdef LIBXML_READER_ENABLED
        && (walker == 0)
#endif
	) {
        patternc = xmlPatterncompile((const xmlChar *) pattern, NULL, 0, NULL);
	if (patternc == NULL) {
	    xmlGenericError(xmlGenericErrorContext,
		    "Pattern %s failed to compile\n", pattern);
            progresult = XMLLINT_ERR_SCHEMAPAT;
	    pattern = NULL;
	}
    }
