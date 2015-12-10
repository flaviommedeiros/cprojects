switch(c)
  {
  case OP_NOT_DIGIT:
  case OP_DIGIT:
  case OP_NOT_WHITESPACE:
  case OP_WHITESPACE:
  case OP_NOT_WORDCHAR:
  case OP_WORDCHAR:
  case OP_ANY:
  case OP_ALLANY:
  case OP_ANYNL:
  case OP_NOT_HSPACE:
  case OP_HSPACE:
  case OP_NOT_VSPACE:
  case OP_VSPACE:
  case OP_EXTUNI:
  case OP_EODN:
  case OP_EOD:
  case OP_DOLL:
  case OP_DOLLM:
  return code;

  case OP_CHAR:
  case OP_NOT:
  GETCHARINCTEST(chr, code);
  list[2] = chr;
  list[3] = NOTACHAR;
  return code;

  case OP_CHARI:
  case OP_NOTI:
  list[0] = (c == OP_CHARI) ? OP_CHAR : OP_NOT;
  GETCHARINCTEST(chr, code);
  list[2] = chr;

#ifdef SUPPORT_UCP
  if (chr < 128 || (chr < 256 && !utf))
    list[3] = fcc[chr];
  else
    list[3] = UCD_OTHERCASE(chr);
#elif defined SUPPORT_UTF || !defined COMPILE_PCRE8
  list[3] = (chr < 256) ? fcc[chr] : chr;
#else
  list[3] = fcc[chr];
#endif

  /* The othercase might be the same value. */

  if (chr == list[3])
    list[3] = NOTACHAR;
  else
    list[4] = NOTACHAR;
  return code;

#ifdef SUPPORT_UCP
  case OP_PROP:
  case OP_NOTPROP:
  if (code[0] != PT_CLIST)
    {
    list[2] = code[0];
    list[3] = code[1];
    return code + 2;
    }

  /* Convert only if we have enough space. */

  clist_src = PRIV(ucd_caseless_sets) + code[1];
  clist_dest = list + 2;
  code += 2;

  do {
     if (clist_dest >= list + 8)
       {
       /* Early return if there is not enough space. This should never
       happen, since all clists are shorter than 5 character now. */
       list[2] = code[0];
       list[3] = code[1];
       return code;
       }
     *clist_dest++ = *clist_src;
     }
  while(*clist_src++ != NOTACHAR);

  /* All characters are stored. The terminating NOTACHAR
  is copied form the clist itself. */

  list[0] = (c == OP_PROP) ? OP_CHAR : OP_NOT;
  return code;
#endif

  case OP_NCLASS:
  case OP_CLASS:
#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
  case OP_XCLASS:
  if (c == OP_XCLASS)
    end = code + GET(code, 0) - 1;
  else
#endif
    end = code + 32 / sizeof(pcre_uchar);

  switch(*end)
    {
    case OP_CRSTAR:
    case OP_CRMINSTAR:
    case OP_CRQUERY:
    case OP_CRMINQUERY:
    case OP_CRPOSSTAR:
    case OP_CRPOSQUERY:
    list[1] = TRUE;
    end++;
    break;

    case OP_CRPLUS:
    case OP_CRMINPLUS:
    case OP_CRPOSPLUS:
    end++;
    break;

    case OP_CRRANGE:
    case OP_CRMINRANGE:
    case OP_CRPOSRANGE:
    list[1] = (GET2(end, 1) == 0);
    end += 1 + 2 * IMM2_SIZE;
    break;
    }
  list[2] = end - code;
  return end;
  }
