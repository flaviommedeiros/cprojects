switch (type) {
  case NT_LIST:
    {
      OptEnv nenv;
      NodeOptInfo nopt;
      Node* nd = node;

      copy_opt_env(&nenv, env);
      do {
	r = optimize_node_left(NCAR(nd), &nopt, &nenv);
	if (r == 0) {
	  add_mml(&nenv.mmd, &nopt.len);
	  concat_left_node_opt_info(env->enc, opt, &nopt);
	}
      } while (r == 0 && IS_NOT_NULL(nd = NCDR(nd)));
    }
    break;

  case NT_ALT:
    {
      NodeOptInfo nopt;
      Node* nd = node;

      do {
	r = optimize_node_left(NCAR(nd), &nopt, env);
	if (r == 0) {
	  if (nd == node) copy_node_opt_info(opt, &nopt);
	  else            alt_merge_node_opt_info(opt, &nopt, env);
	}
      } while ((r == 0) && IS_NOT_NULL(nd = NCDR(nd)));
    }
    break;

  case NT_STR:
    {
      StrNode* sn = NSTR(node);
      int slen = sn->end - sn->s;
      int is_raw = NSTRING_IS_RAW(node);

      if (! NSTRING_IS_AMBIG(node)) {
	concat_opt_exact_info_str(&opt->exb, sn->s, sn->end,
				  NSTRING_IS_RAW(node), env->enc);
	if (slen > 0) {
	  add_char_opt_map_info(&opt->map, *(sn->s), env->enc);
	}
        set_mml(&opt->len, slen, slen);
      }
      else {
        int max;

	if (NSTRING_IS_DONT_GET_OPT_INFO(node)) {
          int n = onigenc_strlen(env->enc, sn->s, sn->end);
          max = ONIGENC_MBC_MAXLEN_DIST(env->enc) * n;
	}
	else {
	  concat_opt_exact_info_str(&opt->exb, sn->s, sn->end,
				    is_raw, env->enc);
	  opt->exb.ignore_case = 1;

	  if (slen > 0) {
	    r = add_char_amb_opt_map_info(&opt->map, sn->s, sn->end,
					  env->enc, env->case_fold_flag);
	    if (r != 0) break;
	  }

	  max = slen;
	}

        set_mml(&opt->len, slen, max);
      }

      if (opt->exb.len == slen)
	opt->exb.reach_end = 1;
    }
    break;

  case NT_CCLASS:
    {
      int i, z;
      CClassNode* cc = NCCLASS(node);

      /* no need to check ignore case. (setted in setup_tree()) */

      if (IS_NOT_NULL(cc->mbuf) || IS_NCCLASS_NOT(cc)) {
        OnigDistance min = ONIGENC_MBC_MINLEN(env->enc);
	OnigDistance max = ONIGENC_MBC_MAXLEN_DIST(env->enc);

	set_mml(&opt->len, min, max);
      }
      else {
        for (i = 0; i < SINGLE_BYTE_SIZE; i++) {
          z = BITSET_AT(cc->bs, i);
          if ((z && !IS_NCCLASS_NOT(cc)) || (!z && IS_NCCLASS_NOT(cc))) {
            add_char_opt_map_info(&opt->map, (UChar )i, env->enc);
          }
        }
	set_mml(&opt->len, 1, 1);
      }
    }
    break;

  case NT_CTYPE:
    {
      int i, min, max;

      max = ONIGENC_MBC_MAXLEN_DIST(env->enc);

      if (max == 1) {
        min = 1;

	switch (NCTYPE(node)->ctype) {
	case ONIGENC_CTYPE_WORD:
	  if (NCTYPE(node)->not != 0) {
	    for (i = 0; i < SINGLE_BYTE_SIZE; i++) {
	      if (! ONIGENC_IS_CODE_WORD(env->enc, i)) {
		add_char_opt_map_info(&opt->map, (UChar )i, env->enc);
	      }
	    }
	  }
	  else {
	    for (i = 0; i < SINGLE_BYTE_SIZE; i++) {
	      if (ONIGENC_IS_CODE_WORD(env->enc, i)) {
		add_char_opt_map_info(&opt->map, (UChar )i, env->enc);
	      }
	    }
	  }
	  break;
	}
      }
      else {
        min = ONIGENC_MBC_MINLEN(env->enc);
      }
      set_mml(&opt->len, min, max);
    }
    break;

  case NT_CANY:
    {
      OnigDistance min = ONIGENC_MBC_MINLEN(env->enc);
      OnigDistance max = ONIGENC_MBC_MAXLEN_DIST(env->enc);
      set_mml(&opt->len, min, max);
    }
    break;

  case NT_ANCHOR:
    switch (NANCHOR(node)->type) {
    case ANCHOR_BEGIN_BUF:
    case ANCHOR_BEGIN_POSITION:
    case ANCHOR_BEGIN_LINE:
    case ANCHOR_END_BUF:
    case ANCHOR_SEMI_END_BUF:
    case ANCHOR_END_LINE:
      add_opt_anc_info(&opt->anc, NANCHOR(node)->type);
      break;

    case ANCHOR_PREC_READ:
      {
	NodeOptInfo nopt;

	r = optimize_node_left(NANCHOR(node)->target, &nopt, env);
	if (r == 0) {
	  if (nopt.exb.len > 0)
	    copy_opt_exact_info(&opt->expr, &nopt.exb);
	  else if (nopt.exm.len > 0)
	    copy_opt_exact_info(&opt->expr, &nopt.exm);

	  opt->expr.reach_end = 0;

	  if (nopt.map.value > 0)
	    copy_opt_map_info(&opt->map, &nopt.map);
	}
      }
      break;

    case ANCHOR_PREC_READ_NOT:
    case ANCHOR_LOOK_BEHIND: /* Sorry, I can't make use of it. */
    case ANCHOR_LOOK_BEHIND_NOT:
      break;
    }
    break;

  case NT_BREF:
    {
      int i;
      int* backs;
      OnigDistance min, max, tmin, tmax;
      Node** nodes = SCANENV_MEM_NODES(env->scan_env);
      BRefNode* br = NBREF(node);

      if (br->state & NST_RECURSION) {
	set_mml(&opt->len, 0, ONIG_INFINITE_DISTANCE);
	break;
      }
      backs = BACKREFS_P(br);
      r = get_min_match_length(nodes[backs[0]], &min, env->scan_env);
      if (r != 0) break;
      r = get_max_match_length(nodes[backs[0]], &max, env->scan_env);
      if (r != 0) break;
      for (i = 1; i < br->back_num; i++) {
	r = get_min_match_length(nodes[backs[i]], &tmin, env->scan_env);
	if (r != 0) break;
	r = get_max_match_length(nodes[backs[i]], &tmax, env->scan_env);
	if (r != 0) break;
	if (min > tmin) min = tmin;
	if (max < tmax) max = tmax;
      }
      if (r == 0) set_mml(&opt->len, min, max);
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    if (IS_CALL_RECURSION(NCALL(node)))
      set_mml(&opt->len, 0, ONIG_INFINITE_DISTANCE);
    else {
      OnigOptionType save = env->options;
      env->options = NENCLOSE(NCALL(node)->target)->option;
      r = optimize_node_left(NCALL(node)->target, opt, env);
      env->options = save;
    }
    break;
#endif

  case NT_QTFR:
    {
      int i;
      OnigDistance min, max;
      NodeOptInfo nopt;
      QtfrNode* qn = NQTFR(node);

      r = optimize_node_left(qn->target, &nopt, env);
      if (r) break;

      if (qn->lower == 0 && IS_REPEAT_INFINITE(qn->upper)) {
	if (env->mmd.max == 0 &&
	    NTYPE(qn->target) == NT_CANY && qn->greedy) {
	  if (IS_MULTILINE(env->options))
	    add_opt_anc_info(&opt->anc, ANCHOR_ANYCHAR_STAR_ML);
	  else
	    add_opt_anc_info(&opt->anc, ANCHOR_ANYCHAR_STAR);
	}
      }
      else {
	if (qn->lower > 0) {
	  copy_node_opt_info(opt, &nopt);
	  if (nopt.exb.len > 0) {
	    if (nopt.exb.reach_end) {
	      for (i = 2; i <= qn->lower &&
		          ! is_full_opt_exact_info(&opt->exb); i++) {
		concat_opt_exact_info(&opt->exb, &nopt.exb, env->enc);
	      }
	      if (i < qn->lower) {
		opt->exb.reach_end = 0;
	      }
	    }
	  }

	  if (qn->lower != qn->upper) {
	    opt->exb.reach_end = 0;
	    opt->exm.reach_end = 0;
	  }
	  if (qn->lower > 1)
	    opt->exm.reach_end = 0;
	}
      }

      min = distance_multiply(nopt.len.min, qn->lower);
      if (IS_REPEAT_INFINITE(qn->upper))
	max = (nopt.len.max > 0 ? ONIG_INFINITE_DISTANCE : 0);
      else
	max = distance_multiply(nopt.len.max, qn->upper);

      set_mml(&opt->len, min, max);
    }
    break;

  case NT_ENCLOSE:
    {
      EncloseNode* en = NENCLOSE(node);

      switch (en->type) {
      case ENCLOSE_OPTION:
	{
	  OnigOptionType save = env->options;

	  env->options = en->option;
	  r = optimize_node_left(en->target, opt, env);
	  env->options = save;
	}
	break;

      case ENCLOSE_MEMORY:
#ifdef USE_SUBEXP_CALL
	en->opt_count++;
	if (en->opt_count > MAX_NODE_OPT_INFO_REF_COUNT) {
	  OnigDistance min, max;

	  min = 0;
	  max = ONIG_INFINITE_DISTANCE;
	  if (IS_ENCLOSE_MIN_FIXED(en)) min = en->min_len;
	  if (IS_ENCLOSE_MAX_FIXED(en)) max = en->max_len;
	  set_mml(&opt->len, min, max);
	}
	else
#endif
	{
	  r = optimize_node_left(en->target, opt, env);

	  if (is_set_opt_anc_info(&opt->anc, ANCHOR_ANYCHAR_STAR_MASK)) {
	    if (BIT_STATUS_AT(env->scan_env->backrefed_mem, en->regnum))
	      remove_opt_anc_info(&opt->anc, ANCHOR_ANYCHAR_STAR_MASK);
	  }
	}
	break;

      case ENCLOSE_STOP_BACKTRACK:
	r = optimize_node_left(en->target, opt, env);
	break;
      }
    }
    break;

  default:
#ifdef ONIG_DEBUG
    fprintf(stderr, "optimize_node_left: undefined node type %d\n",
	    NTYPE(node));
#endif
    r = ONIGERR_TYPE_BUG;
    break;
  }
