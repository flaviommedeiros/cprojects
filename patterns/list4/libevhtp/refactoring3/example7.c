switch (tok->type) {
  case TK_ALT:
  case TK_EOT:
  end_of_token:
  *np = node_new_empty();
  return tok->type;
  break;

  case TK_SUBEXP_OPEN:
    r = parse_enclose(np, tok, TK_SUBEXP_CLOSE, src, end, env);
    if (r < 0) return r;
    if (r == 1) group = 1;
    else if (r == 2) { /* option only */
      Node* target;
      OnigOptionType prev = env->option;

      env->option = NENCLOSE(*np)->option;
      r = fetch_token(tok, src, end, env);
      if (r < 0) return r;
      r = parse_subexp(&target, tok, term, src, end, env);
      env->option = prev;
      if (r < 0) return r;
      NENCLOSE(*np)->target = target;	
      return tok->type;
    }
    break;

  case TK_SUBEXP_CLOSE:
    if (! IS_SYNTAX_BV(env->syntax, ONIG_SYN_ALLOW_UNMATCHED_CLOSE_SUBEXP))
      return ONIGERR_UNMATCHED_CLOSE_PARENTHESIS;

    if (tok->escaped) goto tk_raw_byte;
    else goto tk_byte;
    break;

  case TK_STRING:
  tk_byte:
    {
      *np = node_new_str(tok->backp, *src);
      CHECK_NULL_RETURN_MEMERR(*np);

      while (1) {
	r = fetch_token(tok, src, end, env);
	if (r < 0) return r;
	if (r != TK_STRING) break;

	r = onig_node_str_cat(*np, tok->backp, *src);
	if (r < 0) return r;
      }

    string_end:
      targetp = np;
      goto repeat;
    }
    break;

  case TK_RAW_BYTE:
  tk_raw_byte:
    {
      *np = node_new_str_raw_char((UChar )tok->u.c);
      CHECK_NULL_RETURN_MEMERR(*np);
      len = 1;
      while (1) {
	if (len >= ONIGENC_MBC_MINLEN(env->enc)) {
	  if (len == enclen(env->enc, NSTR(*np)->s)) {
	    r = fetch_token(tok, src, end, env);
	    NSTRING_CLEAR_RAW(*np);
	    goto string_end;
	  }
	}

	r = fetch_token(tok, src, end, env);
	if (r < 0) return r;
	if (r != TK_RAW_BYTE) {
	  /* Don't use this, it is wrong for little endian encodings. */
#ifdef USE_PAD_TO_SHORT_BYTE_CHAR
	  int rem;
	  if (len < ONIGENC_MBC_MINLEN(env->enc)) {
	    rem = ONIGENC_MBC_MINLEN(env->enc) - len;
	    (void )node_str_head_pad(NSTR(*np), rem, (UChar )0);
	    if (len + rem == enclen(env->enc, NSTR(*np)->s)) {
	      NSTRING_CLEAR_RAW(*np);
	      goto string_end;
	    }
	  }
#endif
	  return ONIGERR_TOO_SHORT_MULTI_BYTE_STRING;
	}

	r = node_str_cat_char(*np, (UChar )tok->u.c);
	if (r < 0) return r;

	len++;
      }
    }
    break;

  case TK_CODE_POINT:
    {
      UChar buf[ONIGENC_CODE_TO_MBC_MAXLEN];
      int num = ONIGENC_CODE_TO_MBC(env->enc, tok->u.code, buf);
      if (num < 0) return num;
#ifdef NUMBERED_CHAR_IS_NOT_CASE_AMBIG
      *np = node_new_str_raw(buf, buf + num);
#else
      *np = node_new_str(buf, buf + num);
#endif
      CHECK_NULL_RETURN_MEMERR(*np);
    }
    break;

  case TK_QUOTE_OPEN:
    {
      OnigCodePoint end_op[2];
      UChar *qstart, *qend, *nextp;

      end_op[0] = (OnigCodePoint )MC_ESC(env->syntax);
      end_op[1] = (OnigCodePoint )'E';
      qstart = *src;
      qend = find_str_position(end_op, 2, qstart, end, &nextp, env->enc);
      if (IS_NULL(qend)) {
	nextp = qend = end;
      }
      *np = node_new_str(qstart, qend);
      CHECK_NULL_RETURN_MEMERR(*np);
      *src = nextp;
    }
    break;

  case TK_CHAR_TYPE:
    {
      switch (tok->u.prop.ctype) {
      case ONIGENC_CTYPE_WORD:
	*np = node_new_ctype(tok->u.prop.ctype, tok->u.prop.not);
	CHECK_NULL_RETURN_MEMERR(*np);
	break;

      case ONIGENC_CTYPE_SPACE:
      case ONIGENC_CTYPE_DIGIT:
      case ONIGENC_CTYPE_XDIGIT:
	{
	  CClassNode* cc;

#ifdef USE_SHARED_CCLASS_TABLE
          const OnigCodePoint *mbr;
	  OnigCodePoint sb_out;

          r = ONIGENC_GET_CTYPE_CODE_RANGE(env->enc, tok->u.prop.ctype,
					   &sb_out, &mbr);
          if (r == 0 &&
              ONIGENC_CODE_RANGE_NUM(mbr)
              >= THRESHOLD_RANGE_NUM_FOR_SHARE_CCLASS) {
            type_cclass_key  key;
            type_cclass_key* new_key;

            key.enc  = env->enc;
            key.not  = tok->u.prop.not;
            key.type = tok->u.prop.ctype;

            THREAD_ATOMIC_START;

            if (IS_NULL(OnigTypeCClassTable)) {
              OnigTypeCClassTable
                = onig_st_init_table_with_size(&type_type_cclass_hash, 10);
              if (IS_NULL(OnigTypeCClassTable)) {
                THREAD_ATOMIC_END;
                return ONIGERR_MEMORY;
              }
            }
            else {
              if (onig_st_lookup(OnigTypeCClassTable, (st_data_t )&key,
                                 (st_data_t* )np)) {
                THREAD_ATOMIC_END;
                break;
              }
            }

            *np = node_new_cclass_by_codepoint_range(tok->u.prop.not,
						     sb_out, mbr);
            if (IS_NULL(*np)) {
              THREAD_ATOMIC_END;
              return ONIGERR_MEMORY;
            }

            cc = NCCLASS(*np);
            NCCLASS_SET_SHARE(cc);
            new_key = (type_cclass_key* )xmalloc(sizeof(type_cclass_key));
	    xmemcpy(new_key, &key, sizeof(type_cclass_key));
            onig_st_add_direct(OnigTypeCClassTable, (st_data_t )new_key,
                               (st_data_t )*np);
            
            THREAD_ATOMIC_END;
          }
          else {
#endif
            *np = node_new_cclass();
            CHECK_NULL_RETURN_MEMERR(*np);
            cc = NCCLASS(*np);
            add_ctype_to_cc(cc, tok->u.prop.ctype, 0, env);
            if (tok->u.prop.not != 0) NCCLASS_SET_NOT(cc);
#ifdef USE_SHARED_CCLASS_TABLE
          }
#endif
	}
	break;

      default:
	return ONIGERR_PARSER_BUG;
	break;
      }
    }
    break;

  case TK_CHAR_PROPERTY:
    r = parse_char_property(np, tok, src, end, env);
    if (r != 0) return r;
    break;

  case TK_CC_OPEN:
    {
      CClassNode* cc;

      r = parse_char_class(np, tok, src, end, env);
      if (r != 0) return r;

      cc = NCCLASS(*np);
      if (IS_IGNORECASE(env->option)) {
	IApplyCaseFoldArg iarg;

	iarg.env      = env;
	iarg.cc       = cc;
	iarg.alt_root = NULL_NODE;
	iarg.ptail    = &(iarg.alt_root);

	r = ONIGENC_APPLY_ALL_CASE_FOLD(env->enc, env->case_fold_flag,
					i_apply_case_fold, &iarg);
	if (r != 0) {
	  onig_node_free(iarg.alt_root);
	  return r;
	}
	if (IS_NOT_NULL(iarg.alt_root)) {
          Node* work = onig_node_new_alt(*np, iarg.alt_root);
          if (IS_NULL(work)) {
            onig_node_free(iarg.alt_root);
            return ONIGERR_MEMORY;
          }
          *np = work;
	}
      }
    }
    break;

  case TK_ANYCHAR:
    *np = node_new_anychar();
    CHECK_NULL_RETURN_MEMERR(*np);
    break;

  case TK_ANYCHAR_ANYTIME:
    *np = node_new_anychar();
    CHECK_NULL_RETURN_MEMERR(*np);
    qn = node_new_quantifier(0, REPEAT_INFINITE, 0);
    CHECK_NULL_RETURN_MEMERR(qn);
    NQTFR(qn)->target = *np;
    *np = qn;
    break;

  case TK_BACKREF:
    len = tok->u.backref.num;
    *np = node_new_backref(len,
		   (len > 1 ? tok->u.backref.refs : &(tok->u.backref.ref1)),
			   tok->u.backref.by_name,
#ifdef USE_BACKREF_WITH_LEVEL
			   tok->u.backref.exist_level,
			   tok->u.backref.level,
#endif
			   env);
    CHECK_NULL_RETURN_MEMERR(*np);
    break;

#ifdef USE_SUBEXP_CALL
  case TK_CALL:
    {
      int gnum = tok->u.call.gnum;

      if (gnum < 0) {
	gnum = BACKREF_REL_TO_ABS(gnum, env);
	if (gnum <= 0)
	  return ONIGERR_INVALID_BACKREF;
      }
      *np = node_new_call(tok->u.call.name, tok->u.call.name_end, gnum);
      CHECK_NULL_RETURN_MEMERR(*np);
      env->num_call++;
    }
    break;
#endif

  case TK_ANCHOR:
    *np = onig_node_new_anchor(tok->u.anchor);
    break;

  case TK_OP_REPEAT:
  case TK_INTERVAL:
    if (IS_SYNTAX_BV(env->syntax, ONIG_SYN_CONTEXT_INDEP_REPEAT_OPS)) {
      if (IS_SYNTAX_BV(env->syntax, ONIG_SYN_CONTEXT_INVALID_REPEAT_OPS))
	return ONIGERR_TARGET_OF_REPEAT_OPERATOR_NOT_SPECIFIED;
      else
	*np = node_new_empty();
    }
    else {
      goto tk_byte;
    }
    break;

  default:
    return ONIGERR_PARSER_BUG;
    break;
  }
