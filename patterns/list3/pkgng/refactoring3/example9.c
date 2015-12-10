switch (BYTE_TYPE(enc, ptr)) {
    case BT_DIGIT:
    case BT_HEX:
    case BT_MINUS:
    case BT_APOS:
    case BT_LPAR:
    case BT_RPAR:
    case BT_PLUS:
    case BT_COMMA:
    case BT_SOL:
    case BT_EQUALS:
    case BT_QUEST:
    case BT_CR:
    case BT_LF:
    case BT_SEMI:
    case BT_EXCL:
    case BT_AST:
    case BT_PERCNT:
    case BT_NUM:
#ifdef XML_NS
    case BT_COLON:
#endif
      break;
    case BT_S:
      if (CHAR_MATCHES(enc, ptr, ASCII_TAB)) {
        *badPtr = ptr;
        return 0;
      }
      break;
    case BT_NAME:
    case BT_NMSTRT:
      if (!(BYTE_TO_ASCII(enc, ptr) & ~0x7f))
        break;
    default:
      switch (BYTE_TO_ASCII(enc, ptr)) {
      case 0x24: /* $ */
      case 0x40: /* @ */
        break;
      default:
        *badPtr = ptr;
        return 0;
      }
      break;
    }
