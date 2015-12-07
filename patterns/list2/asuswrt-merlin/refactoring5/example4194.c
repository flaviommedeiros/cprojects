#ifdef LIBXML_SAX1_ENABLED
if (sax1)
		    doc = xmlParseFile(filename);
		else
#endif /* LIBXML_SAX1_ENABLED */
		doc = xmlReadFile(filename, NULL, options);
