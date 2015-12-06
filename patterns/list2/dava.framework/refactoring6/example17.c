if ((*ctxt->cur != 0) && (ctxt->comp != NULL)
#ifdef XPATH_STREAMING
            && (ctxt->comp->stream == NULL)
#endif
	      ) {
	xmlXPatherror(ctxt, __FILE__, __LINE__, XPATH_EXPR_ERROR);
	res = NULL;
    } else {
	res = valuePop(ctxt);
    }
