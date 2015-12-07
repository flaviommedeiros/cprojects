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

          case PT_SPACE:    /* Perl space */
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
            if ((UCD_CATEGORY(c) == ucp_Z || c == CHAR_HT || c == CHAR_NL ||
                 c == CHAR_FF || c == CHAR_CR)
                   == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

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
            if ((UCD_CATEGORY(c) == ucp_Z || c == CHAR_HT || c == CHAR_NL ||
                 c == CHAR_VT || c == CHAR_FF || c == CHAR_CR)
                   == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
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
            break;

            case OP_NOT_HSPACE:
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
            break;

            case OP_HSPACE:
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
            break;

            case OP_NOT_VSPACE:
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
            break;

            case OP_VSPACE:
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
            break;

            case OP_NOT_HSPACE:
            switch(c)
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
            break;

            case OP_HSPACE:
            switch(c)
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
            break;

            case OP_NOT_VSPACE:
            switch(c)
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
            break;

            case OP_VSPACE:
            switch(c)
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
