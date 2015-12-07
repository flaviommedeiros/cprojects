#ifdef SUPPORT_UTF
if (utf)
        {
        for (i = 1; i <= min; i++)
          {
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
        for (i = 1; i <= min; i++)
          {
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
