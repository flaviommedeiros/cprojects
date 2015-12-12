switch ((modifier = *tstr)) {
	case ':':
	    {
		if (tstr[1] == '=' ||
		    (tstr[2] == '=' &&
		     (tstr[1] == '!' || tstr[1] == '+' || tstr[1] == '?'))) {
		    /*
		     * "::=", "::!=", "::+=", or "::?="
		     */
		    GNode *v_ctxt;		/* context where v belongs */
		    const char *emsg;
		    char *sv_name;
		    VarPattern	pattern;
		    int	how;

		    if (v->name[0] == 0)
			goto bad_modifier;

		    v_ctxt = ctxt;
		    sv_name = NULL;
		    ++tstr;
		    if (v->flags & VAR_JUNK) {
			/*
			 * We need to bmake_strdup() it incase
			 * VarGetPattern() recurses.
			 */
			sv_name = v->name;
			v->name = bmake_strdup(v->name);
		    } else if (ctxt != VAR_GLOBAL) {
			Var *gv = VarFind(v->name, ctxt, 0);
			if (gv == NULL)
			    v_ctxt = VAR_GLOBAL;
			else
			    VarFreeEnv(gv, TRUE);
		    }

		    switch ((how = *tstr)) {
		    case '+':
		    case '?':
		    case '!':
			cp = &tstr[2];
			break;
		    default:
			cp = ++tstr;
			break;
		    }
		    delim = startc == PROPEN ? PRCLOSE : BRCLOSE;
		    pattern.flags = 0;

		    pattern.rhs = VarGetPattern(ctxt, &parsestate, errnum,
						&cp, delim, NULL,
						&pattern.rightLen,
						NULL);
		    if (v->flags & VAR_JUNK) {
			/* restore original name */
			free(v->name);
			v->name = sv_name;
		    }
		    if (pattern.rhs == NULL)
			goto cleanup;

		    termc = *--cp;
		    delim = '\0';

		    switch (how) {
		    case '+':
			Var_Append(v->name, pattern.rhs, v_ctxt);
			break;
		    case '!':
			newStr = Cmd_Exec(pattern.rhs, &emsg);
			if (emsg)
			    Error(emsg, nstr);
			else
			    Var_Set(v->name, newStr,  v_ctxt, 0);
			if (newStr)
			    free(newStr);
			break;
		    case '?':
			if ((v->flags & VAR_JUNK) == 0)
			    break;
			/* FALLTHROUGH */
		    default:
			Var_Set(v->name, pattern.rhs, v_ctxt, 0);
			break;
		    }
		    free(UNCONST(pattern.rhs));
		    newStr = varNoError;
		    break;
		}
		goto default_case; /* "::<unrecognised>" */
	    }
	case '@':
	    {
		VarLoop_t	loop;
		int flags = VAR_NOSUBST;

		cp = ++tstr;
		delim = '@';
		if ((loop.tvar = VarGetPattern(ctxt, &parsestate, errnum,
					       &cp, delim,
					       &flags, &loop.tvarLen,
					       NULL)) == NULL)
		    goto cleanup;

		if ((loop.str = VarGetPattern(ctxt, &parsestate, errnum,
					      &cp, delim,
					      &flags, &loop.strLen,
					      NULL)) == NULL)
		    goto cleanup;

		termc = *cp;
		delim = '\0';

		loop.errnum = errnum;
		loop.ctxt = ctxt;
		newStr = VarModify(ctxt, &parsestate, nstr, VarLoopExpand,
				   &loop);
		free(loop.tvar);
		free(loop.str);
		break;
	    }
	case 'D':
	case 'U':
	    {
		Buffer  buf;    	/* Buffer for patterns */
		int	    wantit;	/* want data in buffer */

		/*
		 * Pass through tstr looking for 1) escaped delimiters,
		 * '$'s and backslashes (place the escaped character in
		 * uninterpreted) and 2) unescaped $'s that aren't before
		 * the delimiter (expand the variable substitution).
		 * The result is left in the Buffer buf.
		 */
		Buf_Init(&buf, 0);
		for (cp = tstr + 1;
		     *cp != endc && *cp != ':' && *cp != '\0';
		     cp++) {
		    if ((*cp == '\\') &&
			((cp[1] == ':') ||
			 (cp[1] == '$') ||
			 (cp[1] == endc) ||
			 (cp[1] == '\\')))
			{
			    Buf_AddByte(&buf, cp[1]);
			    cp++;
			} else if (*cp == '$') {
			    /*
			     * If unescaped dollar sign, assume it's a
			     * variable substitution and recurse.
			     */
			    char    *cp2;
			    int	    len;
			    void    *freeIt;

			    cp2 = Var_Parse(cp, ctxt, errnum, &len, &freeIt);
			    Buf_AddBytes(&buf, strlen(cp2), cp2);
			    if (freeIt)
				free(freeIt);
			    cp += len - 1;
			} else {
			    Buf_AddByte(&buf, *cp);
			}
		}

		termc = *cp;

		if (*tstr == 'U')
		    wantit = ((v->flags & VAR_JUNK) != 0);
		else
		    wantit = ((v->flags & VAR_JUNK) == 0);
		if ((v->flags & VAR_JUNK) != 0)
		    v->flags |= VAR_KEEP;
		if (wantit) {
		    newStr = Buf_Destroy(&buf, FALSE);
		} else {
		    newStr = nstr;
		    Buf_Destroy(&buf, TRUE);
		}
		break;
	    }
	case 'L':
	    {
		if ((v->flags & VAR_JUNK) != 0)
		    v->flags |= VAR_KEEP;
		newStr = bmake_strdup(v->name);
		cp = ++tstr;
		termc = *tstr;
		break;
	    }
	case 'P':
	    {
		GNode *gn;

		if ((v->flags & VAR_JUNK) != 0)
		    v->flags |= VAR_KEEP;
		gn = Targ_FindNode(v->name, TARG_NOCREATE);
		if (gn == NULL || gn->type & OP_NOPATH) {
		    newStr = NULL;
		} else if (gn->path) {
		    newStr = bmake_strdup(gn->path);
		} else {
		    newStr = Dir_FindFile(v->name, Suff_FindPath(gn));
		}
		if (!newStr) {
		    newStr = bmake_strdup(v->name);
		}
		cp = ++tstr;
		termc = *tstr;
		break;
	    }
	case '!':
	    {
		const char *emsg;
		VarPattern 	    pattern;
		pattern.flags = 0;

		delim = '!';

		cp = ++tstr;
		if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, errnum,
						 &cp, delim,
						 NULL, &pattern.rightLen,
						 NULL)) == NULL)
		    goto cleanup;
		newStr = Cmd_Exec(pattern.rhs, &emsg);
		free(UNCONST(pattern.rhs));
		if (emsg)
		    Error(emsg, nstr);
		termc = *cp;
		delim = '\0';
		if (v->flags & VAR_JUNK) {
		    v->flags |= VAR_KEEP;
		}
		break;
	    }
	case '[':
	    {
		/*
		 * Look for the closing ']', recursively
		 * expanding any embedded variables.
		 *
		 * estr is a pointer to the expanded result,
		 * which we must free().
		 */
		char *estr;

		cp = tstr+1; /* point to char after '[' */
		delim = ']'; /* look for closing ']' */
		estr = VarGetPattern(ctxt, &parsestate,
				     errnum, &cp, delim,
				     NULL, NULL, NULL);
		if (estr == NULL)
		    goto cleanup; /* report missing ']' */
		/* now cp points just after the closing ']' */
		delim = '\0';
		if (cp[0] != ':' && cp[0] != endc) {
		    /* Found junk after ']' */
		    free(estr);
		    goto bad_modifier;
		}
		if (estr[0] == '\0') {
		    /* Found empty square brackets in ":[]". */
		    free(estr);
		    goto bad_modifier;
		} else if (estr[0] == '#' && estr[1] == '\0') {
		    /* Found ":[#]" */

		    /*
		     * We will need enough space for the decimal
		     * representation of an int.  We calculate the
		     * space needed for the octal representation,
		     * and add enough slop to cope with a '-' sign
		     * (which should never be needed) and a '\0'
		     * string terminator.
		     */
		    int newStrSize =
			(sizeof(int) * CHAR_BIT + 2) / 3 + 2;

		    newStr = bmake_malloc(newStrSize);
		    if (parsestate.oneBigWord) {
			strncpy(newStr, "1", newStrSize);
		    } else {
			/* XXX: brk_string() is a rather expensive
			 * way of counting words. */
			char **av;
			char *as;
			int ac;

			av = brk_string(nstr, &ac, FALSE, &as);
			snprintf(newStr, newStrSize,  "%d", ac);
			free(as);
			free(av);
		    }
		    termc = *cp;
		    free(estr);
		    break;
		} else if (estr[0] == '*' && estr[1] == '\0') {
		    /* Found ":[*]" */
		    parsestate.oneBigWord = TRUE;
		    newStr = nstr;
		    termc = *cp;
		    free(estr);
		    break;
		} else if (estr[0] == '@' && estr[1] == '\0') {
		    /* Found ":[@]" */
		    parsestate.oneBigWord = FALSE;
		    newStr = nstr;
		    termc = *cp;
		    free(estr);
		    break;
		} else {
		    /*
		     * We expect estr to contain a single
		     * integer for :[N], or two integers
		     * separated by ".." for :[start..end].
		     */
		    char *ep;

		    VarSelectWords_t seldata = { 0, 0 };

		    seldata.start = strtol(estr, &ep, 0);
		    if (ep == estr) {
			/* Found junk instead of a number */
			free(estr);
			goto bad_modifier;
		    } else if (ep[0] == '\0') {
			/* Found only one integer in :[N] */
			seldata.end = seldata.start;
		    } else if (ep[0] == '.' && ep[1] == '.' &&
			       ep[2] != '\0') {
			/* Expecting another integer after ".." */
			ep += 2;
			seldata.end = strtol(ep, &ep, 0);
			if (ep[0] != '\0') {
			    /* Found junk after ".." */
			    free(estr);
			    goto bad_modifier;
			}
		    } else {
			/* Found junk instead of ".." */
			free(estr);
			goto bad_modifier;
		    }
		    /*
		     * Now seldata is properly filled in,
		     * but we still have to check for 0 as
		     * a special case.
		     */
		    if (seldata.start == 0 && seldata.end == 0) {
			/* ":[0]" or perhaps ":[0..0]" */
			parsestate.oneBigWord = TRUE;
			newStr = nstr;
			termc = *cp;
			free(estr);
			break;
		    } else if (seldata.start == 0 ||
			       seldata.end == 0) {
			/* ":[0..N]" or ":[N..0]" */
			free(estr);
			goto bad_modifier;
		    }
		    /*
		     * Normal case: select the words
		     * described by seldata.
		     */
		    newStr = VarSelectWords(ctxt, &parsestate,
					    nstr, &seldata);

		    termc = *cp;
		    free(estr);
		    break;
		}

	    }
	case 'g':
	    cp = tstr + 1;	/* make sure it is set */
	    if (STRMOD_MATCH(tstr, "gmtime", 6)) {
		newStr = VarStrftime(nstr, 1);
		cp = tstr + 6;
		termc = *cp;
	    } else {
		goto default_case;
	    }
	    break;
	case 'h':
	    cp = tstr + 1;	/* make sure it is set */
	    if (STRMOD_MATCH(tstr, "hash", 4)) {
		newStr = VarHash(nstr);
		cp = tstr + 4;
		termc = *cp;
	    } else {
		goto default_case;
	    }
	    break;
	case 'l':
	    cp = tstr + 1;	/* make sure it is set */
	    if (STRMOD_MATCH(tstr, "localtime", 9)) {
		newStr = VarStrftime(nstr, 0);
		cp = tstr + 9;
		termc = *cp;
	    } else {
		goto default_case;
	    }
	    break;
	case 't':
	    {
		cp = tstr + 1;	/* make sure it is set */
		if (tstr[1] != endc && tstr[1] != ':') {
		    if (tstr[1] == 's') {
			/*
			 * Use the char (if any) at tstr[2]
			 * as the word separator.
			 */
			VarPattern pattern;

			if (tstr[2] != endc &&
			    (tstr[3] == endc || tstr[3] == ':')) {
			    /* ":ts<unrecognised><endc>" or
			     * ":ts<unrecognised>:" */
			    parsestate.varSpace = tstr[2];
			    cp = tstr + 3;
			} else if (tstr[2] == endc || tstr[2] == ':') {
			    /* ":ts<endc>" or ":ts:" */
			    parsestate.varSpace = 0; /* no separator */
			    cp = tstr + 2;
			} else if (tstr[2] == '\\') {
			    switch (tstr[3]) {
			    case 'n':
				parsestate.varSpace = '\n';
				cp = tstr + 4;
				break;
			    case 't':
				parsestate.varSpace = '\t';
				cp = tstr + 4;
				break;
			    default:
				if (isdigit((unsigned char)tstr[3])) {
				    char *ep;

				    parsestate.varSpace =
					strtoul(&tstr[3], &ep, 0);
				    if (*ep != ':' && *ep != endc)
					goto bad_modifier;
				    cp = ep;
				} else {
				    /*
				     * ":ts<backslash><unrecognised>".
				     */
				    goto bad_modifier;
				}
				break;
			    }
			} else {
			    /*
			     * Found ":ts<unrecognised><unrecognised>".
			     */
			    goto bad_modifier;
			}

			termc = *cp;

			/*
			 * We cannot be certain that VarModify
			 * will be used - even if there is a
			 * subsequent modifier, so do a no-op
			 * VarSubstitute now to for str to be
			 * re-expanded without the spaces.
			 */
			pattern.flags = VAR_SUB_ONE;
			pattern.lhs = pattern.rhs = "\032";
			pattern.leftLen = pattern.rightLen = 1;

			newStr = VarModify(ctxt, &parsestate, nstr,
					   VarSubstitute,
					   &pattern);
		    } else if (tstr[2] == endc || tstr[2] == ':') {
			/*
			 * Check for two-character options:
			 * ":tu", ":tl"
			 */
			if (tstr[1] == 'A') { /* absolute path */
			    newStr = VarModify(ctxt, &parsestate, nstr,
					       VarRealpath, NULL);
			    cp = tstr + 2;
			    termc = *cp;
			} else if (tstr[1] == 'u') {
			    char *dp = bmake_strdup(nstr);
			    for (newStr = dp; *dp; dp++)
				*dp = toupper((unsigned char)*dp);
			    cp = tstr + 2;
			    termc = *cp;
			} else if (tstr[1] == 'l') {
			    char *dp = bmake_strdup(nstr);
			    for (newStr = dp; *dp; dp++)
				*dp = tolower((unsigned char)*dp);
			    cp = tstr + 2;
			    termc = *cp;
			} else if (tstr[1] == 'W' || tstr[1] == 'w') {
			    parsestate.oneBigWord = (tstr[1] == 'W');
			    newStr = nstr;
			    cp = tstr + 2;
			    termc = *cp;
			} else {
			    /* Found ":t<unrecognised>:" or
			     * ":t<unrecognised><endc>". */
			    goto bad_modifier;
			}
		    } else {
			/*
			 * Found ":t<unrecognised><unrecognised>".
			 */
			goto bad_modifier;
		    }
		} else {
		    /*
		     * Found ":t<endc>" or ":t:".
		     */
		    goto bad_modifier;
		}
		break;
	    }
	case 'N':
	case 'M':
	    {
		char    *pattern;
		const char *endpat; /* points just after end of pattern */
		char    *cp2;
		Boolean copy;	/* pattern should be, or has been, copied */
		Boolean needSubst;
		int nest;

		copy = FALSE;
		needSubst = FALSE;
		nest = 1;
		/*
		 * In the loop below, ignore ':' unless we are at
		 * (or back to) the original brace level.
		 * XXX This will likely not work right if $() and ${}
		 * are intermixed.
		 */
		for (cp = tstr + 1;
		     *cp != '\0' && !(*cp == ':' && nest == 1);
		     cp++)
		    {
			if (*cp == '\\' &&
			    (cp[1] == ':' ||
			     cp[1] == endc || cp[1] == startc)) {
			    if (!needSubst) {
				copy = TRUE;
			    }
			    cp++;
			    continue;
			}
			if (*cp == '$') {
			    needSubst = TRUE;
			}
			if (*cp == '(' || *cp == '{')
			    ++nest;
			if (*cp == ')' || *cp == '}') {
			    --nest;
			    if (nest == 0)
				break;
			}
		    }
		termc = *cp;
		endpat = cp;
		if (copy) {
		    /*
		     * Need to compress the \:'s out of the pattern, so
		     * allocate enough room to hold the uncompressed
		     * pattern (note that cp started at tstr+1, so
		     * cp - tstr takes the null byte into account) and
		     * compress the pattern into the space.
		     */
		    pattern = bmake_malloc(cp - tstr);
		    for (cp2 = pattern, cp = tstr + 1;
			 cp < endpat;
			 cp++, cp2++)
			{
			    if ((*cp == '\\') && (cp+1 < endpat) &&
				(cp[1] == ':' || cp[1] == endc)) {
				cp++;
			    }
			    *cp2 = *cp;
			}
		    *cp2 = '\0';
		    endpat = cp2;
		} else {
		    /*
		     * Either Var_Subst or VarModify will need a
		     * nul-terminated string soon, so construct one now.
		     */
		    pattern = bmake_strndup(tstr+1, endpat - (tstr + 1));
		}
		if (needSubst) {
		    /*
		     * pattern contains embedded '$', so use Var_Subst to
		     * expand it.
		     */
		    cp2 = pattern;
		    pattern = Var_Subst(NULL, cp2, ctxt, errnum);
		    free(cp2);
		}
		if (DEBUG(VAR))
		    fprintf(debug_file, "Pattern[%s] for [%s] is [%s]\n",
			v->name, nstr, pattern);
		if (*tstr == 'M') {
		    newStr = VarModify(ctxt, &parsestate, nstr, VarMatch,
				       pattern);
		} else {
		    newStr = VarModify(ctxt, &parsestate, nstr, VarNoMatch,
				       pattern);
		}
		free(pattern);
		break;
	    }
	case 'S':
	    {
		VarPattern 	    pattern;
		Var_Parse_State tmpparsestate;

		pattern.flags = 0;
		tmpparsestate = parsestate;
		delim = tstr[1];
		tstr += 2;

		/*
		 * If pattern begins with '^', it is anchored to the
		 * start of the word -- skip over it and flag pattern.
		 */
		if (*tstr == '^') {
		    pattern.flags |= VAR_MATCH_START;
		    tstr += 1;
		}

		cp = tstr;
		if ((pattern.lhs = VarGetPattern(ctxt, &parsestate, errnum,
						 &cp, delim,
						 &pattern.flags,
						 &pattern.leftLen,
						 NULL)) == NULL)
		    goto cleanup;

		if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, errnum,
						 &cp, delim, NULL,
						 &pattern.rightLen,
						 &pattern)) == NULL)
		    goto cleanup;

		/*
		 * Check for global substitution. If 'g' after the final
		 * delimiter, substitution is global and is marked that
		 * way.
		 */
		for (;; cp++) {
		    switch (*cp) {
		    case 'g':
			pattern.flags |= VAR_SUB_GLOBAL;
			continue;
		    case '1':
			pattern.flags |= VAR_SUB_ONE;
			continue;
		    case 'W':
			tmpparsestate.oneBigWord = TRUE;
			continue;
		    }
		    break;
		}

		termc = *cp;
		newStr = VarModify(ctxt, &tmpparsestate, nstr,
				   VarSubstitute,
				   &pattern);

		/*
		 * Free the two strings.
		 */
		free(UNCONST(pattern.lhs));
		free(UNCONST(pattern.rhs));
		delim = '\0';
		break;
	    }
	case '?':
	    {
		VarPattern 	pattern;
		Boolean	value;

		/* find ':', and then substitute accordingly */

		pattern.flags = 0;

		cp = ++tstr;
		delim = ':';
		if ((pattern.lhs = VarGetPattern(ctxt, &parsestate, errnum,
						 &cp, delim, NULL,
						 &pattern.leftLen,
						 NULL)) == NULL)
		    goto cleanup;

		/* BROPEN or PROPEN */
		delim = endc;
		if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, errnum,
						 &cp, delim, NULL,
						 &pattern.rightLen,
						 NULL)) == NULL)
		    goto cleanup;

		termc = *--cp;
		delim = '\0';
		if (Cond_EvalExpression(NULL, v->name, &value, 0, FALSE)
		    == COND_INVALID) {
		    Error("Bad conditional expression `%s' in %s?%s:%s",
			  v->name, v->name, pattern.lhs, pattern.rhs);
		    goto cleanup;
		}

		if (value) {
		    newStr = UNCONST(pattern.lhs);
		    free(UNCONST(pattern.rhs));
		} else {
		    newStr = UNCONST(pattern.rhs);
		    free(UNCONST(pattern.lhs));
		}
		if (v->flags & VAR_JUNK) {
		    v->flags |= VAR_KEEP;
		}
		break;
	    }
