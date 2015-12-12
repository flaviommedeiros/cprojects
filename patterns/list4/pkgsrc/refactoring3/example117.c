switch (c) {
				  case '[':
					{
						const char *p = sp;
						bool_t special = FALSE;
						while (*p != EOS) {
							if (p[0] == CHAR &&
								p[1] == ']') {
								special = TRUE;
								break;
							}
								
							p += 2;
						}
						if (!special)
							break;
					}
				  case NOT:
				  case '-':
				  case ']':
					/* For character classes - doesn't hurt
					 * to have magic !,-,]'s outside of
					 * [...] expressions.
					 */
					if (f & (DOPAT | DOGLOB)) {
						fdo |= DOMAGIC_;
						if (c == '[')
							fdo |= f & DOGLOB;
						*dp++ = MAGIC;
					}
					break;
				  case '*':
				  case '?':
					if (f & (DOPAT | DOGLOB)) {
						fdo |= DOMAGIC_ | (f & DOGLOB);
						*dp++ = MAGIC;
					}
					break;
#ifdef BRACE_EXPAND
				  case OBRACE:
				  case ',':
				  case CBRACE:
					if ((f & DOBRACE_) && (c == OBRACE
						|| (fdo & DOBRACE_)))
					{
						fdo |= DOBRACE_|DOMAGIC_;
						*dp++ = MAGIC;
					}
					break;
#endif /* BRACE_EXPAND */
				  case '=':
					/* Note first unquoted = for ~ */
					if (!(f & DOTEMP_) && !saw_eq) {
						saw_eq = 1;
						tilde_ok = 1;
					}
					break;
				  case PATHSEP: /* : */
					/* Note unquoted : for ~ */
					if (!(f & DOTEMP_) && (f & DOASNTILDE))
						tilde_ok = 1;
					break;
				  case '~':
					/* tilde_ok is reset whenever
					 * any of ' " $( $(( ${ } are seen.
					 * Note that tilde_ok must be preserved
					 * through the sequence ${A=a=}~
					 */
					if (type == XBASE
					    && (f & (DOTILDE|DOASNTILDE))
					    && (tilde_ok & 2))
					{
						char *p, *dp_x;

						dp_x = dp;
						p = maybe_expand_tilde(sp,
							&ds, &dp_x,
							f & DOASNTILDE);
						if (p) {
							if (dp != dp_x)
								word = IFS_WORD;
							dp = dp_x;
							sp = p;
							continue;
						}
					}
					break;
				}
