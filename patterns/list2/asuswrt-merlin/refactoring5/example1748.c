#ifdef SUPPORT_UTF
if (utf)
          {
          register unsigned int d;
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM28);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            GETCHARINC(d, eptr);
            if (fc == d || (unsigned int)foc == d) RRETURN(MATCH_NOMATCH);
            }
          }
        else
#endif
        /* Not UTF mode */
          {
          for (fi = min;; fi++)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM29);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max) RRETURN(MATCH_NOMATCH);
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              RRETURN(MATCH_NOMATCH);
              }
            if (fc == *eptr || foc == *eptr) RRETURN(MATCH_NOMATCH);
            eptr++;
            }
          }
