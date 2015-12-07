#ifdef LIBXML_XINCLUDE_ENABLED
if (options & XML_PARSE_XINCLUDE) {
	doc = xmlReadFile(filename, NULL, options);
	xmlXIncludeProcessFlags(doc, options);
    } else
#endif
    {
	xmlGetWarningsDefaultValue = 1;
	doc = xmlReadFile(filename, NULL, options);
    }
