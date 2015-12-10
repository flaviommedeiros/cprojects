#ifdef SUPPORT_UTF
if (utf)
        {
        register pcre_uint32 d;
        for (i = 1; i <= min; i++)
          {
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
#endif  /* SUPPORT_UTF */
      /* Not UTF mode */
        {
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject)
            {
            SCHECK_PARTIAL();
            RRETURN(MATCH_NOMATCH);
            }
          if (fc == *eptr || foc == *eptr) RRETURN(MATCH_NOMATCH);
          eptr++;
          }
        }
