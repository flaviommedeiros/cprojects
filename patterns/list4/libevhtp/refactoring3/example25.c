switch (type) {
  case NT_LIST:
    {
      Node* prev = NULL_NODE;
      do {
	r = setup_tree(NCAR(node), reg, state, env);
	if (IS_NOT_NULL(prev) && r == 0) {
	  r = next_setup(prev, NCAR(node), reg);
	}
	prev = NCAR(node);
      } while (r == 0 && IS_NOT_NULL(node = NCDR(node)));
    }
    break;

  case NT_ALT:
    do {
      r = setup_tree(NCAR(node), reg, (state | IN_ALT), env);
    } while (r == 0 && IS_NOT_NULL(node = NCDR(node)));
    break;

  case NT_CCLASS:
    break;

  case NT_STR:
    if (IS_IGNORECASE(reg->options) && !NSTRING_IS_RAW(node)) {
      r = expand_case_fold_string(node, reg);
    }
    break;

  case NT_CTYPE:
  case NT_CANY:
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    break;
#endif

  case NT_BREF:
    {
      int i;
      int* p;
      Node** nodes = SCANENV_MEM_NODES(env);
      BRefNode* br = NBREF(node);
      p = BACKREFS_P(br);
      for (i = 0; i < br->back_num; i++) {
	if (p[i] > env->num_mem)  return ONIGERR_INVALID_BACKREF;
	BIT_STATUS_ON_AT(env->backrefed_mem, p[i]);
	BIT_STATUS_ON_AT(env->bt_mem_start, p[i]);
#ifdef USE_BACKREF_WITH_LEVEL
	if (IS_BACKREF_NEST_LEVEL(br)) {
	  BIT_STATUS_ON_AT(env->bt_mem_end, p[i]);
	}
#endif
	SET_ENCLOSE_STATUS(nodes[p[i]], NST_MEM_BACKREFED);
      }
    }
    break;

  case NT_QTFR:
    {
      OnigDistance d;
      QtfrNode* qn = NQTFR(node);
      Node* target = qn->target;

      if ((state & IN_REPEAT) != 0) {
        qn->state |= NST_IN_REPEAT;
      }

      if (IS_REPEAT_INFINITE(qn->upper) || qn->upper >= 1) {
	r = get_min_match_length(target, &d, env);
	if (r) break;
	if (d == 0) {
	  qn->target_empty_info = NQ_TARGET_IS_EMPTY;
#ifdef USE_MONOMANIAC_CHECK_CAPTURES_IN_ENDLESS_REPEAT
	  r = quantifiers_memory_node_info(target);
	  if (r < 0) break;
	  if (r > 0) {
	    qn->target_empty_info = r;
	  }
#endif
#if 0
	  r = get_max_match_length(target, &d, env);
	  if (r == 0 && d == 0) {
	    /*  ()* ==> ()?, ()+ ==> ()  */
	    qn->upper = 1;
	    if (qn->lower > 1) qn->lower = 1;
	    if (NTYPE(target) == NT_STR) {
	      qn->upper = qn->lower = 0;  /* /(?:)+/ ==> // */
	    }
	  }
#endif
	}
      }

      state |= IN_REPEAT;
      if (qn->lower != qn->upper)
	state |= IN_VAR_REPEAT;
      r = setup_tree(target, reg, state, env);
      if (r) break;

      /* expand string */
#define EXPAND_STRING_MAX_LENGTH  100
      if (NTYPE(target) == NT_STR) {
	if (!IS_REPEAT_INFINITE(qn->lower) && qn->lower == qn->upper &&
	    qn->lower > 1 && qn->lower <= EXPAND_STRING_MAX_LENGTH) {
	  int len = NSTRING_LEN(target);
	  StrNode* sn = NSTR(target);

	  if (len * qn->lower <= EXPAND_STRING_MAX_LENGTH) {
	    int i, n = qn->lower;
	    onig_node_conv_to_str_node(node, NSTR(target)->flag);
	    for (i = 0; i < n; i++) {
	      r = onig_node_str_cat(node, sn->s, sn->end);
	      if (r) break;
	    }
	    onig_node_free(target);
	    break; /* break case NT_QTFR: */
	  }
	}
      }

#ifdef USE_OP_PUSH_OR_JUMP_EXACT
      if (qn->greedy && (qn->target_empty_info != 0)) {
	if (NTYPE(target) == NT_QTFR) {
	  QtfrNode* tqn = NQTFR(target);
	  if (IS_NOT_NULL(tqn->head_exact)) {
	    qn->head_exact  = tqn->head_exact;
	    tqn->head_exact = NULL;
	  }
	}
	else {
	  qn->head_exact = get_head_value_node(qn->target, 1, reg);
	}
      }
#endif
    }
    break;

  case NT_ENCLOSE:
    {
      EncloseNode* en = NENCLOSE(node);

      switch (en->type) {
      case ENCLOSE_OPTION:
	{
	  OnigOptionType options = reg->options;
	  reg->options = NENCLOSE(node)->option;
	  r = setup_tree(NENCLOSE(node)->target, reg, state, env);
	  reg->options = options;
	}
	break;

      case ENCLOSE_MEMORY:
	if ((state & (IN_ALT | IN_NOT | IN_VAR_REPEAT)) != 0) {
	  BIT_STATUS_ON_AT(env->bt_mem_start, en->regnum);
	  /* SET_ENCLOSE_STATUS(node, NST_MEM_IN_ALT_NOT); */
	}
        r = setup_tree(en->target, reg, state, env);
        break;

      case ENCLOSE_STOP_BACKTRACK:
	{
	  Node* target = en->target;
	  r = setup_tree(target, reg, state, env);
	  if (NTYPE(target) == NT_QTFR) {
	    QtfrNode* tqn = NQTFR(target);
	    if (IS_REPEAT_INFINITE(tqn->upper) && tqn->lower <= 1 &&
		tqn->greedy != 0) {  /* (?>a*), a*+ etc... */
	      int qtype = NTYPE(tqn->target);
	      if (IS_NODE_TYPE_SIMPLE(qtype))
		SET_ENCLOSE_STATUS(node, NST_STOP_BT_SIMPLE_REPEAT);
	    }
	  }
	}
	break;
      }
    }
    break;

  case NT_ANCHOR:
    {
      AnchorNode* an = NANCHOR(node);

      switch (an->type) {
      case ANCHOR_PREC_READ:
	r = setup_tree(an->target, reg, state, env);
	break;
      case ANCHOR_PREC_READ_NOT:
	r = setup_tree(an->target, reg, (state | IN_NOT), env);
	break;

/* allowed node types in look-behind */
#define ALLOWED_TYPE_IN_LB  \
  ( BIT_NT_LIST | BIT_NT_ALT | BIT_NT_STR | BIT_NT_CCLASS | BIT_NT_CTYPE | \
    BIT_NT_CANY | BIT_NT_ANCHOR | BIT_NT_ENCLOSE | BIT_NT_QTFR | BIT_NT_CALL )

#define ALLOWED_ENCLOSE_IN_LB       ( ENCLOSE_MEMORY )
#define ALLOWED_ENCLOSE_IN_LB_NOT   0

#define ALLOWED_ANCHOR_IN_LB \
( ANCHOR_LOOK_BEHIND | ANCHOR_BEGIN_LINE | ANCHOR_END_LINE | ANCHOR_BEGIN_BUF | ANCHOR_BEGIN_POSITION )
#define ALLOWED_ANCHOR_IN_LB_NOT \
( ANCHOR_LOOK_BEHIND | ANCHOR_LOOK_BEHIND_NOT | ANCHOR_BEGIN_LINE | ANCHOR_END_LINE | ANCHOR_BEGIN_BUF | ANCHOR_BEGIN_POSITION )

      case ANCHOR_LOOK_BEHIND:
	{
	  r = check_type_tree(an->target, ALLOWED_TYPE_IN_LB,
			      ALLOWED_ENCLOSE_IN_LB, ALLOWED_ANCHOR_IN_LB);
	  if (r < 0) return r;
	  if (r > 0) return ONIGERR_INVALID_LOOK_BEHIND_PATTERN;
	  r = setup_look_behind(node, reg, env);
	  if (r != 0) return r;
	  r = setup_tree(an->target, reg, state, env);
	}
	break;

      case ANCHOR_LOOK_BEHIND_NOT:
	{
	  r = check_type_tree(an->target, ALLOWED_TYPE_IN_LB,
		      ALLOWED_ENCLOSE_IN_LB_NOT, ALLOWED_ANCHOR_IN_LB_NOT);
	  if (r < 0) return r;
	  if (r > 0) return ONIGERR_INVALID_LOOK_BEHIND_PATTERN;
	  r = setup_look_behind(node, reg, env);
	  if (r != 0) return r;
	  r = setup_tree(an->target, reg, (state | IN_NOT), env);
	}
	break;
      }
    }
    break;

  default:
    break;
  }
