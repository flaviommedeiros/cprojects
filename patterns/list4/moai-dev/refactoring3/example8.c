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
