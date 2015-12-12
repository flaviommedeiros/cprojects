switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
    case BT_GT: case BT_RPAR: case BT_COMMA:
    case BT_VERBAR: case BT_LSQB: case BT_PERCNT:
    case BT_S: case BT_CR: case BT_LF:
      *nextTokPtr = ptr;
      return tok;
#ifdef XML_NS
    case BT_COLON:
      ptr += MINBPC(enc);
      switch (tok) {
      case XML_TOK_NAME:
        if (ptr == end)
          return XML_TOK_PARTIAL;
        tok = XML_TOK_PREFIXED_NAME;
        switch (BYTE_TYPE(enc, ptr)) {
        CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
        default:
          tok = XML_TOK_NMTOKEN;
          break;
        }
        break;
      case XML_TOK_PREFIXED_NAME:
        tok = XML_TOK_NMTOKEN;
        break;
      }
      break;
#endif
    case BT_PLUS:
      if (tok == XML_TOK_NMTOKEN)  {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_NAME_PLUS;
    case BT_AST:
      if (tok == XML_TOK_NMTOKEN)  {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_NAME_ASTERISK;
    case BT_QUEST:
      if (tok == XML_TOK_NMTOKEN)  {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_NAME_QUESTION;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
