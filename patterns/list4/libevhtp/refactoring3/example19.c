switch (NTYPE(node)) {
  case NT_LIST:
  case NT_ALT:
    {
      int v;
      do {
	v = quantifiers_memory_node_info(NCAR(node));
	if (v > r) r = v;
      } while (v >= 0 && IS_NOT_NULL(node = NCDR(node)));
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    if (IS_CALL_RECURSION(NCALL(node))) {
      return NQ_TARGET_IS_EMPTY_REC; /* tiny version */
    }
    else
      r = quantifiers_memory_node_info(NCALL(node)->target);
    break;
#endif

  case NT_QTFR:
    {
      QtfrNode* qn = NQTFR(node);
      if (qn->upper != 0) {
	r = quantifiers_memory_node_info(qn->target);
      }
    }
    break;

  case NT_ENCLOSE:
    {
      EncloseNode* en = NENCLOSE(node);
      switch (en->type) {
      case ENCLOSE_MEMORY:
	return NQ_TARGET_IS_EMPTY_MEM;
	break;

      case ENCLOSE_OPTION:
      case ENCLOSE_STOP_BACKTRACK:
	r = quantifiers_memory_node_info(en->target);
	break;
      default:
	break;
      }
    }
    break;

  case NT_BREF:
  case NT_STR:
  case NT_CTYPE:
  case NT_CCLASS:
  case NT_CANY:
  case NT_ANCHOR:
  default:
    break;
  }
