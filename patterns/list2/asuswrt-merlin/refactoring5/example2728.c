#ifdef LIBXML_HTML_ENABLED
if (options & XML_PARSE_HTML)
        res = 1;
    else
#endif
    res = ctxt->wellFormed;
