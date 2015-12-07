#ifdef SUPPORT_UCP
if (prop_type >= 0)
        {
        switch(prop_type)
          {
          case PT_ANY:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            if (prop_fail_result) break;
            eptr+= len;
            }
          break;

          case PT_LAMP:
          for (i = min; i < max; i++)
            {
            int chartype;
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            chartype = UCD_CHARTYPE(c);
            if ((chartype == ucp_Lu ||
                 chartype == ucp_Ll ||
                 chartype == ucp_Lt) == prop_fail_result)
              break;
            eptr+= len;
            }
          break;

          case PT_GC:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            if ((UCD_CATEGORY(c) == prop_value) == prop_fail_result) break;
            eptr+= len;
            }
          break;

          case PT_PC:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            if ((UCD_CHARTYPE(c) == prop_value) == prop_fail_result) break;
            eptr+= len;
            }
          break;

          case PT_SC:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            if ((UCD_SCRIPT(c) == prop_value) == prop_fail_result) break;
            eptr+= len;
            }
          break;

          case PT_ALNUM:
          for (i = min; i < max; i++)
            {
            int category;
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            category = UCD_CATEGORY(c);
            if ((category == ucp_L || category == ucp_N) == prop_fail_result)
              break;
            eptr+= len;
            }
          break;

          case PT_SPACE:    /* Perl space */
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            if ((UCD_CATEGORY(c) == ucp_Z || c == CHAR_HT || c == CHAR_NL ||
                 c == CHAR_FF || c == CHAR_CR)
                 == prop_fail_result)
              break;
            eptr+= len;
            }
          break;

          case PT_PXSPACE:  /* POSIX space */
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            if ((UCD_CATEGORY(c) == ucp_Z || c == CHAR_HT || c == CHAR_NL ||
                 c == CHAR_VT || c == CHAR_FF || c == CHAR_CR)
                 == prop_fail_result)
              break;
            eptr+= len;
            }
          break;

          case PT_WORD:
          for (i = min; i < max; i++)
            {
            int category;
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            category = UCD_CATEGORY(c);
            if ((category == ucp_L || category == ucp_N ||
                 c == CHAR_UNDERSCORE) == prop_fail_result)
              break;
            eptr+= len;
            }
          break;

          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }

        /* eptr is now past the end of the maximum run */

        if (possessive) continue;
        for(;;)
          {
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM44);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        /* Stop if tried at original pos */
          if (utf) BACKCHAR(eptr);
          }
        }

      /* Match extended Unicode sequences. We will get here only if the
      support is in the binary; otherwise a compile-time error occurs. */

      else if (ctype == OP_EXTUNI)
        {
        for (i = min; i < max; i++)
          {
          int len = 1;
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            break;
            }
          if (!utf) c = *eptr; else { GETCHARLEN(c, eptr, len); }
          if (UCD_CATEGORY(c) == ucp_M) break;
          eptr += len;
          while (eptr < md->end_subject)
            {
            len = 1;
            if (!utf) c = *eptr; else { GETCHARLEN(c, eptr, len); }
            if (UCD_CATEGORY(c) != ucp_M) break;
            eptr += len;
            }
          CHECK_PARTIAL();
          }

        /* eptr is now past the end of the maximum run */

        if (possessive) continue;

        for(;;)
          {
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM45);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        /* Stop if tried at original pos */
          for (;;)                        /* Move back over one extended */
            {
            if (!utf) c = *eptr; else
              {
              BACKCHAR(eptr);
              GETCHAR(c, eptr);
              }
            if (UCD_CATEGORY(c) != ucp_M) break;
            eptr--;
            }
          }
        }

      else
#endif   /* SUPPORT_UCP */

