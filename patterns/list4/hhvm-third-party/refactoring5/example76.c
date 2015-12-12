#ifdef SUPPORT_UTF
if (utf)
          {
          register pcre_uint32 d;
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM32);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINC(d, eptr);
            if (fc == d) RRETURN(MATCH_NOMATCH);
            }
          }
        else
#endif
        /* Not UTF mode */
          {
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM33);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            if (fc == *eptr++) RRETURN(MATCH_NOMATCH);
            }
          }
