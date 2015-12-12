switch (c)
      {
      case '\n':    /* LF */
      case '\v':    /* VT */
      case '\f':    /* FF */
      case '\r':    /* CR */
#ifndef EBCDIE
      case 0x85:    /* Unicode NEL */
      case 0x2028:  /* Unicode LS */
      case 0x2029:  /* Unicode PS */
#endif  /* Not EBCDIC */
      return p;

      default:
      break;
      }
