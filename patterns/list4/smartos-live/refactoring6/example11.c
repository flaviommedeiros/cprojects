if ((
#if JS_HAS_BLOCK_SCOPE
                     type == TOK_LET ||
#endif
                     !pn3->pn_expr) &&
                    js_NewSrcNote2(cx, cg, SRC_DECL,
                                   type == TOK_VAR
                                   ? SRC_DECL_VAR
                                   : SRC_DECL_LET) < 0) {
                    return JS_FALSE;
                }
