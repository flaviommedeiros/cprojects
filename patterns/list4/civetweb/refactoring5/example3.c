#ifdef DUK_USE_JX
if (DUK_LIKELY(js_ctx->flag_ext_custom)) {
			tmp = DUK__MKESC(8, DUK_ASC_BACKSLASH, DUK_ASC_UC_U);
		} else
#endif
		{
			/* In compatible mode and standard JSON mode, output
			 * something useful for non-BMP characters.  This won't
			 * roundtrip but will still be more or less readable and
			 * more useful than an error.
			 */
			tmp = DUK__MKESC(8, DUK_ASC_UC_U, DUK_ASC_PLUS);
		}
