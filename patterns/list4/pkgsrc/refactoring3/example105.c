switch (c = token(cf|KEYWORD|ALIAS|VARASN)) {
	  default:
		REJECT;
		afree((void*) iops, ATEMP);
		XPfree(args);
		XPfree(vars);
		return NULL; /* empty line */

	  case LWORD:
	  case REDIR:
		REJECT;
		syniocf &= ~(KEYWORD|ALIAS);
		t = newtp(TCOM);
		t->lineno = source->line;
		while (1) {
			cf = (t->u.evalflags ? ARRAYVAR : 0)
			     | (XPsize(args) == 0 ? ALIAS|VARASN : CMDWORD);
			switch (tpeek(cf)) {
			  case REDIR:
				if (iopn >= NUFILE)
					yyerror("too many redirections\n");
				iops[iopn++] = synio(cf);
				break;

			  case LWORD:
				ACCEPT;
				/* the iopn == 0 and XPsize(vars) == 0 are
				 * dubious but at&t ksh acts this way
				 */
				if (iopn == 0 && XPsize(vars) == 0
				    && XPsize(args) == 0
				    && assign_command(ident))
					t->u.evalflags = DOVACHECK;
				if ((XPsize(args) == 0 || Flag(FKEYWORD))
				    && is_wdvarassign(yylval.cp))
					XPput(vars, yylval.cp);
				else
					XPput(args, yylval.cp);
				break;

			  case '(':
				/* Check for "> foo (echo hi)", which at&t ksh
				 * allows (not POSIX, but not disallowed)
				 */
				afree(t, ATEMP);
				if (XPsize(args) == 0 && XPsize(vars) == 0) {
					ACCEPT;
					goto Subshell;
				}
				/* Must be a function */
				if (iopn != 0 || XPsize(args) != 1
				    || XPsize(vars) != 0)
					syntaxerr((char *) 0);
				ACCEPT;
				/*(*/
				musthave(')', 0);
				t = function_body(XPptrv(args)[0], FALSE);
				goto Leave;

			  default:
				goto Leave;
			}
		}
	  Leave:
		break;

	  Subshell:
	  case '(':
		t = nested(TPAREN, '(', ')');
		break;

	  case '{': /*}*/
		t = nested(TBRACE, '{', '}');
		break;

#ifdef KSH
	  case MDPAREN:
	  {
		static const char let_cmd[] = { CHAR, 'l', CHAR, 'e',
						CHAR, 't', EOS };
		/* Leave KEYWORD in syniocf (allow if (( 1 )) then ...) */
		t = newtp(TCOM);
		t->lineno = source->line;
		ACCEPT;
		XPput(args, wdcopy(let_cmd, ATEMP));
		musthave(LWORD,LETEXPR);
		XPput(args, yylval.cp);
		break;
	  }
#endif /* KSH */

#ifdef KSH
	  case DBRACKET: /* [[ .. ]] */
		/* Leave KEYWORD in syniocf (allow if [[ -n 1 ]] then ...) */
		t = newtp(TDBRACKET);
		ACCEPT;
		{
			Test_env te;

			te.flags = TEF_DBRACKET;
			te.pos.av = &args;
			te.isa = dbtestp_isa;
			te.getopnd = dbtestp_getopnd;
			te.eval = dbtestp_eval;
			te.error = dbtestp_error;

			test_parse(&te);
		}
		break;
#endif /* KSH */

	  case FOR:
	  case SELECT:
		t = newtp((c == FOR) ? TFOR : TSELECT);
		musthave(LWORD, ARRAYVAR);
		if (!is_wdvarname(yylval.cp, TRUE))
			yyerror("%s: bad identifier\n",
				c == FOR ? "for" : "select");
		t->str = str_save(ident, ATEMP);
		nesting_push(&old_nesting, c);
		t->vars = wordlist();
		t->left = dogroup();
		nesting_pop(&old_nesting);
		break;

	  case WHILE:
	  case UNTIL:
		nesting_push(&old_nesting, c);
		t = newtp((c == WHILE) ? TWHILE : TUNTIL);
		t->left = c_list(TRUE);
		t->right = dogroup();
		nesting_pop(&old_nesting);
		break;

	  case CASE:
		t = newtp(TCASE);
		musthave(LWORD, 0);
		t->str = yylval.cp;
		nesting_push(&old_nesting, c);
		t->left = caselist();
		nesting_pop(&old_nesting);
		break;

	  case IF:
		nesting_push(&old_nesting, c);
		t = newtp(TIF);
		t->left = c_list(TRUE);
		t->right = thenpart();
		musthave(FI, KEYWORD|ALIAS);
		nesting_pop(&old_nesting);
		break;

	  case BANG:
		syniocf &= ~(KEYWORD|ALIAS);
		t = pipeline(0);
		if (t == (struct op *) 0)
			syntaxerr((char *) 0);
		t = block(TBANG, NOBLOCK, t, NOWORDS);
		break;

	  case TIME:
		syniocf &= ~(KEYWORD|ALIAS);
		t = pipeline(0);
		t = block(TTIME, t, NOBLOCK, NOWORDS);
		break;

	  case FUNCTION:
		musthave(LWORD, 0);
		t = function_body(yylval.cp, TRUE);
		break;
	}
