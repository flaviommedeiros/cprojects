switch (BYTE_TYPE(enc, ptr1)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: \
      if (*ptr1++ != *ptr2++) \
        return 0;
    LEAD_CASE(4) LEAD_CASE(3) LEAD_CASE(2)
#undef LEAD_CASE
      /* fall through */
      if (*ptr1++ != *ptr2++)
        return 0;
      break;
    case BT_NONASCII:
    case BT_NMSTRT:
#ifdef XML_NS
    case BT_COLON:
#endif
    case BT_HEX:
    case BT_DIGIT:
    case BT_NAME:
    case BT_MINUS:
      if (*ptr2++ != *ptr1++)
        return 0;
      if (MINBPC(enc) > 1) {
        if (*ptr2++ != *ptr1++)
          return 0;
        if (MINBPC(enc) > 2) {
          if (*ptr2++ != *ptr1++)
            return 0;
          if (MINBPC(enc) > 3) {
            if (*ptr2++ != *ptr1++)
              return 0;
          }
        }
      }
      break;
    default:
      if (MINBPC(enc) == 1 && *ptr1 == *ptr2)
        return 1;
      switch (BYTE_TYPE(enc, ptr2)) {
      case BT_LEAD2:
      case BT_LEAD3:
      case BT_LEAD4:
      case BT_NONASCII:
      case BT_NMSTRT:
#ifdef XML_NS
      case BT_COLON:
#endif
      case BT_HEX:
      case BT_DIGIT:
      case BT_NAME:
      case BT_MINUS:
        return 0;
      default:
        return 1;
      }
    }
