#ifdef LIBXML_HTML_ENABLED
if ((ctxt->html) &&
        (value == NULL) && (htmlIsBooleanAttr(fullname))) {
            nval = xmlStrdup(fullname);
            value = (const xmlChar *) nval;
    } else
#endif
    {
#ifdef LIBXML_VALID_ENABLED
        /*
         * Do the last stage of the attribute normalization
         * Needed for HTML too:
         *   http://www.w3.org/TR/html4/types.html#h-6.2
         */
        ctxt->vctxt.valid = 1;
        nval = xmlValidCtxtNormalizeAttributeValue(&ctxt->vctxt,
                                               ctxt->myDoc, ctxt->node,
                                               fullname, value);
        if (ctxt->vctxt.valid != 1) {
            ctxt->valid = 0;
        }
        if (nval != NULL)
            value = nval;
#else
        nval = NULL;
#endif /* LIBXML_VALID_ENABLED */
    }
