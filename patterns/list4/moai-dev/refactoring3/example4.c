switch (BYTE_TYPE(enc, ptr)) {
  case BT_QUOT:
    return PREFIX(scanLit)(BT_QUOT, enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_APOS:
    return PREFIX(scanLit)(BT_APOS, enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_LT:
    {
      ptr += MINBPC(enc);
      if (ptr == end)
        return XML_TOK_PARTIAL;
      switch (BYTE_TYPE(enc, ptr)) {
      case BT_EXCL:
        return PREFIX(scanDecl)(enc, ptr + MINBPC(enc), end, nextTokPtr);
      case BT_QUEST:
        return PREFIX(scanPi)(enc, ptr + MINBPC(enc), end, nextTokPtr);
      case BT_NMSTRT:
      case BT_HEX:
      case BT_NONASCII:
      case BT_LEAD2:
      case BT_LEAD3:
      case BT_LEAD4:
        *nextTokPtr = ptr - MINBPC(enc);
        return XML_TOK_INSTANCE_START;
      }
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  case BT_CR:
    if (ptr + MINBPC(enc) == end) {
      *nextTokPtr = end;
      /* indicate that this might be part of a CR/LF pair */
      return -XML_TOK_PROLOG_S;
    }
    /* fall through */
  case BT_S: case BT_LF:
    for (;;) {
      ptr += MINBPC(enc);
      if (ptr == end)
        break;
      switch (BYTE_TYPE(enc, ptr)) {
      case BT_S: case BT_LF:
        break;
      case BT_CR:
        /* don't split CR/LF pair */
        if (ptr + MINBPC(enc) != end)
          break;
        /* fall through */
      default:
        *nextTokPtr = ptr;
        return XML_TOK_PROLOG_S;
      }
    }
    *nextTokPtr = ptr;
    return XML_TOK_PROLOG_S;
  case BT_PERCNT:
    return PREFIX(scanPercent)(enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_COMMA:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_COMMA;
  case BT_LSQB:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_OPEN_BRACKET;
  case BT_RSQB:
    ptr += MINBPC(enc);
    if (ptr == end)
      return -XML_TOK_CLOSE_BRACKET;
    if (CHAR_MATCHES(enc, ptr, ASCII_RSQB)) {
      if (ptr + MINBPC(enc) == end)
        return XML_TOK_PARTIAL;
      if (CHAR_MATCHES(enc, ptr + MINBPC(enc), ASCII_GT)) {
        *nextTokPtr = ptr + 2*MINBPC(enc);
        return XML_TOK_COND_SECT_CLOSE;
      }
    }
    *nextTokPtr = ptr;
    return XML_TOK_CLOSE_BRACKET;
  case BT_LPAR:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_OPEN_PAREN;
  case BT_RPAR:
    ptr += MINBPC(enc);
    if (ptr == end)
      return -XML_TOK_CLOSE_PAREN;
    switch (BYTE_TYPE(enc, ptr)) {
    case BT_AST:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_CLOSE_PAREN_ASTERISK;
    case BT_QUEST:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_CLOSE_PAREN_QUESTION;
    case BT_PLUS:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_CLOSE_PAREN_PLUS;
    case BT_CR: case BT_LF: case BT_S:
    case BT_GT: case BT_COMMA: case BT_VERBAR:
    case BT_RPAR:
      *nextTokPtr = ptr;
      return XML_TOK_CLOSE_PAREN;
    }
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  case BT_VERBAR:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_OR;
  case BT_GT:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_DECL_CLOSE;
  case BT_NUM:
    return PREFIX(scanPoundName)(enc, ptr + MINBPC(enc), end, nextTokPtr);
#define LEAD_CASE(n) \
  case BT_LEAD ## n: \
    if (end - ptr < n) \
      return XML_TOK_PARTIAL_CHAR; \
    if (IS_NMSTRT_CHAR(enc, ptr, n)) { \
      ptr += n; \
      tok = XML_TOK_NAME; \
      break; \
    } \
    if (IS_NAME_CHAR(enc, ptr, n)) { \
      ptr += n; \
      tok = XML_TOK_NMTOKEN; \
      break; \
    } \
    *nextTokPtr = ptr; \
    return XML_TOK_INVALID;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
  case BT_NMSTRT:
  case BT_HEX:
    tok = XML_TOK_NAME;
    ptr += MINBPC(enc);
    break;
  case BT_DIGIT:
  case BT_NAME:
  case BT_MINUS:
#ifdef XML_NS
  case BT_COLON:
#endif
    tok = XML_TOK_NMTOKEN;
    ptr += MINBPC(enc);
    break;
  case BT_NONASCII:
    if (IS_NMSTRT_CHAR_MINBPC(enc, ptr)) {
      ptr += MINBPC(enc);
      tok = XML_TOK_NAME;
      break;
    }
    if (IS_NAME_CHAR_MINBPC(enc, ptr)) {
      ptr += MINBPC(enc);
      tok = XML_TOK_NMTOKEN;
      break;
    }
    /* fall through */
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
