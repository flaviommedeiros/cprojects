#ifdef LIBXML_XPTR_ENABLED
if (rangeto) {
	    PUSH_BINARY_EXPR(XPATH_OP_RANGETO, op2, op1, 0, 0);
	} else
#endif
	    PUSH_FULL_EXPR(XPATH_OP_COLLECT, op1, ctxt->comp->last, axis,
			   test, type, (void *)prefix, (void *)name);
