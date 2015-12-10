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

          /* Perl space used to exclude VT, but from Perl 5.18 it is included,
          which means that Perl space and POSIX space are now identical. PCRE
          was changed at release 8.34. */

          case PT_SPACE:    /* Perl space */
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
            switch(c)
              {
              HSPACE_CASES:
              VSPACE_CASES:
              if (prop_fail_result) goto ENDLOOP99;  /* Break the loop */
              break;

              default:
              if ((UCD_CATEGORY(c) == ucp_Z) == prop_fail_result)
                goto ENDLOOP99;   /* Break the loop */
              break;
              }
            eptr+= len;
            }
          ENDLOOP99:
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

          case PT_CLIST:
          for (i = min; i < max; i++)
            {
            const pcre_uint32 *cp;
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            cp = PRIV(ucd_caseless_sets) + prop_value;
            for (;;)
              {
              if (c < *cp)
                { if (prop_fail_result) break; else goto GOT_MAX; }
              if (c == *cp++)
                { if (prop_fail_result) goto GOT_MAX; else break; }
              }
            eptr += len;
            }
          GOT_MAX:
          break;

          case PT_UCNC:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLENTEST(c, eptr, len);
            if ((c == CHAR_DOLLAR_SIGN || c == CHAR_COMMERCIAL_AT ||
                 c == CHAR_GRAVE_ACCENT || (c >= 0xa0 && c <= 0xd7ff) ||
                 c >= 0xe000) == prop_fail_result)
              break;
            eptr += len;
            }
          break;

          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }

        /* eptr is now past the end of the maximum run */

        if (possessive) continue;    /* No backtracking */
        for(;;)
          {
          if (eptr == pp) goto TAIL_RECURSE;
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM44);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          eptr--;
          if (utf) BACKCHAR(eptr);
          }
        }

      /* Match extended Unicode grapheme clusters. We will get here only if the
      support is in the binary; otherwise a compile-time error occurs. */

      else if (ctype == OP_EXTUNI)
        {
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            break;
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

        /* eptr is now past the end of the maximum run */

        if (possessive) continue;    /* No backtracking */

        for(;;)
          {
          int lgb, rgb;
          PCRE_PUCHAR fptr;

          if (eptr == pp) goto TAIL_RECURSE;   /* At start of char run */
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM45);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);

          /* Backtracking over an extended grapheme cluster involves inspecting
          the previous two characters (if present) to see if a break is
          permitted between them. */

          eptr--;
          if (!utf) c = *eptr; else
            {
            BACKCHAR(eptr);
            GETCHAR(c, eptr);
            }
          rgb = UCD_GRAPHBREAK(c);

          for (;;)
            {
            if (eptr == pp) goto TAIL_RECURSE;   /* At start of char run */
            fptr = eptr - 1;
            if (!utf) c = *fptr; else
              {
              BACKCHAR(fptr);
              GETCHAR(c, fptr);
              }
            lgb = UCD_GRAPHBREAK(c);
            if ((PRIV(ucp_gbtable)[lgb] & (1 << rgb)) == 0) break;
            eptr = fptr;
            rgb = lgb;
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
                  UCHAR21(eptr) == NLBLOCK->nl[0])
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
                  UCHAR21(eptr) == NLBLOCK->nl[0])
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
            if (c == CHAR_CR)
              {
              if (++eptr >= md->end_subject) break;
              if (UCHAR21(eptr) == CHAR_LF) eptr++;
              }
            else
              {
              if (c != CHAR_LF &&
                  (md->bsr_anycrlf ||
                   (c != CHAR_VT && c != CHAR_FF && c != CHAR_NEL
#ifndef EBCDIC
                    && c != 0x2028 && c != 0x2029
#endif  /* Not EBCDIC */
                    )))
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
              HSPACE_CASES: gotspace = TRUE; break;
              default: gotspace = FALSE; break;
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
              VSPACE_CASES: gotspace = TRUE; break;
              default: gotspace = FALSE; break;
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

        if (possessive) continue;    /* No backtracking */
        for(;;)
          {
          if (eptr == pp) goto TAIL_RECURSE;
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM46);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          eptr--;
          BACKCHAR(eptr);
          if (ctype == OP_ANYNL && eptr > pp  && UCHAR21(eptr) == CHAR_NL &&
              UCHAR21(eptr - 1) == CHAR_CR) eptr--;
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
            if (c == CHAR_CR)
              {
              if (++eptr >= md->end_subject) break;
              if (*eptr == CHAR_LF) eptr++;
              }
            else
              {
              if (c != CHAR_LF && (md->bsr_anycrlf ||
                 (c != CHAR_VT && c != CHAR_FF && c != CHAR_NEL
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
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
            switch(*eptr)
              {
              default: eptr++; break;
              HSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
              HSPACE_MULTIBYTE_CASES:
#endif
              goto ENDLOOP00;
              }
            }
          ENDLOOP00:
          break;

          case OP_HSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            switch(*eptr)
              {
              default: goto ENDLOOP01;
              HSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
              HSPACE_MULTIBYTE_CASES:
#endif
              eptr++; break;
              }
            }
          ENDLOOP01:
          break;

          case OP_NOT_VSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            switch(*eptr)
              {
              default: eptr++; break;
              VSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
              VSPACE_MULTIBYTE_CASES:
#endif
              goto ENDLOOP02;
              }
            }
          ENDLOOP02:
          break;

          case OP_VSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            switch(*eptr)
              {
              default: goto ENDLOOP03;
              VSPACE_BYTE_CASES:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
              VSPACE_MULTIBYTE_CASES:
#endif
              eptr++; break;
              }
            }
          ENDLOOP03:
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

        if (possessive) continue;    /* No backtracking */
        for (;;)
          {
          if (eptr == pp) goto TAIL_RECURSE;
          RMATCH(eptr, ecode, offset_top, md, eptrb, RM47);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          eptr--;
          if (ctype == OP_ANYNL && eptr > pp  && *eptr == CHAR_LF &&
              eptr[-1] == CHAR_CR) eptr--;
          }
        }