#ifndef NO_REGEX
	case 'C':
	    {
		VarREPattern    pattern;
		char           *re;
		int             error;
		Var_Parse_State tmpparsestate;

		pattern.flags = 0;
		tmpparsestate = parsestate;
		delim = tstr[1];
		tstr += 2;

		cp = tstr;

		if ((re = VarGetPattern(ctxt, &parsestate, errnum, &cp, delim,
					NULL, NULL, NULL)) == NULL)
		    goto cleanup;

		if ((pattern.replace = VarGetPattern(ctxt, &parsestate,
						     errnum, &cp, delim, NULL,
						     NULL, NULL)) == NULL){
		    free(re);
		    goto cleanup;
		}

		for (;; cp++) {
		    switch (*cp) {
		    case 'g':
			pattern.flags |= VAR_SUB_GLOBAL;
			continue;
		    case '1':
			pattern.flags |= VAR_SUB_ONE;
			continue;
		    case 'W':
			tmpparsestate.oneBigWord = TRUE;
			continue;
		    }
		    break;
		}

		termc = *cp;

		error = regcomp(&pattern.re, re, REG_EXTENDED);
		free(re);
		if (error)  {
		    *lengthPtr = cp - start + 1;
		    VarREError(error, &pattern.re, "RE substitution error");
		    free(pattern.replace);
		    goto cleanup;
		}

		pattern.nsub = pattern.re.re_nsub + 1;
		if (pattern.nsub < 1)
		    pattern.nsub = 1;
		if (pattern.nsub > 10)
		    pattern.nsub = 10;
		pattern.matches = bmake_malloc(pattern.nsub *
					  sizeof(regmatch_t));
		newStr = VarModify(ctxt, &tmpparsestate, nstr,
				   VarRESubstitute,
				   &pattern);
		regfree(&pattern.re);
		free(pattern.replace);
		free(pattern.matches);
		delim = '\0';
		break;
	    }
