if (kid->pn_type != TOK_NAME &&
        kid->pn_type != TOK_DOT &&
#if JS_HAS_LVALUE_RETURN
        (kid->pn_type != TOK_LP || kid->pn_op != JSOP_CALL) &&
#endif
#if JS_HAS_XML_SUPPORT
        (kid->pn_type != TOK_UNARYOP || kid->pn_op != JSOP_XMLNAME) &&
#endif
        kid->pn_type != TOK_LB) {
        js_ReportCompileErrorNumber(cx, ts, JSREPORT_TS | JSREPORT_ERROR,
                                    JSMSG_BAD_OPERAND, name);
        return NULL;
    }
