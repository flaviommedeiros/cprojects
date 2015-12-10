#ifdef SUPPORT_UTF
if (utf)
          {
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(c, eptr, len);
            if (c > 255)
              {
              if (op == OP_CLASS) break;
              }
            else
              if ((BYTE_MAP[c/8] & (1 << (c&7))) == 0) break;
            eptr += len;
            }

          if (possessive) continue;    /* No backtracking */

          for (;;)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM18);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (eptr-- == pp) break;        /* Stop if tried at original pos */
            BACKCHAR(eptr);
            }
          }
        else
#endif
          /* Not UTF mode */
          {
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            c = *eptr;
#ifndef COMPILE_PCRE8
            if (c > 255)
              {
              if (op == OP_CLASS) break;
              }
            else
#endif
              if ((BYTE_MAP[c/8] & (1 << (c&7))) == 0) break;
            eptr++;
            }

          if (possessive) continue;    /* No backtracking */

          while (eptr >= pp)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM19);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            eptr--;
            }
          }