#endif
	case 'Q':
	    if (tstr[1] == endc || tstr[1] == ':') {
		newStr = VarQuote(nstr);
		cp = tstr + 1;
		termc = *cp;
		break;
	    }
	    goto default_case;
	case 'T':
	    if (tstr[1] == endc || tstr[1] == ':') {
		newStr = VarModify(ctxt, &parsestate, nstr, VarTail,
				   NULL);
		cp = tstr + 1;
		termc = *cp;
		break;
	    }
	    goto default_case;
	case 'H':
	    if (tstr[1] == endc || tstr[1] == ':') {
		newStr = VarModify(ctxt, &parsestate, nstr, VarHead,
				   NULL);
		cp = tstr + 1;
		termc = *cp;
		break;
	    }
	    goto default_case;
	case 'E':
	    if (tstr[1] == endc || tstr[1] == ':') {
		newStr = VarModify(ctxt, &parsestate, nstr, VarSuffix,
				   NULL);
		cp = tstr + 1;
		termc = *cp;
		break;
	    }
	    goto default_case;
	case 'R':
	    if (tstr[1] == endc || tstr[1] == ':') {
		newStr = VarModify(ctxt, &parsestate, nstr, VarRoot,
				   NULL);
		cp = tstr + 1;
		termc = *cp;
		break;
	    }
	    goto default_case;
	case 'O':
	    {
		char otype;

		cp = tstr + 1;	/* skip to the rest in any case */
		if (tstr[1] == endc || tstr[1] == ':') {
		    otype = 's';
		    termc = *cp;
		} else if ( (tstr[1] == 'x') &&
			    (tstr[2] == endc || tstr[2] == ':') ) {
		    otype = tstr[1];
		    cp = tstr + 2;
		    termc = *cp;
		} else {
		    goto bad_modifier;
		}
		newStr = VarOrder(nstr, otype);
		break;
	    }
	case 'u':
	    if (tstr[1] == endc || tstr[1] == ':') {
		newStr = VarUniq(nstr);
		cp = tstr + 1;
		termc = *cp;
		break;
	    }
	    goto default_case;
