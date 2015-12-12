#ifdef SUPPORT_UCP
if (prop_type >= 0)
        {
        switch(prop_type)
          {
          case PT_ANY:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (prop_fail_result) break;
            eptr+= len;
            }
          break;

          case PT_LAMP:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            prop_chartype = UCD_CHARTYPE(c);
            if ((prop_chartype == ucp_Lu ||
                 prop_chartype == ucp_Ll ||
                 prop_chartype == ucp_Lt) == prop_fail_result)
              break;
            eptr+= len;
            }
          break;

          case PT_GC:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            prop_category = UCD_CATEGORY(c);
            if ((prop_category == prop_value) == prop_fail_result)
              break;
            eptr+= len;
            }
          break;

          case PT_PC:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            prop_chartype = UCD_CHARTYPE(c);
            if ((prop_chartype == prop_value) == prop_fail_result)
              break;
            eptr+= len;
            }
          break;

          case PT_SC:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            prop_script = UCD_SCRIPT(c);
            if ((prop_script == prop_value) == prop_fail_result)
              break;
            eptr+= len;
            }
          break;
          }

        /* eptr is now past the end of the maximum run */

        if (possessive) continue;
        for(;;)
          {
          RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM44);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        /* Stop if tried at original pos */
          if (utf8) BACKCHAR(eptr);
          }
        }

      /* Match extended Unicode sequences. We will get here only if the
      support is in the binary; otherwise a compile-time error occurs. */

      else if (ctype == OP_EXTUNI)
        {
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject) break;
          GETCHARINCTEST(c, eptr);
          prop_category = UCD_CATEGORY(c);
          if (prop_category == ucp_M) break;
          while (eptr < md->end_subject)
            {
            int len = 1;
            if (!utf8) c = *eptr; else
              {
              GETCHARLEN(c, eptr, len);
              }
            prop_category = UCD_CATEGORY(c);
            if (prop_category != ucp_M) break;
            eptr += len;
            }
          }

        /* eptr is now past the end of the maximum run */

        if (possessive) continue;
        for(;;)
          {
          RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM45);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        /* Stop if tried at original pos */
          for (;;)                        /* Move back over one extended */
            {
            int len = 1;
            if (!utf8) c = *eptr; else
              {
              BACKCHAR(eptr);
              GETCHARLEN(c, eptr, len);
              }
            prop_category = UCD_CATEGORY(c);
            if (prop_category != ucp_M) break;
            eptr--;
            }
          }
        }

      else
#endif   /* SUPPORT_UCP */

#ifdef SUPPORT_UTF8
      /* UTF-8 mode */

      if (utf8)
        {
        switch(ctype)
          {
          case OP_ANY:
          if (max < INT_MAX)
            {
            for (i = min; i < max; i++)
              {
              if (eptr >= md->end_subject || IS_NEWLINE(eptr)) break;
              eptr++;
              while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
              }
            }

          /* Handle unlimited UTF-8 repeat */

          else
            {
            for (i = min; i < max; i++)
              {
              if (eptr >= md->end_subject || IS_NEWLINE(eptr)) break;
              eptr++;
              while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
              }
            }
          break;

          case OP_ALLANY:
          if (max < INT_MAX)
            {
            for (i = min; i < max; i++)
              {
              if (eptr >= md->end_subject) break;
              eptr++;
              while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
              }
            }
          else eptr = md->end_subject;   /* Unlimited UTF-8 repeat */
          break;

          /* The byte case is the same as non-UTF8 */

          case OP_ANYBYTE:
          c = max - min;
          if (c > (unsigned int)(md->end_subject - eptr))
            c = md->end_subject - eptr;
          eptr += c;
          break;

          case OP_ANYNL:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
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
            if (eptr >= md->end_subject) break;
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
            if (eptr >= md->end_subject) break;
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
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_digit) != 0) break;
            eptr+= len;
            }
          break;

          case OP_DIGIT:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c >= 256 ||(md->ctypes[c] & ctype_digit) == 0) break;
            eptr+= len;
            }
          break;

          case OP_NOT_WHITESPACE:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_space) != 0) break;
            eptr+= len;
            }
          break;

          case OP_WHITESPACE:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c >= 256 ||(md->ctypes[c] & ctype_space) == 0) break;
            eptr+= len;
            }
          break;

          case OP_NOT_WORDCHAR:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_word) != 0) break;
            eptr+= len;
            }
          break;

          case OP_WORDCHAR:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c >= 256 || (md->ctypes[c] & ctype_word) == 0) break;
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
          RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM46);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        /* Stop if tried at original pos */
          BACKCHAR(eptr);
          }
        }
      else
#endif  /* SUPPORT_UTF8 */

      /* Not UTF-8 mode */
        {
        switch(ctype)
          {
          case OP_ANY:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || IS_NEWLINE(eptr)) break;
            eptr++;
            }
          break;

          case OP_ALLANY:
          case OP_ANYBYTE:
          c = max - min;
          if (c > (unsigned int)(md->end_subject - eptr))
            c = md->end_subject - eptr;
          eptr += c;
          break;

          case OP_ANYNL:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject) break;
            c = *eptr;
            if (c == 0x000d)
              {
              if (++eptr >= md->end_subject) break;
              if (*eptr == 0x000a) eptr++;
              }
            else
              {
              if (c != 0x000a &&
                  (md->bsr_anycrlf ||
                    (c != 0x000b && c != 0x000c && c != 0x0085)))
                break;
              eptr++;
              }
            }
          break;

          case OP_NOT_HSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject) break;
            c = *eptr;
            if (c == 0x09 || c == 0x20 || c == 0xa0) break;
            eptr++;
            }
          break;

          case OP_HSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject) break;
            c = *eptr;
            if (c != 0x09 && c != 0x20 && c != 0xa0) break;
            eptr++;
            }
          break;

          case OP_NOT_VSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject) break;
            c = *eptr;
            if (c == 0x0a || c == 0x0b || c == 0x0c || c == 0x0d || c == 0x85)
              break;
            eptr++;
            }
          break;

          case OP_VSPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject) break;
            c = *eptr;
            if (c != 0x0a && c != 0x0b && c != 0x0c && c != 0x0d && c != 0x85)
              break;
            eptr++;
            }
          break;

          case OP_NOT_DIGIT:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_digit) != 0)
              break;
            eptr++;
            }
          break;

          case OP_DIGIT:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_digit) == 0)
              break;
            eptr++;
            }
          break;

          case OP_NOT_WHITESPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_space) != 0)
              break;
            eptr++;
            }
          break;

          case OP_WHITESPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_space) == 0)
              break;
            eptr++;
            }
          break;

          case OP_NOT_WORDCHAR:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_word) != 0)
              break;
            eptr++;
            }
          break;

          case OP_WORDCHAR:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_word) == 0)
              break;
            eptr++;
            }
          break;

          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }

        /* eptr is now past the end of the maximum run */

        if (possessive) continue;
        while (eptr >= pp)
          {
          RMATCH(eptr, ecode, offset_top, md, ims, eptrb, 0, RM47);
          eptr--;
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          }
        }
