#ifdef SUPPORT_UTF
if (utf)
          {
          register pcre_uint32 d;
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
          if (possessive) continue;    /* No backtracking */
          for(;;)
            {
            if (eptr == pp) goto TAIL_RECURSE;
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM30);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            eptr--;
            BACKCHAR(eptr);
            }
          }
        else
#endif  /* SUPPORT_UTF */
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
          if (possessive) continue;    /* No backtracking */
          for (;;)
            {
            if (eptr == pp) goto TAIL_RECURSE;
            RMATCH(eptr, ecode, offset_top, md, eptrb, RM31);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            eptr--;
            }
          }