#ifdef SUNSHCMD
	case 's':
	    if (tstr[1] == 'h' && (tstr[2] == endc || tstr[2] == ':')) {
		const char *emsg;
		newStr = Cmd_Exec(nstr, &emsg);
		if (emsg)
		    Error(emsg, nstr);
		cp = tstr + 2;
		termc = *cp;
		break;
	    }
	    goto default_case;
#endif
	default:
	default_case:
	{
#ifdef SYSVVARSUB
	    /*
	     * This can either be a bogus modifier or a System-V
	     * substitution command.
	     */
	    VarPattern      pattern;
	    Boolean         eqFound;

	    pattern.flags = 0;
	    eqFound = FALSE;
	    /*
	     * First we make a pass through the string trying
	     * to verify it is a SYSV-make-style translation:
	     * it must be: <string1>=<string2>)
	     */
	    cp = tstr;
	    cnt = 1;
	    while (*cp != '\0' && cnt) {
		if (*cp == '=') {
		    eqFound = TRUE;
		    /* continue looking for endc */
		}
		else if (*cp == endc)
		    cnt--;
		else if (*cp == startc)
		    cnt++;
		if (cnt)
		    cp++;
	    }
	    if (*cp == endc && eqFound) {

		/*
		 * Now we break this sucker into the lhs and
		 * rhs. We must null terminate them of course.
		 */
		delim='=';
		cp = tstr;
		if ((pattern.lhs = VarGetPattern(ctxt, &parsestate,
						 errnum, &cp, delim, &pattern.flags,
						 &pattern.leftLen, NULL)) == NULL)
		    goto cleanup;
		delim = endc;
		if ((pattern.rhs = VarGetPattern(ctxt, &parsestate,
						 errnum, &cp, delim, NULL, &pattern.rightLen,
						 &pattern)) == NULL)
		    goto cleanup;

		/*
		 * SYSV modifications happen through the whole
		 * string. Note the pattern is anchored at the end.
		 */
		termc = *--cp;
		delim = '\0';
		if (pattern.leftLen == 0 && *nstr == '\0') {
		    newStr = nstr;	/* special case */
		} else {
		    newStr = VarModify(ctxt, &parsestate, nstr,
				       VarSYSVMatch,
				       &pattern);
		}
		free(UNCONST(pattern.lhs));
		free(UNCONST(pattern.rhs));
	    } else
#endif
		{
		    Error("Unknown modifier '%c'", *tstr);
		    for (cp = tstr+1;
			 *cp != ':' && *cp != endc && *cp != '\0';
			 cp++)
			continue;
		    termc = *cp;
		    newStr = var_Error;
		}
	    }
	}
