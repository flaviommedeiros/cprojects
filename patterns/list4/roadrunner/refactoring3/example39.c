switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
#ifdef XML_NS
    case BT_COLON:
      if (hadColon) {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      hadColon = 1;
      ptr += MINBPC(enc);
      if (ptr == end)
        return XML_TOK_PARTIAL;
      switch (BYTE_TYPE(enc, ptr)) {
      CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
      default:
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      break;
#endif
    case BT_S: case BT_CR: case BT_LF:
      for (;;) {
        int t;

        ptr += MINBPC(enc);
        if (ptr == end)
          return XML_TOK_PARTIAL;
        t = BYTE_TYPE(enc, ptr);
        if (t == BT_EQUALS)
          break;
        switch (t) {
        case BT_S:
        case BT_LF:
        case BT_CR:
          break;
        default:
          *nextTokPtr = ptr;
          return XML_TOK_INVALID;
        }
      }
    /* fall through */
    case BT_EQUALS:
      {
        int open;
#ifdef XML_NS
        hadColon = 0;
#endif
        for (;;) {
          ptr += MINBPC(enc);
          if (ptr == end)
            return XML_TOK_PARTIAL;
          open = BYTE_TYPE(enc, ptr);
          if (open == BT_QUOT || open == BT_APOS)
            break;
          switch (open) {
          case BT_S:
          case BT_LF:
          case BT_CR:
            break;
          default:
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          }
        }
        ptr += MINBPC(enc);
        /* in attribute value */
        for (;;) {
          int t;
          if (ptr == end)
            return XML_TOK_PARTIAL;
          t = BYTE_TYPE(enc, ptr);
          if (t == open)
            break;
          switch (t) {
          INVALID_CASES(ptr, nextTokPtr)
          case BT_AMP:
            {
              int tok = PREFIX(scanRef)(enc, ptr + MINBPC(enc), end, &ptr);
              if (tok <= 0) {
                if (tok == XML_TOK_INVALID)
                  *nextTokPtr = ptr;
                return tok;
              }
              break;
            }
          case BT_LT:
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          default:
            ptr += MINBPC(enc);
            break;
          }
        }
        ptr += MINBPC(enc);
        if (ptr == end)
          return XML_TOK_PARTIAL;
        switch (BYTE_TYPE(enc, ptr)) {
        case BT_S:
        case BT_CR:
        case BT_LF:
          break;
        case BT_SOL:
          goto sol;
        case BT_GT:
          goto gt;
        default:
          *nextTokPtr = ptr;
          return XML_TOK_INVALID;
        }
        /* ptr points to closing quote */
        for (;;) {
          ptr += MINBPC(enc);
          if (ptr == end)
            return XML_TOK_PARTIAL;
          switch (BYTE_TYPE(enc, ptr)) {
          CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
          case BT_S: case BT_CR: case BT_LF:
            continue;
          case BT_GT:
          gt:
            *nextTokPtr = ptr + MINBPC(enc);
            return XML_TOK_START_TAG_WITH_ATTS;
          case BT_SOL:
          sol:
            ptr += MINBPC(enc);
            if (ptr == end)
              return XML_TOK_PARTIAL;
            if (!CHAR_MATCHES(enc, ptr, ASCII_GT)) {
              *nextTokPtr = ptr;
              return XML_TOK_INVALID;
            }
            *nextTokPtr = ptr + MINBPC(enc);
            return XML_TOK_EMPTY_ELEMENT_WITH_ATTS;
          default:
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          }
          break;
        }
        break;
      }
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
