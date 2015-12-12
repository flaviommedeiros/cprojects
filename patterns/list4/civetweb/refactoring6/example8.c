if (!duk_unicode_is_identifier_part(x)
#if defined(DUK_USE_NONSTD_REGEXP_DOLLAR_ESCAPE)
			           || x == '$'
#endif
			          ) {
				/* IdentityEscape */
				ch = x;
			} else {
				DUK_ERROR(lex_ctx->thr, DUK_ERR_SYNTAX_ERROR,
				          "invalid regexp escape");
			}
