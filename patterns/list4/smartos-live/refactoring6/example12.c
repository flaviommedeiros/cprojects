if (pn2->pn_type != TOK_NAME &&
#if JS_HAS_DESTRUCTURING
            pn2->pn_type != TOK_RB &&
            pn2->pn_type != TOK_RC &&
#endif
            js_NewSrcNote2(cx, cg, SrcNoteForPropOp(pn2, pn2->pn_op),
                           CG_OFFSET(cg) - top) < 0) {
            return JS_FALSE;
        }
