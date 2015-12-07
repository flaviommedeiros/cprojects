#ifdef LIBXML_EXPR_ENABLED
if (use_exp) {
	    for (i = 1; i < argc ; i++) {
	        if (strcmp(argv[i], "--") == 0)
		    data = 1;
		else if ((argv[i][0] != '-') || (strcmp(argv[i], "-") == 0) ||
		    (data == 1)) {
		    if (pattern == NULL) {
			pattern = argv[i];
			printf("Testing expr %s:\n", pattern);
			expr = xmlExpParse(ctxt, pattern);
			if (expr == NULL) {
			    printf("   failed to compile\n");
			    break;
			}
			if (debug) {
			    exprDebug(ctxt, expr);
			}
		    } else {
			testReduce(ctxt, expr, argv[i]);
		    }
		}
	    }
	    if (expr != NULL) {
		xmlExpFree(ctxt, expr);
		expr = NULL;
	    }
	} else
#endif
        {
	    for (i = 1; i < argc ; i++) {
	        if (strcmp(argv[i], "--") == 0)
		    data = 1;
		else if ((argv[i][0] != '-') || (strcmp(argv[i], "-") == 0) ||
		         (data == 1)) {
		    if (pattern == NULL) {
			pattern = argv[i];
			printf("Testing %s:\n", pattern);
			comp = xmlRegexpCompile((const xmlChar *) pattern);
			if (comp == NULL) {
			    printf("   failed to compile\n");
			    break;
			}
			if (debug)
			    xmlRegexpPrint(stdout, comp);
		    } else {
			testRegexp(comp, argv[i]);
		    }
		}
	    }
	    if (comp != NULL)
		xmlRegFreeRegexp(comp);
        }
