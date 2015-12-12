switch (*cc)
    {
    case OP_CHARI:
    caseless = TRUE;
    case OP_CHAR:
    last = FALSE;
    cc++;
    break;

    case OP_SOD:
    case OP_SOM:
    case OP_SET_SOM:
    case OP_NOT_WORD_BOUNDARY:
    case OP_WORD_BOUNDARY:
    case OP_EODN:
    case OP_EOD:
    case OP_CIRC:
    case OP_CIRCM:
    case OP_DOLL:
    case OP_DOLLM:
    /* Zero width assertions. */
    cc++;
    continue;

    case OP_ASSERT:
    case OP_ASSERT_NOT:
    case OP_ASSERTBACK:
    case OP_ASSERTBACK_NOT:
    cc = bracketend(cc);
    continue;

    case OP_PLUSI:
    case OP_MINPLUSI:
    case OP_POSPLUSI:
    caseless = TRUE;
    case OP_PLUS:
    case OP_MINPLUS:
    case OP_POSPLUS:
    cc++;
    break;

    case OP_EXACTI:
    caseless = TRUE;
    case OP_EXACT:
    repeat = GET2(cc, 1);
    last = FALSE;
    cc += 1 + IMM2_SIZE;
    break;

    case OP_QUERYI:
    case OP_MINQUERYI:
    case OP_POSQUERYI:
    caseless = TRUE;
    case OP_QUERY:
    case OP_MINQUERY:
    case OP_POSQUERY:
    len = 1;
    cc++;
#ifdef SUPPORT_UTF
    if (common->utf && HAS_EXTRALEN(*cc)) len += GET_EXTRALEN(*cc);
#endif
    max_chars = scan_prefix(common, cc + len, chars, bytes, max_chars);
    if (max_chars == 0)
      return consumed;
    last = FALSE;
    break;

    case OP_KET:
    cc += 1 + LINK_SIZE;
    continue;

    case OP_ALT:
    cc += GET(cc, 1);
    continue;

    case OP_ONCE:
    case OP_ONCE_NC:
    case OP_BRA:
    case OP_BRAPOS:
    case OP_CBRA:
    case OP_CBRAPOS:
    alternative = cc + GET(cc, 1);
    while (*alternative == OP_ALT)
      {
      max_chars = scan_prefix(common, alternative + 1 + LINK_SIZE, chars, bytes, max_chars);
      if (max_chars == 0)
        return consumed;
      alternative += GET(alternative, 1);
      }

    if (*cc == OP_CBRA || *cc == OP_CBRAPOS)
      cc += IMM2_SIZE;
    cc += 1 + LINK_SIZE;
    continue;

    case OP_CLASS:
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
    if (common->utf && !is_char7_bitset((const pcre_uint8 *)(cc + 1), FALSE)) return consumed;
#endif
    any = TRUE;
    cc += 1 + 32 / sizeof(pcre_uchar);
    break;

    case OP_NCLASS:
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
    if (common->utf) return consumed;
#endif
    any = TRUE;
    cc += 1 + 32 / sizeof(pcre_uchar);
    break;

#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
    case OP_XCLASS:
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
    if (common->utf) return consumed;
#endif
    any = TRUE;
    cc += GET(cc, 1);
    break;
#endif

    case OP_DIGIT:
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
    if (common->utf && !is_char7_bitset((const pcre_uint8 *)common->ctypes - cbit_length + cbit_digit, FALSE))
      return consumed;
#endif
    any = TRUE;
    cc++;
    break;

    case OP_WHITESPACE:
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
    if (common->utf && !is_char7_bitset((const pcre_uint8 *)common->ctypes - cbit_length + cbit_space, FALSE))
      return consumed;
#endif
    any = TRUE;
    cc++;
    break;

    case OP_WORDCHAR:
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
    if (common->utf && !is_char7_bitset((const pcre_uint8 *)common->ctypes - cbit_length + cbit_word, FALSE))
      return consumed;
#endif
    any = TRUE;
    cc++;
    break;

    case OP_NOT:
    case OP_NOTI:
    cc++;
    /* Fall through. */
    case OP_NOT_DIGIT:
    case OP_NOT_WHITESPACE:
    case OP_NOT_WORDCHAR:
    case OP_ANY:
    case OP_ALLANY:
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
    if (common->utf) return consumed;
#endif
    any = TRUE;
    cc++;
    break;

#ifdef SUPPORT_UCP
    case OP_NOTPROP:
    case OP_PROP:
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
    if (common->utf) return consumed;
#endif
    any = TRUE;
    cc += 1 + 2;
    break;
#endif

    case OP_TYPEEXACT:
    repeat = GET2(cc, 1);
    cc += 1 + IMM2_SIZE;
    continue;

    case OP_NOTEXACT:
    case OP_NOTEXACTI:
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
    if (common->utf) return consumed;
#endif
    any = TRUE;
    repeat = GET2(cc, 1);
    cc += 1 + IMM2_SIZE + 1;
    break;

    default:
    return consumed;
    }
