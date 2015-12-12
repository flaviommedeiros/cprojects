if (pn->pn_type == TOK_INC || pn->pn_type == TOK_DEC ||
            pn->pn_type == TOK_THROW ||
#if JS_HAS_GENERATORS
            pn->pn_type == TOK_YIELD ||
#endif
            pn->pn_type == TOK_DEFSHARP) {
            /* All these operations have effects that we must commit. */
            *answer = JS_TRUE;
        } else if (pn->pn_type == TOK_DELETE) {
            pn2 = pn->pn_kid;
            switch (pn2->pn_type) {
              case TOK_NAME:
              case TOK_DOT:
#if JS_HAS_XML_SUPPORT
              case TOK_DBLDOT:
#endif
#if JS_HAS_LVALUE_RETURN
              case TOK_LP:
#endif
              case TOK_LB:
                /* All these delete addressing modes have effects too. */
                *answer = JS_TRUE;
                break;
              default:
                ok = CheckSideEffects(cx, tc, pn2, answer);
                break;
            }
        } else {
            ok = CheckSideEffects(cx, tc, pn->pn_kid, answer);
        }
