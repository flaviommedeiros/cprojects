#ifdef LIBXML_EXPR_ENABLED
if (use_exp)
	    runFileTest(ctxt, filename);
	else
#endif
	    testRegexpFile(filename);
