switch (NTYPE(node)) {
  case NT_LIST:
    do {
      r = get_max_match_length(NCAR(node), &tmax, env);
      if (r == 0)
	*max = distance_add(*max, tmax);
    } while (r == 0 && IS_NOT_NULL(node = NCDR(node)));
    break;

  case NT_ALT:
    do {
      r = get_max_match_length(NCAR(node), &tmax, env);
      if (r == 0 && *max < tmax) *max = tmax;
    } while (r == 0 && IS_NOT_NULL(node = NCDR(node)));
    break;

  case NT_STR:
    {
      StrNode* sn = NSTR(node);
      *max = sn->end - sn->s;
    }
    break;

  case NT_CTYPE:
    *max = ONIGENC_MBC_MAXLEN_DIST(env->enc);
    break;

  case NT_CCLASS:
  case NT_CANY:
    *max = ONIGENC_MBC_MAXLEN_DIST(env->enc);
    break;

  case NT_BREF:
    {
      int i;
      int* backs;
      Node** nodes = SCANENV_MEM_NODES(env);
      BRefNode* br = NBREF(node);
      if (br->state & NST_RECURSION) {
	*max = ONIG_INFINITE_DISTANCE;
	break;
      }
      backs = BACKREFS_P(br);
      for (i = 0; i < br->back_num; i++) {
	if (backs[i] > env->num_mem)  return ONIGERR_INVALID_BACKREF;
	r = get_max_match_length(nodes[backs[i]], &tmax, env);
	if (r != 0) break;
	if (*max < tmax) *max = tmax;
      }
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    if (! IS_CALL_RECURSION(NCALL(node)))
      r = get_max_match_length(NCALL(node)->target, max, env);
    else
      *max = ONIG_INFINITE_DISTANCE;
    break;
#endif

  case NT_QTFR:
    {
      QtfrNode* qn = NQTFR(node);

      if (qn->upper != 0) {
	r = get_max_match_length(qn->target, max, env);
	if (r == 0 && *max != 0) {
	  if (! IS_REPEAT_INFINITE(qn->upper))
	    *max = distance_multiply(*max, qn->upper);
	  else
	    *max = ONIG_INFINITE_DISTANCE;
	}
      }
    }
    break;

  case NT_ENCLOSE:
    {
      EncloseNode* en = NENCLOSE(node);
      switch (en->type) {
      case ENCLOSE_MEMORY:
#ifdef USE_SUBEXP_CALL
	if (IS_ENCLOSE_MAX_FIXED(en))
	  *max = en->max_len;
	else {
	  r = get_max_match_length(en->target, max, env);
	  if (r == 0) {
	    en->max_len = *max;
	    SET_ENCLOSE_STATUS(node, NST_MAX_FIXED);
	  }
	}
	break;
#endif
      case ENCLOSE_OPTION:
      case ENCLOSE_STOP_BACKTRACK:
	r = get_max_match_length(en->target, max, env);
	break;
      }
    }
    break;

  case NT_ANCHOR:
  default:
    break;
  }
