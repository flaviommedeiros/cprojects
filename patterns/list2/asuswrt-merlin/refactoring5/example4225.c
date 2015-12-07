#ifdef LIBXML_VALID_ENABLED
if ((!ctxt->html) && ctxt->validate && ctxt->wellFormed &&
        ctxt->myDoc && ctxt->myDoc->intSubset) {
	/*
	 * If we don't substitute entities, the validation should be
	 * done on a value with replaced entities anyway.
	 */
        if (!ctxt->replaceEntities) {
	    dup = xmlSAX2DecodeAttrEntities(ctxt, value, valueend);
	    if (dup == NULL) {
	        if (*valueend == 0) {
		    ctxt->valid &= xmlValidateOneAttribute(&ctxt->vctxt,
				    ctxt->myDoc, ctxt->node, ret, value);
		} else {
		    /*
		     * That should already be normalized.
		     * cheaper to finally allocate here than duplicate
		     * entry points in the full validation code
		     */
		    dup = xmlStrndup(value, valueend - value);

		    ctxt->valid &= xmlValidateOneAttribute(&ctxt->vctxt,
				    ctxt->myDoc, ctxt->node, ret, dup);
		}
	    } else {
	        /*
		 * dup now contains a string of the flattened attribute
		 * content with entities substitued. Check if we need to
		 * apply an extra layer of normalization.
		 * It need to be done twice ... it's an extra burden related
		 * to the ability to keep references in attributes
		 */
		if (ctxt->attsSpecial != NULL) {
		    xmlChar *nvalnorm;
		    xmlChar fn[50];
		    xmlChar *fullname;
		    
		    fullname = xmlBuildQName(localname, prefix, fn, 50);
		    if (fullname != NULL) {
			ctxt->vctxt.valid = 1;
		        nvalnorm = xmlValidCtxtNormalizeAttributeValue(
			                 &ctxt->vctxt, ctxt->myDoc,
					 ctxt->node, fullname, dup);
			if (ctxt->vctxt.valid != 1)
			    ctxt->valid = 0;

			if ((fullname != fn) && (fullname != localname))
			    xmlFree(fullname);
			if (nvalnorm != NULL) {
			    xmlFree(dup);
			    dup = nvalnorm;
			}
		    }
		}

		ctxt->valid &= xmlValidateOneAttribute(&ctxt->vctxt,
			        ctxt->myDoc, ctxt->node, ret, dup);
	    }
	} else {
	    /*
	     * if entities already have been substitued, then
	     * the attribute as passed is already normalized
	     */
	    dup = xmlStrndup(value, valueend - value);

	    ctxt->valid &= xmlValidateOneAttribute(&ctxt->vctxt,
	                             ctxt->myDoc, ctxt->node, ret, dup);
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
        if ((prefix == ctxt->str_xml) &&
	           (localname[0] == 'i') && (localname[1] == 'd') &&
		   (localname[2] == 0)) {
	    /*
	     * Add the xml:id value
	     *
	     * Open issue: normalization of the value.
	     */
	    if (dup == NULL)
	        dup = xmlStrndup(value, valueend - value);
#ifdef LIBXML_VALID_ENABLED
	    if (xmlValidateNCName(dup, 1) != 0) {
	        xmlErrValid(ctxt, XML_DTD_XMLID_VALUE,
		      "xml:id : attribute value %s is not an NCName\n",
			    (const char *) dup, NULL);
	    }
#endif
	    xmlAddID(&ctxt->vctxt, ctxt->myDoc, dup, ret);
	} else if (xmlIsID(ctxt->myDoc, ctxt->node, ret)) {
	    /* might be worth duplicate entry points and not copy */
	    if (dup == NULL)
	        dup = xmlStrndup(value, valueend - value);
	    xmlAddID(&ctxt->vctxt, ctxt->myDoc, dup, ret);
	} else if (xmlIsRef(ctxt->myDoc, ctxt->node, ret)) {
	    if (dup == NULL)
	        dup = xmlStrndup(value, valueend - value);
	    xmlAddRef(&ctxt->vctxt, ctxt->myDoc, dup, ret);
	}
    }
