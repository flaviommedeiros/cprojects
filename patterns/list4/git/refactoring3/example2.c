switch (node->type)
    {
    case CHARACTER:
      if (node->opr.c != ch)
	return 0;
      break;

    case SIMPLE_BRACKET:
      if (!bitset_contain (node->opr.sbcset, ch))
	return 0;
      break;

#ifdef RE_ENABLE_I18N
    case OP_UTF8_PERIOD:
      if (ch >= 0x80)
	return 0;
      /* FALLTHROUGH */
#endif
    case OP_PERIOD:
      if ((ch == '\n' && !(mctx->dfa->syntax & RE_DOT_NEWLINE))
	  || (ch == '\0' && (mctx->dfa->syntax & RE_DOT_NOT_NULL)))
	return 0;
      break;

    default:
      return 0;
    }
