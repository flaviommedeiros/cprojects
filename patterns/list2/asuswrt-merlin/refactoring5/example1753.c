#ifdef SUPPORT_UCP
if (prop_type >= 0)
        {
        switch(prop_type)
          {
          case PT_ANY:
          if (prop_fail_result) RRETURN(MATCH_NOMATCH);
          for (i = 1; i <= min; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            }
          break;

          case PT_LAMP:
          for (i = 1; i <= min; i++)
            {
            int chartype;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            chartype = UCD_CHARTYPE(c);
            if ((chartype == ucp_Lu ||
                 chartype == ucp_Ll ||
                 chartype == ucp_Lt) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          break;

          case PT_GC:
          for (i = 1; i <= min; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((UCD_CATEGORY(c) == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          break;

          case PT_PC:
          for (i = 1; i <= min; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((UCD_CHARTYPE(c) == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          break;

          case PT_SC:
          for (i = 1; i <= min; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((UCD_SCRIPT(c) == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          break;

          case PT_ALNUM:
          for (i = 1; i <= min; i++)
            {
            int category;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            category = UCD_CATEGORY(c);
            if ((category == ucp_L || category == ucp_N) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          break;

          case PT_SPACE:    /* Perl space */
          for (i = 1; i <= min; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((UCD_CATEGORY(c) == ucp_Z || c == CHAR_HT || c == CHAR_NL ||
                 c == CHAR_FF || c == CHAR_CR)
                   == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          break;

          case PT_PXSPACE:  /* POSIX space */
          for (i = 1; i <= min; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((UCD_CATEGORY(c) == ucp_Z || c == CHAR_HT || c == CHAR_NL ||
                 c == CHAR_VT || c == CHAR_FF || c == CHAR_CR)
                   == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          break;

          case PT_WORD:
          for (i = 1; i <= min; i++)
            {
            int category;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            category = UCD_CATEGORY(c);
            if ((category == ucp_L || category == ucp_N || c == CHAR_UNDERSCORE)
                   == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          break;

          /* This should not occur */

          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }
        }

      /* Match extended Unicode sequences. We will get here only if the
      support is in the binary; otherwise a compile-time error occurs. */

      else if (ctype == OP_EXTUNI)
        {
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          GETCHARINCTEST(c, eptr);
          if (UCD_CATEGORY(c) == ucp_M) RRETURN(MATCH_NOMATCH);
          while (eptr < md->end_subject)
            {
            int len = 1;
            if (!utf) c = *eptr; else { GETCHARLEN(c, eptr, len); }
            if (UCD_CATEGORY(c) != ucp_M) break;
            eptr += len;
            }
          CHECK_PARTIAL();
          }
        }

      else
#endif     /* SUPPORT_UCP */

/* Handle all other cases when the coding is UTF-8 */

#ifdef SUPPORT_UTF
      if (utf) switch(ctype)
        {
        case OP_ANY:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (IS_NEWLINE(eptr)) RRETURN(MATCH_NOMATCH);
          if (md->partial != 0 &&
              eptr + 1 >= md->end_subject &&
              NLBLOCK->nltype == NLTYPE_FIXED &&
              NLBLOCK->nllen == 2 &&
              *eptr == NLBLOCK->nl[0])
            {
            md->hitend = TRUE;
            if (md->partial > 1) RRETURN(PCRE_ERROR_PARTIAL);
            }
          eptr++;
          ACROSSCHAR(eptr < md->end_subject, *eptr, eptr++);
          }
        break;

        case OP_ALLANY:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          eptr++;
          ACROSSCHAR(eptr < md->end_subject, *eptr, eptr++);
          }
        break;

        case OP_ANYBYTE:
        if (eptr > md->end_subject - min) RRETURN(MATCH_NOMATCH);
        eptr += min;
        break;

        case OP_ANYNL:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          GETCHARINC(c, eptr);
          switch(c)
            {
            default: RRETURN(MATCH_NOMATCH);

            case 0x000d:
            if (eptr < md->end_subject && *eptr == 0x0a) eptr++;
            break;

            case 0x000a:
            break;

            case 0x000b:
            case 0x000c:
            case 0x0085:
            case 0x2028:
            case 0x2029:
            if (md->bsr_anycrlf) RRETURN(MATCH_NOMATCH);
            break;
            }
          }
        break;

        case OP_NOT_HSPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          GETCHARINC(c, eptr);
          switch(c)
            {
            default: break;
            case 0x09:      /* HT */
            case 0x20:      /* SPACE */
            case 0xa0:      /* NBSP */
            case 0x1680:    /* OGHAM SPACE MARK */
            case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
            case 0x2000:    /* EN QUAD */
            case 0x2001:    /* EM QUAD */
            case 0x2002:    /* EN SPACE */
            case 0x2003:    /* EM SPACE */
            case 0x2004:    /* THREE-PER-EM SPACE */
            case 0x2005:    /* FOUR-PER-EM SPACE */
            case 0x2006:    /* SIX-PER-EM SPACE */
            case 0x2007:    /* FIGURE SPACE */
            case 0x2008:    /* PUNCTUATION SPACE */
            case 0x2009:    /* THIN SPACE */
            case 0x200A:    /* HAIR SPACE */
            case 0x202f:    /* NARROW NO-BREAK SPACE */
            case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
            case 0x3000:    /* IDEOGRAPHIC SPACE */
            RRETURN(MATCH_NOMATCH);
            }
          }
        break;

        case OP_HSPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          GETCHARINC(c, eptr);
          switch(c)
            {
            default: RRETURN(MATCH_NOMATCH);
            case 0x09:      /* HT */
            case 0x20:      /* SPACE */
            case 0xa0:      /* NBSP */
            case 0x1680:    /* OGHAM SPACE MARK */
            case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
            case 0x2000:    /* EN QUAD */
            case 0x2001:    /* EM QUAD */
            case 0x2002:    /* EN SPACE */
            case 0x2003:    /* EM SPACE */
            case 0x2004:    /* THREE-PER-EM SPACE */
            case 0x2005:    /* FOUR-PER-EM SPACE */
            case 0x2006:    /* SIX-PER-EM SPACE */
            case 0x2007:    /* FIGURE SPACE */
            case 0x2008:    /* PUNCTUATION SPACE */
            case 0x2009:    /* THIN SPACE */
            case 0x200A:    /* HAIR SPACE */
            case 0x202f:    /* NARROW NO-BREAK SPACE */
            case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
            case 0x3000:    /* IDEOGRAPHIC SPACE */
            break;
            }
          }
        break;

        case OP_NOT_VSPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          GETCHARINC(c, eptr);
          switch(c)
            {
            default: break;
            case 0x0a:      /* LF */
            case 0x0b:      /* VT */
            case 0x0c:      /* FF */
            case 0x0d:      /* CR */
            case 0x85:      /* NEL */
            case 0x2028:    /* LINE SEPARATOR */
            case 0x2029:    /* PARAGRAPH SEPARATOR */
            RRETURN(MATCH_NOMATCH);
            }
          }
        break;

        case OP_VSPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          GETCHARINC(c, eptr);
          switch(c)
            {
            default: RRETURN(MATCH_NOMATCH);
            case 0x0a:      /* LF */
            case 0x0b:      /* VT */
            case 0x0c:      /* FF */
            case 0x0d:      /* CR */
            case 0x85:      /* NEL */
            case 0x2028:    /* LINE SEPARATOR */
            case 0x2029:    /* PARAGRAPH SEPARATOR */
            break;
            }
          }
        break;

        case OP_NOT_DIGIT:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          GETCHARINC(c, eptr);
          if (c < 128 && (md->ctypes[c] & ctype_digit) != 0)
            RRETURN(MATCH_NOMATCH);
          }
        break;

        case OP_DIGIT:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (*eptr >= 128 || (md->ctypes[*eptr] & ctype_digit) == 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          /* No need to skip more bytes - we know it's a 1-byte character */
          }
        break;

        case OP_NOT_WHITESPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (*eptr < 128 && (md->ctypes[*eptr] & ctype_space) != 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          ACROSSCHAR(eptr < md->end_subject, *eptr, eptr++);
          }
        break;

        case OP_WHITESPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (*eptr >= 128 || (md->ctypes[*eptr] & ctype_space) == 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          /* No need to skip more bytes - we know it's a 1-byte character */
          }
        break;

        case OP_NOT_WORDCHAR:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (*eptr < 128 && (md->ctypes[*eptr] & ctype_word) != 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          ACROSSCHAR(eptr < md->end_subject, *eptr, eptr++);
          }
        break;

        case OP_WORDCHAR:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (*eptr >= 128 || (md->ctypes[*eptr] & ctype_word) == 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          /* No need to skip more bytes - we know it's a 1-byte character */
          }
        break;

        default:
        RRETURN(PCRE_ERROR_INTERNAL);
        }  /* End switch(ctype) */

      else
#endif     /* SUPPORT_UTF */

      /* Code for the non-UTF-8 case for minimum matching of operators other
      than OP_PROP and OP_NOTPROP. */

      switch(ctype)
        {
        case OP_ANY:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (IS_NEWLINE(eptr)) RRETURN(MATCH_NOMATCH);
          if (md->partial != 0 &&
              eptr + 1 >= md->end_subject &&
              NLBLOCK->nltype == NLTYPE_FIXED &&
              NLBLOCK->nllen == 2 &&
              *eptr == NLBLOCK->nl[0])
            {
            md->hitend = TRUE;
            if (md->partial > 1) RRETURN(PCRE_ERROR_PARTIAL);
            }
          eptr++;
          }
        break;

        case OP_ALLANY:
        if (eptr > md->end_subject - min)
          {
          SCHECK_PARTIAL();
          RRETURN(MATCH_NOMATCH);
          }
        eptr += min;
        break;

        case OP_ANYBYTE:
        if (eptr > md->end_subject - min)
          {
          SCHECK_PARTIAL();
          RRETURN(MATCH_NOMATCH);
          }
        eptr += min;
        break;

        case OP_ANYNL:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          switch(*eptr++)
            {
            default: RRETURN(MATCH_NOMATCH);

            case 0x000d:
            if (eptr < md->end_subject && *eptr == 0x0a) eptr++;
            break;

            case 0x000a:
            break;

            case 0x000b:
            case 0x000c:
            case 0x0085:
#ifdef COMPILE_PCRE16
            case 0x2028:
            case 0x2029:
#endif
            if (md->bsr_anycrlf) RRETURN(MATCH_NOMATCH);
            break;
            }
          }
        break;

        case OP_NOT_HSPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          switch(*eptr++)
            {
            default: break;
            case 0x09:      /* HT */
            case 0x20:      /* SPACE */
            case 0xa0:      /* NBSP */
#ifdef COMPILE_PCRE16
            case 0x1680:    /* OGHAM SPACE MARK */
            case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
            case 0x2000:    /* EN QUAD */
            case 0x2001:    /* EM QUAD */
            case 0x2002:    /* EN SPACE */
            case 0x2003:    /* EM SPACE */
            case 0x2004:    /* THREE-PER-EM SPACE */
            case 0x2005:    /* FOUR-PER-EM SPACE */
            case 0x2006:    /* SIX-PER-EM SPACE */
            case 0x2007:    /* FIGURE SPACE */
            case 0x2008:    /* PUNCTUATION SPACE */
            case 0x2009:    /* THIN SPACE */
            case 0x200A:    /* HAIR SPACE */
            case 0x202f:    /* NARROW NO-BREAK SPACE */
            case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
            case 0x3000:    /* IDEOGRAPHIC SPACE */
#endif
            RRETURN(MATCH_NOMATCH);
            }
          }
        break;

        case OP_HSPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          switch(*eptr++)
            {
            default: RRETURN(MATCH_NOMATCH);
            case 0x09:      /* HT */
            case 0x20:      /* SPACE */
            case 0xa0:      /* NBSP */
#ifdef COMPILE_PCRE16
            case 0x1680:    /* OGHAM SPACE MARK */
            case 0x180e:    /* MONGOLIAN VOWEL SEPARATOR */
            case 0x2000:    /* EN QUAD */
            case 0x2001:    /* EM QUAD */
            case 0x2002:    /* EN SPACE */
            case 0x2003:    /* EM SPACE */
            case 0x2004:    /* THREE-PER-EM SPACE */
            case 0x2005:    /* FOUR-PER-EM SPACE */
            case 0x2006:    /* SIX-PER-EM SPACE */
            case 0x2007:    /* FIGURE SPACE */
            case 0x2008:    /* PUNCTUATION SPACE */
            case 0x2009:    /* THIN SPACE */
            case 0x200A:    /* HAIR SPACE */
            case 0x202f:    /* NARROW NO-BREAK SPACE */
            case 0x205f:    /* MEDIUM MATHEMATICAL SPACE */
            case 0x3000:    /* IDEOGRAPHIC SPACE */
#endif
            break;
            }
          }
        break;

        case OP_NOT_VSPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          switch(*eptr++)
            {
            default: break;
            case 0x0a:      /* LF */
            case 0x0b:      /* VT */
            case 0x0c:      /* FF */
            case 0x0d:      /* CR */
            case 0x85:      /* NEL */
#ifdef COMPILE_PCRE16
            case 0x2028:    /* LINE SEPARATOR */
            case 0x2029:    /* PARAGRAPH SEPARATOR */
#endif
            RRETURN(MATCH_NOMATCH);
            }
          }
        break;

        case OP_VSPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          switch(*eptr++)
            {
            default: RRETURN(MATCH_NOMATCH);
            case 0x0a:      /* LF */
            case 0x0b:      /* VT */
            case 0x0c:      /* FF */
            case 0x0d:      /* CR */
            case 0x85:      /* NEL */
#ifdef COMPILE_PCRE16
            case 0x2028:    /* LINE SEPARATOR */
            case 0x2029:    /* PARAGRAPH SEPARATOR */
#endif
            break;
            }
          }
        break;

        case OP_NOT_DIGIT:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (MAX_255(*eptr) && (md->ctypes[*eptr] & ctype_digit) != 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          }
        break;

        case OP_DIGIT:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (!MAX_255(*eptr) || (md->ctypes[*eptr] & ctype_digit) == 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          }
        break;

        case OP_NOT_WHITESPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (MAX_255(*eptr) && (md->ctypes[*eptr] & ctype_space) != 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          }
        break;

        case OP_WHITESPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (!MAX_255(*eptr) || (md->ctypes[*eptr] & ctype_space) == 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          }
        break;

        case OP_NOT_WORDCHAR:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (MAX_255(*eptr) && (md->ctypes[*eptr] & ctype_word) != 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          }
        break;

        case OP_WORDCHAR:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (!MAX_255(*eptr) || (md->ctypes[*eptr] & ctype_word) == 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          }
        break;

        default:
        RRETURN(PCRE_ERROR_INTERNAL);
        }