#ifdef SUPPORT_UTF
      if (utf)
        {
        switch(ctype)
          {
          case OP_ANY:
          if (max < INT_MAX)
            {
            for (i = min; i < max; i++)
              {
              if (eptr >= md->end_subject)
                {
                SCHECK_PARTIAL();
                break;
                }
              if (IS_NEWLINE(eptr)) break;
              if (md->partial != 0 &&    /* Take care with CRLF partial */
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
            }

          /* Handle unlimited UTF-8 repeat */

          else
            {
            for (i = min; i < max; i++)
              {
              if (eptr >= md->end_subject)
                {
                SCHECK_PARTIAL();
                break;
                }
              if (IS_NEWLINE(eptr)) break;
              if (md->partial != 0 &&    /* Take care with CRLF partial */
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
            }
          break;

          case OP_ALLANY:
          if (max < INT_MAX)
            {
            for (i = min; i < max; i++)
              {
              if (eptr >= md->end_subject)
                {
                SCHECK_PARTIAL();
                break;
                }
              eptr++;
              ACROSSCHAR(eptr < md->end_subject, *eptr, eptr++);
              }
            }
          else
            {
            eptr = md->end_subject;   /* Unlimited UTF-8 repeat */
            SCHECK_PARTIAL();
            }
          break;

          /* The byte case is the same as non-UTF8 */

          case OP_ANYBYTE:
          c = max - min;
          if (c > (unsigned int)(md->end_subject - eptr))
            {
            eptr = md->end_subject;
            SCHECK_PARTIAL();
            }
          else eptr += c;
          break;

          case OP_ANYNL:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            if (c == 0x000d)
              {
              if (++eptr >= md->end_subject) break;
              if (*eptr == 0x000a) eptr++;
              }
            else
              {
              if (c != 0x000a &&
                  (md->bsr_anycrlf ||
                   (c != 0x000b && c != 0x000c &&
                    c != 0x0085 && c != 0x2028 && c != 0x2029)))
                break;
              eptr += len;
              }
            }
          break;

          case OP_NOT_HSPACE:
          case OP_HSPACE:
          for (i = min; i < max; i++)
            {
            BOOL gotspace;
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            switch(c)
              {
              default: gotspace = FALSE; break;
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
              gotspace = TRUE;
              break;
              }
            if (gotspace == (ctype == OP_NOT_HSPACE)) break;
            eptr += len;
            }
          break;

          case OP_NOT_VSPACE:
          case OP_VSPACE:
          for (i = min; i < max; i++)
            {
            BOOL gotspace;
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            switch(c)
              {
              default: gotspace = FALSE; break;
              case 0x0a:      /* LF */
              case 0x0b:      /* VT */
              case 0x0c:      /* FF */
              case 0x0d:      /* CR */
              case 0x85:      /* NEL */
              case 0x2028:    /* LINE SEPARATOR */
              case 0x2029:    /* PARAGRAPH SEPARATOR */
              gotspace = TRUE;
              break;
              }
            if (gotspace == (ctype == OP_NOT_VSPACE)) break;
            eptr += len;
            }
          break;

          case OP_NOT_DIGIT:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_digit) != 0) break;
            eptr+= len;
            }
          break;

          case OP_DIGIT:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            if (c >= 256 ||(md->ctypes[c] & ctype_digit) == 0) break;
            eptr+= len;
            }
          break;

          case OP_NOT_WHITESPACE:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_space) != 0) break;
            eptr+= len;
            }
          break;

          case OP_WHITESPACE:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            if (c >= 256 ||(md->ctypes[c] & ctype_space) == 0) break;
            eptr+= len;
            }
          break;

          case OP_NOT_WORDCHAR:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_word) != 0) break;
            eptr+= len;
            }
          break;

          case OP_WORDCHAR:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            if (c >= 256 || (md->ctypes[c] & ctype_word) == 0) break;
            eptr+= len;
            }
          break;

          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }

        /* eptr is now past the end of the maximum run. If possessive, we are
        done (no backing up). Otherwise, match at this position; anything other
        than no match is immediately returned. For nomatch, back up one
        character, unless we are matching \R and the last thing matched was
        \r\n, in which case, back up two bytes. */

        if (possessive) continue;
        for(;;)
          {
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM46);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        /* Stop if tried at original pos */
          BACKCHAR(eptr);
          if (ctype == OP_ANYNL && eptr > pp  && *eptr == '\n' &&
              eptr[-1] == '\r') eptr--;
          }
        }
      else
