switch(*pos) {
    case 'd':
    case 'i':
      flags |= CONV_INTEGER | RADIX_DECIMAL | SIGNED_YES;
      break;
    case 'u':
      flags |= CONV_INTEGER | RADIX_DECIMAL | SIGNED_NO;
      break;
    case 'o':
      flags |= CONV_INTEGER | RADIX_OCTAL | SIGNED_NO;
      break;
    case 'x':
      flags |= CONV_INTEGER | RADIX_HEX | SIGNED_NO;
      break;
    case 'X':
      flags |= CONV_INTEGER | RADIX_HEX | SIGNED_NO | CAPS_YES;
      break;
#ifdef HAVE_DOUBLE
    case 'f':
      flags |= CONV_FLOAT | FLOAT_NORMAL;
      break;
    case 'F':
      flags |= CONV_FLOAT | FLOAT_NORMAL | CAPS_YES;
      break;
    case 'e':
      flags |= CONV_FLOAT | FLOAT_EXPONENT;
      break;
    case 'E':
      flags |= CONV_FLOAT | FLOAT_EXPONENT | CAPS_YES;
      break;
    case 'g':
      flags |= CONV_FLOAT | FLOAT_DEPENDANT;
      break;
    case 'G':
      flags |= CONV_FLOAT | FLOAT_DEPENDANT | CAPS_YES;
      break;
    case 'a':
      flags |= CONV_FLOAT | FLOAT_HEX;
      break;
    case 'A':
      flags |= CONV_FLOAT | FLOAT_HEX | CAPS_YES;
      break;
#endif
    case 'c':
      flags |= CONV_CHAR;
      break;
    case 's':
      flags |= CONV_STRING;
      break;
    case 'p':
      flags |= CONV_POINTER;
      break;
    case 'n':
      flags |= CONV_WRITTEN;
      break;
    case '%':
      flags |= CONV_PERCENT;
      break;
    case '\0':
      va_end(ap);
      return written;
    }
