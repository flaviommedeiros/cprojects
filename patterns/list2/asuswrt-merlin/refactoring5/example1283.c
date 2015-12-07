#ifdef LIBXML_SCHEMAS_ENABLED
if (relaxng != NULL)
		endTimer("Parsing and validating");
	    else
#endif
#ifdef LIBXML_VALID_ENABLED
	    if (valid)
		endTimer("Parsing and validating");
	    else
#endif
	    endTimer("Parsing");
