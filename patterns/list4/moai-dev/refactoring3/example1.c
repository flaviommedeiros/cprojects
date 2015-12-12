switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
    case BT_S: case BT_CR: case BT_LF:
      for (ptr += MINBPC(enc); ptr != end; ptr += MINBPC(enc)) {
        switch (BYTE_TYPE(enc, ptr)) {
        case BT_S: case BT_CR: case BT_LF:
          break;
        case BT_GT:
          *nextTokPtr = ptr + MINBPC(enc);
          return XML_TOK_END_TAG;
        default:
          *nextTokPtr = ptr;
          return XML_TOK_INVALID;
        }
      }
      return XML_TOK_PARTIAL;
#ifdef XML_NS
    case BT_COLON:
      /* no need to check qname syntax here,
         since end-tag must match exactly */
      ptr += MINBPC(enc);
      break;
#endif
    case BT_GT:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_END_TAG;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
