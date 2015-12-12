switch (c) {
    case ':':   /* (?:...) grouping only */
    group:
      r = fetch_token(tok, &p, end, env);
      if (r < 0) return r;
      r = parse_subexp(np, tok, term, &p, end, env);
      if (r < 0) return r;
      *src = p;
      return 1; /* group */
      break;

    case '=':
      *np = onig_node_new_anchor(ANCHOR_PREC_READ);
      break;
    case '!':  /*         preceding read */
      *np = onig_node_new_anchor(ANCHOR_PREC_READ_NOT);
      break;
    case '>':            /* (?>...) stop backtrack */
      *np = node_new_enclose(ENCLOSE_STOP_BACKTRACK);
      break;

#ifdef USE_NAMED_GROUP
    case '\'':
      if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_QMARK_LT_NAMED_GROUP)) {
	goto named_group1;
      }
      else
	return ONIGERR_UNDEFINED_GROUP_OPTION;
      break;
#endif

    case '<':   /* look behind (?<=...), (?<!...) */
      PFETCH(c);
      if (c == '=')
	*np = onig_node_new_anchor(ANCHOR_LOOK_BEHIND);
      else if (c == '!')
	*np = onig_node_new_anchor(ANCHOR_LOOK_BEHIND_NOT);
#ifdef USE_NAMED_GROUP
      else {
	if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_QMARK_LT_NAMED_GROUP)) {
	  UChar *name;
	  UChar *name_end;

	  PUNFETCH;
	  c = '<';

	named_group1:
	  list_capture = 0;

	named_group2:
	  name = p;
	  r = fetch_name((OnigCodePoint )c, &p, end, &name_end, env, &num, 0);
	  if (r < 0) return r;

	  num = scan_env_add_mem_entry(env);
	  if (num < 0) return num;
	  if (list_capture != 0 && num >= (int )BIT_STATUS_BITS_NUM)
	    return ONIGERR_GROUP_NUMBER_OVER_FOR_CAPTURE_HISTORY;

	  r = name_add(env->reg, name, name_end, num, env);
	  if (r != 0) return r;
	  *np = node_new_enclose_memory(env->option, 1);
	  CHECK_NULL_RETURN_MEMERR(*np);
	  NENCLOSE(*np)->regnum = num;
	  if (list_capture != 0)
	    BIT_STATUS_ON_AT_SIMPLE(env->capture_history, num);
	  env->num_named++;
	}
	else {
	  return ONIGERR_UNDEFINED_GROUP_OPTION;
	}
      }
#else
      else {
	return ONIGERR_UNDEFINED_GROUP_OPTION;
      }
#endif
      break;

    case '@':
      if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_ATMARK_CAPTURE_HISTORY)) {
#ifdef USE_NAMED_GROUP
	if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_QMARK_LT_NAMED_GROUP)) {
	  PFETCH(c);
	  if (c == '<' || c == '\'') {
	    list_capture = 1;
	    goto named_group2; /* (?@<name>...) */
	  }
	  PUNFETCH;
	}
#endif
	*np = node_new_enclose_memory(env->option, 0);
	CHECK_NULL_RETURN_MEMERR(*np);
	num = scan_env_add_mem_entry(env);
	if (num < 0) {
	  onig_node_free(*np);
	  return num;
	}
	else if (num >= (int )BIT_STATUS_BITS_NUM) {
	  onig_node_free(*np);
	  return ONIGERR_GROUP_NUMBER_OVER_FOR_CAPTURE_HISTORY;
	}
	NENCLOSE(*np)->regnum = num;
	BIT_STATUS_ON_AT_SIMPLE(env->capture_history, num);
      }
      else {
	return ONIGERR_UNDEFINED_GROUP_OPTION;
      }
      break;

#ifdef USE_POSIXLINE_OPTION
    case 'p':
#endif
    case '-': case 'i': case 'm': case 's': case 'x':
      {
	int neg = 0;

	while (1) {
	  switch (c) {
	  case ':':
	  case ')':
	  break;

	  case '-':  neg = 1; break;
	  case 'x':  ONOFF(option, ONIG_OPTION_EXTEND,     neg); break;
	  case 'i':  ONOFF(option, ONIG_OPTION_IGNORECASE, neg); break;
	  case 's':
	    if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_OPTION_PERL)) {
	      ONOFF(option, ONIG_OPTION_MULTILINE,  neg);
	    }
	    else
	      return ONIGERR_UNDEFINED_GROUP_OPTION;
	    break;

	  case 'm':
	    if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_OPTION_PERL)) {
	      ONOFF(option, ONIG_OPTION_SINGLELINE, (neg == 0 ? 1 : 0));
	    }
	    else if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_OPTION_RUBY)) {
	      ONOFF(option, ONIG_OPTION_MULTILINE,  neg);
	    }
	    else
	      return ONIGERR_UNDEFINED_GROUP_OPTION;
	    break;
#ifdef USE_POSIXLINE_OPTION
	  case 'p':
	    ONOFF(option, ONIG_OPTION_MULTILINE|ONIG_OPTION_SINGLELINE, neg);
	    break;
#endif
	  default:
	    return ONIGERR_UNDEFINED_GROUP_OPTION;
	  }

	  if (c == ')') {
	    *np = node_new_option(option);
	    CHECK_NULL_RETURN_MEMERR(*np);
	    *src = p;
	    return 2; /* option only */
	  }
	  else if (c == ':') {
	    OnigOptionType prev = env->option;

	    env->option     = option;
	    r = fetch_token(tok, &p, end, env);
	    if (r < 0) return r;
	    r = parse_subexp(&target, tok, term, &p, end, env);
	    env->option = prev;
	    if (r < 0) return r;
	    *np = node_new_option(option);
	    CHECK_NULL_RETURN_MEMERR(*np);
	    NENCLOSE(*np)->target = target;
	    *src = p;
	    return 0;
	  }

	  if (PEND) return ONIGERR_END_PATTERN_IN_GROUP;
	  PFETCH(c);
	}
      }
      break;

    default:
      return ONIGERR_UNDEFINED_GROUP_OPTION;
    }
