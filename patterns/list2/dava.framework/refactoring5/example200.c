#ifdef LIBXML_VALID_ENABLED
if ((!ctxt->html) && ctxt->validate && ctxt->wellFormed &&
        ctxt->myDoc && ctxt->myDoc->intSubset) {
	
	/*
	 * If we don't substitute entities, the validation should be
	 * done on a value with replaced entities anyway.
	 */
        if (!ctxt->replaceEntities) {
	    xmlChar *val;

	    ctxt->depth++;
	    val = xmlStringDecodeEntities(ctxt, value, XML_SUBSTITUTE_REF,
		                          0,0,0);
	    ctxt->depth--;
	    
	    if (val == NULL)
		ctxt->valid &= xmlValidateOneAttribute(&ctxt->vctxt,
				ctxt->myDoc, ctxt->node, ret, value);
	    else {
		xmlChar *nvalnorm;

		/*
		 * Do the last stage of the attribute normalization
		 * It need to be done twice ... it's an extra burden related
		 * to the ability to keep xmlSAX2References in attributes
		 */
		nvalnorm = xmlValidNormalizeAttributeValue(ctxt->myDoc,
					    ctxt->node, fullname, val);
		if (nvalnorm != NULL) {
		    xmlFree(val);
		    val = nvalnorm;
		}

		ctxt->valid &= xmlValidateOneAttribute(&ctxt->vctxt,
			        ctxt->myDoc, ctxt->node, ret, val);
                xmlFree(val);
	    }
	} else {
	    ctxt->valid &= xmlValidateOneAttribute(&ctxt->vctxt, ctxt->myDoc,
					       ctxt->node, ret, value);
	}
    } else
#endif /* LIBXML_VALID_ENABLED */
           if (((ctxt->loadsubset & XML_SKIP_IDS) == 0) &&
	       (((ctxt->replaceEntities == 0) && (ctxt->external != 2)) ||
	        ((ctxt->replaceEntities != 0) && (ctxt->inSubset == 0)))) {
        /*
	 * when validating, the ID registration is done at the attribute
	 * validation level. Otherwise we have to do specific handling here.
	 */
	if (xmlIsID(ctxt->myDoc, ctxt->node, ret))
	    xmlAddID(&ctxt->vctxt, ctxt->myDoc, value, ret);
	else if (xmlIsRef(ctxt->myDoc, ctxt->node, ret))
	    xmlAddRef(&ctxt->vctxt, ctxt->myDoc, value, ret);
	else if (xmlStrEqual(fullname, BAD_CAST "xml:id")) {
	    /*
	     * Add the xml:id value
	     *
	     * Open issue: normalization of the value.
	     */
	    if (xmlValidateNCName(value, 1) != 0) {
	        xmlErrValid(ctxt, XML_DTD_XMLID_VALUE,
		      "xml:id : attribute value %s is not an NCName\n",
			    (const char *) value, NULL);
	    }
	    xmlAddID(&ctxt->vctxt, ctxt->myDoc, value, ret);
	}
    }
