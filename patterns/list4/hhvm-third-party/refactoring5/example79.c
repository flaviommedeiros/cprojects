#ifdef SUPPORT_UCP
if (prop_type >= 0)
        {
        switch(prop_type)
          {
          case PT_ANY:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM36);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if (prop_fail_result) RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_LAMP:
          for (fi = min;; fi++)
            {
            int chartype;
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM37);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
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
          /* Control never gets here */

          case PT_GC:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM38);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((UCD_CATEGORY(c) == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_PC:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM39);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((UCD_CHARTYPE(c) == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_SC:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM40);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            if ((UCD_SCRIPT(c) == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_ALNUM:
          for (fi = min;; fi++)
            {
            int category;
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM59);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
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
          /* Control never gets here */

          /* Perl space used to exclude VT, but from Perl 5.18 it is included,
          which means that Perl space and POSIX space are now identical. PCRE
          was changed at release 8.34. */

          case PT_SPACE:    /* Perl space */
          case PT_PXSPACE:  /* POSIX space */
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM61);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
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
          /* Control never gets here */

          case PT_WORD:
          for (fi = min;; fi++)
            {
            int category;
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM62);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINCTEST(c, eptr);
            category = UCD_CATEGORY(c);
            if ((category == ucp_L ||
                 category == ucp_N ||
                 c == CHAR_UNDERSCORE)
                   == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_CLIST:
          for (fi = min;; fi++)
            {
            const pcre_uint32 *cp;
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM67);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
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
          /* Control never gets here */

          case PT_UCNC:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM60);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
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
          /* Control never gets here */

          /* This should never occur */
          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }
        }

      /* Match extended Unicode sequences. We will get here only if the
      support is in the binary; otherwise a compile-time error occurs. */

      else if (ctype == OP_EXTUNI)
        {
        for (fi = min;; fi++)
          {
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM41);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max) RRETURN(MATCH_NOMATCH);
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

#ifdef SUPPORT_UTF
      if (utf)
        {
        for (fi = min;; fi++)
          {
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM42);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max) RRETURN(MATCH_NOMATCH);
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (ctype == OP_ANY && IS_NEWLINE(eptr))
            RRETURN(MATCH_NOMATCH);
          GETCHARINC(c, eptr);
          switch(ctype)
            {
            case OP_ANY:               /* This is the non-NL case */
            if (md->partial != 0 &&    /* Take care with CRLF partial */
                eptr >= md->end_subject &&
                NLBLOCK->nltype == NLTYPE_FIXED &&
                NLBLOCK->nllen == 2 &&
                c == NLBLOCK->nl[0])
              {
              md->hitend = TRUE;
              if (md->partial > 1) RRETURN(PCRE_ERROR_PARTIAL);
              }
            break;

            case OP_ALLANY:
            case OP_ANYBYTE:
            break;

            case OP_ANYNL:
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
            break;

            case OP_NOT_HSPACE:
            switch(c)
              {
              HSPACE_CASES: RRETURN(MATCH_NOMATCH);
              default: break;
              }
            break;

            case OP_HSPACE:
            switch(c)
              {
              HSPACE_CASES: break;
              default: RRETURN(MATCH_NOMATCH);
              }
            break;

            case OP_NOT_VSPACE:
            switch(c)
              {
              VSPACE_CASES: RRETURN(MATCH_NOMATCH);
              default: break;
              }
            break;

            case OP_VSPACE:
            switch(c)
              {
              VSPACE_CASES: break;
              default: RRETURN(MATCH_NOMATCH);
              }
            break;

            case OP_NOT_DIGIT:
            if (c < 256 && (md->ctypes[c] & ctype_digit) != 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_DIGIT:
            if (c >= 256 || (md->ctypes[c] & ctype_digit) == 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WHITESPACE:
            if (c < 256 && (md->ctypes[c] & ctype_space) != 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_WHITESPACE:
            if (c >= 256 || (md->ctypes[c] & ctype_space) == 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WORDCHAR:
            if (c < 256 && (md->ctypes[c] & ctype_word) != 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_WORDCHAR:
            if (c >= 256 || (md->ctypes[c] & ctype_word) == 0)
              RRETURN(MATCH_NOMATCH);
            break;

            default:
            RRETURN(PCRE_ERROR_INTERNAL);
            }
          }
        }
      else
#endif
      /* Not UTF mode */
        {
        for (fi = min;; fi++)
          {
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM43);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max) RRETURN(MATCH_NOMATCH);
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (ctype == OP_ANY && IS_NEWLINE(eptr))
            RRETURN(MATCH_NOMATCH);
          c = *eptr++;
          switch(ctype)
            {
            case OP_ANY:               /* This is the non-NL case */
            if (md->partial != 0 &&    /* Take care with CRLF partial */
                eptr >= md->end_subject &&
                NLBLOCK->nltype == NLTYPE_FIXED &&
                NLBLOCK->nllen == 2 &&
                c == NLBLOCK->nl[0])
              {
              md->hitend = TRUE;
              if (md->partial > 1) RRETURN(PCRE_ERROR_PARTIAL);
              }
            break;

            case OP_ALLANY:
            case OP_ANYBYTE:
            break;

            case OP_ANYNL:
            switch(c)
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
            break;

            case OP_NOT_HSPACE:
            switch(c)
              {
              default: break;
              HSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
              HSPACE_MULTIBYTE_CASES:
#endif
              RRETURN(MATCH_NOMATCH);
              }
            break;

            case OP_HSPACE:
            switch(c)
              {
              default: RRETURN(MATCH_NOMATCH);
              HSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
              HSPACE_MULTIBYTE_CASES:
#endif
              break;
              }
            break;

            case OP_NOT_VSPACE:
            switch(c)
              {
              default: break;
              VSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
              VSPACE_MULTIBYTE_CASES:
#endif
              RRETURN(MATCH_NOMATCH);
              }
            break;

            case OP_VSPACE:
            switch(c)
              {
              default: RRETURN(MATCH_NOMATCH);
              VSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
              VSPACE_MULTIBYTE_CASES:
#endif
              break;
              }
            break;

            case OP_NOT_DIGIT:
            if (MAX_255(c) && (md->ctypes[c] & ctype_digit) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_DIGIT:
            if (!MAX_255(c) || (md->ctypes[c] & ctype_digit) == 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WHITESPACE:
            if (MAX_255(c) && (md->ctypes[c] & ctype_space) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_WHITESPACE:
            if (!MAX_255(c) || (md->ctypes[c] & ctype_space) == 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WORDCHAR:
            if (MAX_255(c) && (md->ctypes[c] & ctype_word) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_WORDCHAR:
            if (!MAX_255(c) || (md->ctypes[c] & ctype_word) == 0) RRETURN(MATCH_NOMATCH);
            break;

            default:
            RRETURN(PCRE_ERROR_INTERNAL);
            }
          }
        }
