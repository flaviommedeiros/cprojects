#ifdef SUPPORT_UTF
if (utf)
          {
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM16);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINC(c, eptr);
            if (c > 255)
              {
              if (op == OP_CLASS) RRETURN(MATCH_NOMATCH);
              }
            else
              if ((BYTE_MAP[c/8] & (1 << (c&7))) == 0) RRETURN(MATCH_NOMATCH);
            }
          }
        else
#endif
        /* Not UTF mode */
          {
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM17);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            c = *eptr++;
#ifndef COMPILE_PCRE8
            if (c > 255)
              {
              if (op == OP_CLASS) RRETURN(MATCH_NOMATCH);
              }
            else
#endif
              if ((BYTE_MAP[c/8] & (1 << (c&7))) == 0) RRETURN(MATCH_NOMATCH);
            }
          }
