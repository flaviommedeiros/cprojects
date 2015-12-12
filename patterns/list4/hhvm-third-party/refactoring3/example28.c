switch(list_ptr[0])
      {
      case OP_CHAR:
      ochr_ptr = list_ptr + 2;
      do
        {
        if (chr == *ochr_ptr) return FALSE;
        ochr_ptr++;
        }
      while(*ochr_ptr != NOTACHAR);
      break;

      case OP_NOT:
      ochr_ptr = list_ptr + 2;
      do
        {
        if (chr == *ochr_ptr)
          break;
        ochr_ptr++;
        }
      while(*ochr_ptr != NOTACHAR);
      if (*ochr_ptr == NOTACHAR) return FALSE;   /* Not found */
      break;

      /* Note that OP_DIGIT etc. are generated only when PCRE_UCP is *not*
      set. When it is set, \d etc. are converted into OP_(NOT_)PROP codes. */

      case OP_DIGIT:
      if (chr < 256 && (cd->ctypes[chr] & ctype_digit) != 0) return FALSE;
      break;

      case OP_NOT_DIGIT:
      if (chr > 255 || (cd->ctypes[chr] & ctype_digit) == 0) return FALSE;
      break;

      case OP_WHITESPACE:
      if (chr < 256 && (cd->ctypes[chr] & ctype_space) != 0) return FALSE;
      break;

      case OP_NOT_WHITESPACE:
      if (chr > 255 || (cd->ctypes[chr] & ctype_space) == 0) return FALSE;
      break;

      case OP_WORDCHAR:
      if (chr < 255 && (cd->ctypes[chr] & ctype_word) != 0) return FALSE;
      break;

      case OP_NOT_WORDCHAR:
      if (chr > 255 || (cd->ctypes[chr] & ctype_word) == 0) return FALSE;
      break;

      case OP_HSPACE:
      switch(chr)
        {
        HSPACE_CASES: return FALSE;
        default: break;
        }
      break;

      case OP_NOT_HSPACE:
      switch(chr)
        {
        HSPACE_CASES: break;
        default: return FALSE;
        }
      break;

      case OP_ANYNL:
      case OP_VSPACE:
      switch(chr)
        {
        VSPACE_CASES: return FALSE;
        default: break;
        }
      break;

      case OP_NOT_VSPACE:
      switch(chr)
        {
        VSPACE_CASES: break;
        default: return FALSE;
        }
      break;

      case OP_DOLL:
      case OP_EODN:
      switch (chr)
        {
        case CHAR_CR:
        case CHAR_LF:
        case CHAR_VT:
        case CHAR_FF:
        case CHAR_NEL:
#ifndef EBCDIC
        case 0x2028:
        case 0x2029:
#endif  /* Not EBCDIC */
        return FALSE;
        }
      break;

      case OP_EOD:    /* Can always possessify before \z */
      break;

#ifdef SUPPORT_UCP
      case OP_PROP:
      case OP_NOTPROP:
      if (!check_char_prop(chr, list_ptr[2], list_ptr[3],
            list_ptr[0] == OP_NOTPROP))
        return FALSE;
      break;
#endif

      case OP_NCLASS:
      if (chr > 255) return FALSE;
      /* Fall through */

      case OP_CLASS:
      if (chr > 255) break;
      class_bitset = (pcre_uint8 *)
        ((list_ptr == list ? code : base_end) - list_ptr[2]);
      if ((class_bitset[chr >> 3] & (1 << (chr & 7))) != 0) return FALSE;
      break;

#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
      case OP_XCLASS:
      if (PRIV(xclass)(chr, (list_ptr == list ? code : base_end) -
          list_ptr[2] + LINK_SIZE, utf)) return FALSE;
      break;
#endif

      default:
      return FALSE;
      }
