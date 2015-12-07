if ((op->ch1 != -1) && (op->ch2 != -1) &&
#ifdef XP_OPTIMIZED_FILTER_FIRST
		    /*
		    * FILTER TODO: Can we assume that the inner processing
		    *  will result in an ordered list if we have an
		    *  XPATH_OP_FILTER?
		    *  What about an additional field or flag on
		    *  xmlXPathObject like @sorted ? This way we wouln'd need
		    *  to assume anything, so it would be more robust and
		    *  easier to optimize.
		    */
                    ((comp->steps[op->ch1].op == XPATH_OP_SORT) || /* 18 */
		     (comp->steps[op->ch1].op == XPATH_OP_FILTER)) && /* 17 */
#else
		    (comp->steps[op->ch1].op == XPATH_OP_SORT) &&
#endif
                    (comp->steps[op->ch2].op == XPATH_OP_VALUE)) { /* 12 */
                    xmlXPathObjectPtr val;

                    val = comp->steps[op->ch2].value4;
                    if ((val != NULL) && (val->type == XPATH_NUMBER) &&
                        (val->floatval == 1.0)) {
                        xmlNodePtr first = NULL;

                        total +=
                            xmlXPathCompOpEvalFirst(ctxt,
                                                    &comp->steps[op->ch1],
                                                    &first);
			CHECK_ERROR0;
                        /*
                         * The nodeset should be in document order,
                         * Keep only the first value
                         */
                        if ((ctxt->value != NULL) &&
                            (ctxt->value->type == XPATH_NODESET) &&
                            (ctxt->value->nodesetval != NULL) &&
                            (ctxt->value->nodesetval->nodeNr > 1))
                            ctxt->value->nodesetval->nodeNr = 1;
                        return (total);
                    }
                }
