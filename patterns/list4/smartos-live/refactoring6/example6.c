if (TOKEN_TYPE_IS_DECL(tt)
                ? (pn1->pn_count > 1 || pn1->pn_op == JSOP_DEFCONST
#if JS_HAS_DESTRUCTURING
                   || (pn->pn_op == JSOP_FORIN &&
                       (pn1->pn_head->pn_type == TOK_RC ||
                        (pn1->pn_head->pn_type == TOK_RB &&
                         pn1->pn_head->pn_count != 2) ||
                        (pn1->pn_head->pn_type == TOK_ASSIGN &&
                         (pn1->pn_head->pn_left->pn_type != TOK_RB ||
                          pn1->pn_head->pn_left->pn_count != 2))))
#endif
                  )
                : (pn1->pn_type != TOK_NAME &&
                   pn1->pn_type != TOK_DOT &&
#if JS_HAS_DESTRUCTURING
                   ((pn->pn_op == JSOP_FORIN)
                    ? (pn1->pn_type != TOK_RB || pn1->pn_count != 2)
                    : (pn1->pn_type != TOK_RB && pn1->pn_type != TOK_RC)) &&
#endif
#if JS_HAS_LVALUE_RETURN
                   pn1->pn_type != TOK_LP &&
#endif
#if JS_HAS_XML_SUPPORT
                   (pn1->pn_type != TOK_UNARYOP ||
                    pn1->pn_op != JSOP_XMLNAME) &&
#endif
                   pn1->pn_type != TOK_LB)) {
                js_ReportCompileErrorNumber(cx, ts,
                                            JSREPORT_TS | JSREPORT_ERROR,
                                            JSMSG_BAD_FOR_LEFTSIDE);
                return NULL;
            }