#endif  /* SUPPORT_UTF */
      /* Not UTF mode */
        {
        switch(ctype)
          {
          case OP_ANY:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            if (IS_NEWLINE(eptr)) break;
            if (md->partial != 0 &&    /* Take care with CRLF partial */
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
          case OP_ANYBYTE:
          c = max - min;
          if (c > (unsigned int)(md->end_subject - eptr))
            {
            eptr = md->end_subject;
            SCHECK_PARTIAL();
            }
          else eptr += c;
          break;

          case OP_ANYNL:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            c = *eptr;
            if (c == 0x000d)
              {
              if (++eptr >= md->end_subject) break;
              if (*eptr == 0x000a) eptr++;
              }
            else
              {
              if (c != 0x000a && (md->bsr_anycrlf ||
                (c != 0x000b && c != 0x000c && c != 0x0085
#ifdef COMPILE_PCRE16
                && c != 0x2028 && c != 0x2029
#endif
                ))) break;
              eptr++;
              }
            }
          break;

          case OP_NOT_HSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            c = *eptr;
            if (c == 0x09 || c == 0x20 || c == 0xa0
#ifdef COMPILE_PCRE16
              || c == 0x1680 || c == 0x180e || (c >= 0x2000 && c <= 0x200A)
              || c == 0x202f || c == 0x205f || c == 0x3000
#endif
              ) break;
            eptr++;
            }
          break;

          case OP_HSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            c = *eptr;
            if (c != 0x09 && c != 0x20 && c != 0xa0
#ifdef COMPILE_PCRE16
              && c != 0x1680 && c != 0x180e && (c < 0x2000 || c > 0x200A)
              && c != 0x202f && c != 0x205f && c != 0x3000
#endif
              ) break;
            eptr++;
            }
          break;

          case OP_NOT_VSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            c = *eptr;
            if (c == 0x0a || c == 0x0b || c == 0x0c || c == 0x0d || c == 0x85
#ifdef COMPILE_PCRE16
              || c == 0x2028 || c == 0x2029
#endif
              ) break;
            eptr++;
            }
          break;

          case OP_VSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            c = *eptr;
            if (c != 0x0a && c != 0x0b && c != 0x0c && c != 0x0d && c != 0x85
#ifdef COMPILE_PCRE16
              && c != 0x2028 && c != 0x2029
#endif
              ) break;
            eptr++;
            }
          break;

          case OP_NOT_DIGIT:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            if (MAX_255(*eptr) && (md->ctypes[*eptr] & ctype_digit) != 0) break;
            eptr++;
            }
          break;

          case OP_DIGIT:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            if (!MAX_255(*eptr) || (md->ctypes[*eptr] & ctype_digit) == 0) break;
            eptr++;
            }
          break;

          case OP_NOT_WHITESPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            if (MAX_255(*eptr) && (md->ctypes[*eptr] & ctype_space) != 0) break;
            eptr++;
            }
          break;

          case OP_WHITESPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            if (!MAX_255(*eptr) || (md->ctypes[*eptr] & ctype_space) == 0) break;
            eptr++;
            }
          break;

          case OP_NOT_WORDCHAR:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            if (MAX_255(*eptr) && (md->ctypes[*eptr] & ctype_word) != 0) break;
            eptr++;
            }
          break;

          case OP_WORDCHAR:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            if (!MAX_255(*eptr) || (md->ctypes[*eptr] & ctype_word) == 0) break;
            eptr++;
            }
          break;

          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }

        /* eptr is now past the end of the maximum run. If possessive, we are
        done (no backing up). Otherwise, match at this position; anything other
        than no match is immediately returned. For nomatch, back up one
        character (byte), unless we are matching \R and the last thing matched
        was \r\n, in which case, back up two bytes. */

        if (possessive) continue;
        while (eptr >= pp)
          {
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM47);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          eptr--;
          if (ctype == OP_ANYNL && eptr > pp  && *eptr == '\n' &&
              eptr[-1] == '\r') eptr--;
          }
        }
