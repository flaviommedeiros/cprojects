if ((debug)
#ifdef LIBXML_PATTERN_ENABLED
	        || (patternc)
#endif
	       )
		processNode(reader);
