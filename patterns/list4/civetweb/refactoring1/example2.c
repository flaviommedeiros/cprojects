if (x == '0' && (y == 'x' || y == 'X')) {
			DUK__APPENDBUFFER(lex_ctx, x);
			DUK__APPENDBUFFER(lex_ctx, y);
			DUK__ADVANCECHARS(lex_ctx, 2);
			int_only = 1;
			allow_hex = 1;
#ifdef DUK_USE_OCTAL_SUPPORT
		} else if (!strict_mode && x == '0' && DUK__ISDIGIT(y)) {
			/* Note: if DecimalLiteral starts with a '0', it can only be
			 * followed by a period or an exponent indicator which starts
			 * with 'e' or 'E'.  Hence the if-check above ensures that
			 * OctalIntegerLiteral is the only valid NumericLiteral
			 * alternative at this point (even if y is, say, '9').
			 */

			DUK__APPENDBUFFER(lex_ctx, x);
			DUK__ADVANCECHARS(lex_ctx, 1);
			int_only = 1;
#endif
		}
#endif
