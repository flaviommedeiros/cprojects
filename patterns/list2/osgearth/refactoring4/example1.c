#if defined(DUK_USE_NONSTD_FUNC_STMT)
if (allow_source_elem || !comp_ctx->curr_func.is_strict)
#else  /* DUK_USE_NONSTD_FUNC_STMT */
		/* Strict: never allow function declarations outside top level. */
		if (allow_source_elem)
#endif  /* DUK_USE_NONSTD_FUNC_STMT */
		{
			/* FunctionDeclaration: not strictly a statement but handled as such.
			 *
		 	 * O(depth^2) parse count for inner functions is handled by recording a
			 * lexer offset on the first compilation pass, so that the function can
			 * be efficiently skipped on the second pass.  This is encapsulated into
			 * duk__parse_func_like_fnum().
			 */

			duk_int_t fnum;

			DUK_DDD(DUK_DDDPRINT("function declaration statement"));

			duk__advance(comp_ctx);  /* eat 'function' */
			fnum = duk__parse_func_like_fnum(comp_ctx, 1 /*is_decl*/, 0 /*is_setget*/);

			if (comp_ctx->curr_func.in_scanning) {
				duk_uarridx_t n;
				duk_hstring *h_funcname;

				duk_get_prop_index(ctx, comp_ctx->curr_func.funcs_idx, fnum * 3);
				duk_get_prop_stridx(ctx, -1, DUK_STRIDX_NAME);  /* -> [ ... func name ] */
				h_funcname = duk_get_hstring(ctx, -1);
				DUK_ASSERT(h_funcname != NULL);

				DUK_DDD(DUK_DDDPRINT("register function declaration %!O in pass 1, fnum %ld",
				                     (duk_heaphdr *) h_funcname, (long) fnum));
				n = (duk_uarridx_t) duk_get_length(ctx, comp_ctx->curr_func.decls_idx);
				duk_push_hstring(ctx, h_funcname);
				duk_put_prop_index(ctx, comp_ctx->curr_func.decls_idx, n);
				duk_push_int(ctx, (duk_int_t) (DUK_DECL_TYPE_FUNC + (fnum << 8)));
				duk_put_prop_index(ctx, comp_ctx->curr_func.decls_idx, n + 1);

				duk_pop_n(ctx, 2);
			}

			/* no statement value (unlike function expression) */
			stmt_flags = 0;
			break;
		} else {
			DUK_ERROR(thr, DUK_ERR_SYNTAX_ERROR, DUK_STR_FUNC_STMT_NOT_ALLOWED);
		}
