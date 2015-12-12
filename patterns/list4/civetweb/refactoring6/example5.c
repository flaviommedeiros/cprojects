if ((y >= 0 && !duk_unicode_is_identifier_part(y)) ||
#if defined(DUK_USE_NONSTD_REGEXP_DOLLAR_ESCAPE)
		           y == '$' ||
#endif
		           y == DUK_UNICODE_CP_ZWNJ ||
		           y == DUK_UNICODE_CP_ZWJ) {
			/* IdentityEscape, with dollar added as a valid additional
			 * non-standard escape (see test-regexp-identity-escape-dollar.js).
			 * Careful not to match end-of-buffer (<0) here.
			 */
			out_token->num = y;
		} else {
			DUK_ERROR(lex_ctx->thr, DUK_ERR_SYNTAX_ERROR,
			          "invalid regexp escape");
		}
