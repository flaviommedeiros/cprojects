if (end_trigger && end_trigger == ch
		 && (ch != ';' || heredoc_cnt == 0)
#if ENABLE_HUSH_CASE
		 && (ch != ')'
		    || ctx.ctx_res_w != RES_MATCH
		    || (!dest.has_quoted_part && strcmp(dest.data, "esac") == 0)
		    )
#endif
		) {
			if (heredoc_cnt) {
				/* This is technically valid:
				 * { cat <<HERE; }; echo Ok
				 * heredoc
				 * heredoc
				 * HERE
				 * but we don't support this.
				 * We require heredoc to be in enclosing {}/(),
				 * if any.
				 */
				syntax_error_unterm_str("here document");
				goto parse_error;
			}
			if (done_word(&dest, &ctx)) {
				goto parse_error;
			}
			done_pipe(&ctx, PIPE_SEQ);
			dest.o_assignment = MAYBE_ASSIGNMENT;
			debug_printf_parse("dest.o_assignment='%s'\n", assignment_flag[dest.o_assignment]);
			/* Do we sit outside of any if's, loops or case's? */
			if (!HAS_KEYWORDS
			 IF_HAS_KEYWORDS(|| (ctx.ctx_res_w == RES_NONE && ctx.old_flag == 0))
			) {
				o_free(&dest);
#if !BB_MMU
				debug_printf_parse("as_string '%s'\n", ctx.as_string.data);
				if (pstring)
					*pstring = ctx.as_string.data;
				else
					o_free_unsafe(&ctx.as_string);
#endif
				debug_leave();
				debug_printf_parse("parse_stream return %p: "
						"end_trigger char found\n",
						ctx.list_head);
				return ctx.list_head;
			}
		}
