#ifdef SUPPORT_UCP
if (prop_type >= 0)
        {
        switch(prop_type)
          {
          case PT_ANY:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM36);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINC(c, eptr);
            if (prop_fail_result) RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_LAMP:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM37);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINC(c, eptr);
            prop_chartype = UCD_CHARTYPE(c);
            if ((prop_chartype == ucp_Lu ||
                 prop_chartype == ucp_Ll ||
                 prop_chartype == ucp_Lt) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_GC:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM38);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINC(c, eptr);
            prop_category = UCD_CATEGORY(c);
            if ((prop_category == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_PC:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM39);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINC(c, eptr);
            prop_chartype = UCD_CHARTYPE(c);
            if ((prop_chartype == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

          case PT_SC:
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM40);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINC(c, eptr);
            prop_script = UCD_SCRIPT(c);
            if ((prop_script == prop_value) == prop_fail_result)
              RRETURN(MATCH_NOMATCH);
            }
          /* Control never gets here */

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
          RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM41);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max) RRETURN(MATCH_NOMATCH);
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          GETCHARINCTEST(c, eptr);
          prop_category = UCD_CATEGORY(c);
          if (prop_category == ucp_M) RRETURN(MATCH_NOMATCH);
          while (eptr < md->end_subject)
            {
            int len = 1;
            if (!utf8) c = *eptr;
              else { GETCHARLEN(c, eptr, len); }
            prop_category = UCD_CATEGORY(c);
            if (prop_category != ucp_M) break;
            eptr += len;
            }
          }
        }

      else
#endif     /* SUPPORT_UCP */

#ifdef SUPPORT_UTF8
      /* UTF-8 mode */
      if (utf8)
        {
        for (fi = min;; fi++)
          {
          RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM42);
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
            case OP_ANY:        /* This is the non-NL case */
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
            if  (c >= 256 || (md->ctypes[c] & ctype_space) == 0)
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
      /* Not UTF-8 mode */
        {
        for (fi = min;; fi++)
          {
          RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM43);
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
            case OP_ANY:     /* This is the non-NL case */
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
              break;
              }
            break;

            case OP_NOT_DIGIT:
            if ((md->ctypes[c] & ctype_digit) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_DIGIT:
            if ((md->ctypes[c] & ctype_digit) == 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WHITESPACE:
            if ((md->ctypes[c] & ctype_space) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_WHITESPACE:
            if  ((md->ctypes[c] & ctype_space) == 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WORDCHAR:
            if ((md->ctypes[c] & ctype_word) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_WORDCHAR:
            if ((md->ctypes[c] & ctype_word) == 0) RRETURN(MATCH_NOMATCH);
            break;

            default:
            RRETURN(PCRE_ERROR_INTERNAL);
            }
          }
        }
