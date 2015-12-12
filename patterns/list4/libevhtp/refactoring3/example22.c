switch (NTYPE(node)) {
  case NT_LIST:
    do {
      r = get_char_length_tree1(NCAR(node), reg, &tlen, level);
      if (r == 0)
	*len = distance_add(*len, tlen);
    } while (r == 0 && IS_NOT_NULL(node = NCDR(node)));
    break;

  case NT_ALT:
    {
      int tlen2;
      int varlen = 0;

      r = get_char_length_tree1(NCAR(node), reg, &tlen, level);
      while (r == 0 && IS_NOT_NULL(node = NCDR(node))) {
	r = get_char_length_tree1(NCAR(node), reg, &tlen2, level);
	if (r == 0) {
	  if (tlen != tlen2)
	    varlen = 1;
	}
      }
      if (r == 0) {
	if (varlen != 0) {
	  if (level == 1)
	    r = GET_CHAR_LEN_TOP_ALT_VARLEN;
	  else
	    r = GET_CHAR_LEN_VARLEN;
	}
	else
	  *len = tlen;
      }
    }
    break;

  case NT_STR:
    {
      StrNode* sn = NSTR(node);
      UChar *s = sn->s;
      while (s < sn->end) {
	s += enclen(reg->enc, s);
	(*len)++;
      }
    }
    break;

  case NT_QTFR:
    {
      QtfrNode* qn = NQTFR(node);
      if (qn->lower == qn->upper) {
	r = get_char_length_tree1(qn->target, reg, &tlen, level);
	if (r == 0)
	  *len = distance_multiply(tlen, qn->lower);
      }
      else
	r = GET_CHAR_LEN_VARLEN;
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    if (! IS_CALL_RECURSION(NCALL(node)))
      r = get_char_length_tree1(NCALL(node)->target, reg, len, level);
    else
      r = GET_CHAR_LEN_VARLEN;
    break;
#endif

  case NT_CTYPE:
    *len = 1;
    break;

  case NT_CCLASS:
  case NT_CANY:
    *len = 1;
    break;

  case NT_ENCLOSE:
    {
      EncloseNode* en = NENCLOSE(node);
      switch (en->type) {
      case ENCLOSE_MEMORY:
#ifdef USE_SUBEXP_CALL
	if (IS_ENCLOSE_CLEN_FIXED(en))
	  *len = en->char_len;
	else {
	  r = get_char_length_tree1(en->target, reg, len, level);
	  if (r == 0) {
	    en->char_len = *len;
	    SET_ENCLOSE_STATUS(node, NST_CLEN_FIXED);
	  }
	}
	break;
#endif
      case ENCLOSE_OPTION:
      case ENCLOSE_STOP_BACKTRACK:
	r = get_char_length_tree1(en->target, reg, len, level);
	break;
      default:
	break;
      }
    }
    break;

  case NT_ANCHOR:
    break;

  default:
    r = GET_CHAR_LEN_VARLEN;
    break;
  }
