#ifdef LIBXML_VALID_ENABLED
if (valid)
	    xmlTextReaderSetParserProp(reader, XML_PARSER_VALIDATE, 1);
	else
#endif /* LIBXML_VALID_ENABLED */
	    xmlTextReaderSetParserProp(reader, XML_PARSER_LOADDTD, 1);
