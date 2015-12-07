switch (category)
  {
#ifdef LC_COLLATE
  case LC_COLLATE:
    retval = "LC_COLLATE";
    break;
#endif
#ifdef LC_CTYPE
  case LC_CTYPE:
    retval = "LC_CTYPE";
    break;
#endif
#ifdef LC_MONETARY
  case LC_MONETARY:
    retval = "LC_MONETARY";
    break;
#endif
#ifdef LC_NUMERIC
  case LC_NUMERIC:
    retval = "LC_NUMERIC";
    break;
#endif
#ifdef LC_TIME
  case LC_TIME:
    retval = "LC_TIME";
    break;
#endif
#ifdef LC_MESSAGES
  case LC_MESSAGES:
    retval = "LC_MESSAGES";
    break;
#endif
#ifdef LC_RESPONSE
  case LC_RESPONSE:
    retval = "LC_RESPONSE";
    break;
#endif
#ifdef LC_ALL
  case LC_ALL:
    /* This might not make sense but is perhaps better than any other
       value.  */
    retval = "LC_ALL";
    break;
#endif
  default:
    /* If you have a better idea for a default value let me know.  */
    retval = "LC_XXX";
  }
