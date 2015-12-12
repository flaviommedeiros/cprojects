switch (c)
      {
      case '\n':    /* LF */
      case '\v':    /* VT */
      case '\f':    /* FF */
      *lenptr = 1;
      return p;

      case '\r':    /* CR */
      if (p < endptr && *p == '\n')
        {
        *lenptr = 2;
        p++;
        }
      else *lenptr = 1;
      return p;

#ifndef EBCDIC
      case 0x85:    /* Unicode NEL */
      *lenptr = utf8? 2 : 1;
      return p;

      case 0x2028:  /* Unicode LS */
      case 0x2029:  /* Unicode PS */
      *lenptr = 3;
      return p;
#endif  /* Not EBCDIC */

      default:
      break;
      }
