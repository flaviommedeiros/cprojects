switch (node->type)
    {
    case CHARACTER:
      if (node->opr.c != ch)
        return false;
      break;

    case SIMPLE_BRACKET:
      if (!bitset_contain (node->opr.sbcset, ch))
        return false;
      break;

#ifdef RE_ENABLE_I18N
    case OP_UTF8_PERIOD:
      if (ch >= ASCII_CHARS)
        return false;
      /* FALLTHROUGH */
#endif
    case OP_PERIOD:
      if ((ch == '\n' && !(mctx->dfa->syntax & RE_DOT_NEWLINE))
	  || (ch == '\0' && (mctx->dfa->syntax & RE_DOT_NOT_NULL)))
	return false;
      break;

    default:
      return false;
    }
