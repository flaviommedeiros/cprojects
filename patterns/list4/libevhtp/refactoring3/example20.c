switch (NTYPE(node)) {
  case NT_BREF:
    {
      int i;
      int* backs;
      Node** nodes = SCANENV_MEM_NODES(env);
      BRefNode* br = NBREF(node);
      if (br->state & NST_RECURSION) break;

      backs = BACKREFS_P(br);
      if (backs[0] > env->num_mem)  return ONIGERR_INVALID_BACKREF;
      r = get_min_match_length(nodes[backs[0]], min, env);
      if (r != 0) break;
      for (i = 1; i < br->back_num; i++) {
	if (backs[i] > env->num_mem)  return ONIGERR_INVALID_BACKREF;
	r = get_min_match_length(nodes[backs[i]], &tmin, env);
	if (r != 0) break;
	if (*min > tmin) *min = tmin;
      }
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    if (IS_CALL_RECURSION(NCALL(node))) {
      EncloseNode* en = NENCLOSE(NCALL(node)->target);
      if (IS_ENCLOSE_MIN_FIXED(en))
	*min = en->min_len;
    }
    else
      r = get_min_match_length(NCALL(node)->target, min, env);
    break;
#endif

  case NT_LIST:
    do {
      r = get_min_match_length(NCAR(node), &tmin, env);
      if (r == 0) *min += tmin;
    } while (r == 0 && IS_NOT_NULL(node = NCDR(node)));
    break;

  case NT_ALT:
    {
      Node *x, *y;
      y = node;
      do {
	x = NCAR(y);
	r = get_min_match_length(x, &tmin, env);
	if (r != 0) break;
	if (y == node) *min = tmin;
	else if (*min > tmin) *min = tmin;
      } while (r == 0 && IS_NOT_NULL(y = NCDR(y)));
    }
    break;

  case NT_STR:
    {
      StrNode* sn = NSTR(node);
      *min = sn->end - sn->s;
    }
    break;

  case NT_CTYPE:
    *min = 1;
    break;

  case NT_CCLASS:
  case NT_CANY:
    *min = 1;
    break;

  case NT_QTFR:
    {
      QtfrNode* qn = NQTFR(node);

      if (qn->lower > 0) {
	r = get_min_match_length(qn->target, min, env);
	if (r == 0)
	  *min = distance_multiply(*min, qn->lower);
      }
    }
    break;

  case NT_ENCLOSE:
    {
      EncloseNode* en = NENCLOSE(node);
      switch (en->type) {
      case ENCLOSE_MEMORY:
#ifdef USE_SUBEXP_CALL
	if (IS_ENCLOSE_MIN_FIXED(en))
	  *min = en->min_len;
	else {
	  r = get_min_match_length(en->target, min, env);
	  if (r == 0) {
	    en->min_len = *min;
	    SET_ENCLOSE_STATUS(node, NST_MIN_FIXED);
	  }
	}
	break;
#endif
      case ENCLOSE_OPTION:
      case ENCLOSE_STOP_BACKTRACK:
	r = get_min_match_length(en->target, min, env);
	break;
      }
    }
    break;

  case NT_ANCHOR:
  default:
    break;
  }
