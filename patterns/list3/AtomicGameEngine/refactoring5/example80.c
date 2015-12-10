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

          /* Perl space used to exclude VT, but from Perl 5.18 it is included,
          which means that Perl space and POSIX space are now identical. PCRE
          was changed at release 8.34. */

          case PT_SPACE:    /* Perl space */
          case PT_PXSPACE:  /* POSIX space */
          for (i = 1; i <= min; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            switch(c)
              {
              HSPACE_CASES:
              VSPACE_CASES:
              if (prop_fail_result) RRETURN(MATCH_NOMATCH);
              break;

              default:
              if ((UCD_CATEGORY(c) == ucp_Z) == prop_fail_result)
                RRETURN(MATCH_NOMATCH);
              break;
              }
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

          case PT_CLIST:
          for (i = 1; i <= min; i++)
            {
            const pcre_uint32 *cp;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            cp = PRIV(ucd_caseless_sets) + prop_value;
            for (;;)
              {
              if (c < *cp)
                { if (prop_fail_result) break; else { RRETURN(MATCH_NOMATCH); } }
              if (c == *cp++)
                { if (prop_fail_result) { RRETURN(MATCH_NOMATCH); } else break; }
              }
            }
          break;

          case PT_UCNC:
          for (i = 1; i <= min; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((c == CHAR_DOLLAR_SIGN || c == CHAR_COMMERCIAL_AT ||
                 c == CHAR_GRAVE_ACCENT || (c >= 0xa0 && c <= 0xd7ff) ||
                 c >= 0xe000) == prop_fail_result)
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
          else
            {
            int lgb, rgb;
            GETCHARINCTEST(c, eptr);
            lgb = UCD_GRAPHBREAK(c);
           while (eptr < md->end_subject)
              {
              int len = 1;
              if (!utf) c = *eptr; else { GETCHARLEN(c, eptr, len); }
              rgb = UCD_GRAPHBREAK(c);
              if ((PRIV(ucp_gbtable)[lgb] & (1 << rgb)) == 0) break;
              lgb = rgb;
              eptr += len;
              }
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
              UCHAR21(eptr) == NLBLOCK->nl[0])
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

            case CHAR_CR:
            if (eptr < md->end_subject && UCHAR21(eptr) == CHAR_LF) eptr++;
            break;

            case CHAR_LF:
            break;

            case CHAR_VT:
            case CHAR_FF:
            case CHAR_NEL:
#ifndef EBCDIC
            case 0x2028:
            case 0x2029:
#endif  /* Not EBCDIC */
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
            HSPACE_CASES: RRETURN(MATCH_NOMATCH);  /* Byte and multibyte cases */
            default: break;
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
            HSPACE_CASES: break;  /* Byte and multibyte cases */
            default: RRETURN(MATCH_NOMATCH);
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
            VSPACE_CASES: RRETURN(MATCH_NOMATCH);
            default: break;
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
            VSPACE_CASES: break;
            default: RRETURN(MATCH_NOMATCH);
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
          pcre_uint32 cc;
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          cc = UCHAR21(eptr);
          if (cc >= 128 || (md->ctypes[cc] & ctype_digit) == 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          /* No need to skip more bytes - we know it's a 1-byte character */
          }
        break;

        case OP_NOT_WHITESPACE:
        for (i = 1; i <= min; i++)
          {
          pcre_uint32 cc;
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          cc = UCHAR21(eptr);
          if (cc < 128 && (md->ctypes[cc] & ctype_space) != 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          ACROSSCHAR(eptr < md->end_subject, *eptr, eptr++);
          }
        break;

        case OP_WHITESPACE:
        for (i = 1; i <= min; i++)
          {
          pcre_uint32 cc;
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          cc = UCHAR21(eptr);
          if (cc >= 128 || (md->ctypes[cc] & ctype_space) == 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          /* No need to skip more bytes - we know it's a 1-byte character */
          }
        break;

        case OP_NOT_WORDCHAR:
        for (i = 1; i <= min; i++)
          {
          pcre_uint32 cc;
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          cc = UCHAR21(eptr);
          if (cc < 128 && (md->ctypes[cc] & ctype_word) != 0)
            RRETURN(MATCH_NOMATCH);
          eptr++;
          ACROSSCHAR(eptr < md->end_subject, *eptr, eptr++);
          }
        break;

        case OP_WORDCHAR:
        for (i = 1; i <= min; i++)
          {
          pcre_uint32 cc;
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          cc = UCHAR21(eptr);
          if (cc >= 128 || (md->ctypes[cc] & ctype_word) == 0)
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

            case CHAR_CR:
            if (eptr < md->end_subject && *eptr == CHAR_LF) eptr++;
            break;

            case CHAR_LF:
            break;

            case CHAR_VT:
            case CHAR_FF:
            case CHAR_NEL:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
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
            HSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
            HSPACE_MULTIBYTE_CASES:
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
            HSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
            HSPACE_MULTIBYTE_CASES:
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
            VSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
            VSPACE_MULTIBYTE_CASES:
#endif
            RRETURN(MATCH_NOMATCH);
            default: break;
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
            VSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
            VSPACE_MULTIBYTE_CASES:
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
