switch (NTYPE(node)) {
  case NT_BREF:
  case NT_ALT:
  case NT_CANY:
#ifdef USE_SUBEXP_CALL
  case NT_CALL:
#endif
    break;

  case NT_CTYPE:
  case NT_CCLASS:
    if (exact == 0) {
      n = node;
    }
    break;

  case NT_LIST:
    n = get_head_value_node(NCAR(node), exact, reg);
    break;

  case NT_STR:
    {
      StrNode* sn = NSTR(node);

      if (sn->end <= sn->s)
	break;

      if (exact != 0 &&
	  !NSTRING_IS_RAW(node) && IS_IGNORECASE(reg->options)) {
      }
      else {
	n = node;
      }
    }
    break;

  case NT_QTFR:
    {
      QtfrNode* qn = NQTFR(node);
      if (qn->lower > 0) {
	if (IS_NOT_NULL(qn->head_exact))
	  n = qn->head_exact;
	else
	  n = get_head_value_node(qn->target, exact, reg);
      }
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
	  n = get_head_value_node(NENCLOSE(node)->target, exact, reg);
	  reg->options = options;
	}
	break;

      case ENCLOSE_MEMORY:
      case ENCLOSE_STOP_BACKTRACK:
	n = get_head_value_node(en->target, exact, reg);
	break;
      }
    }
    break;

  case NT_ANCHOR:
    if (NANCHOR(node)->type == ANCHOR_PREC_READ)
      n = get_head_value_node(NANCHOR(node)->target, exact, reg);
    break;

  default:
    break;
  }
