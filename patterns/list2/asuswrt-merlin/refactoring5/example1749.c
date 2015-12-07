#ifdef SUPPORT_UTF
if (utf)
          {
          register unsigned int d;
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject)
              {
              SCHECK_PARTIAL();
              break;
              }
            GETCHARLEN(d, eptr, len);
            if (fc == d || (unsigned int)foc == d) break;
            eptr += len;
            }
          if (possessive) continue;
          for(;;)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM30);
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
            if (fc == *eptr || foc == *eptr) break;
            eptr++;
            }
          if (possessive) continue;
          while (eptr >= pp)
            {
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM31);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            eptr--;
            }
          }
