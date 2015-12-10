#ifdef SUPPORT_UTF
if (utf)
      {
      length = 1;
      ecode++;
      GETCHARLEN(fc, ecode, length);
      if (length > md->end_subject - eptr)
        {
        CHECK_PARTIAL();             /* Not SCHECK_PARTIAL() */
        RRETURN(MATCH_NOMATCH);
        }
      while (length-- > 0) if (*ecode++ != UCHAR21INC(eptr)) RRETURN(MATCH_NOMATCH);
      }
    else
#endif
    /* Not UTF mode */
      {
      if (md->end_subject - eptr < 1)
        {
        SCHECK_PARTIAL();            /* This one can use SCHECK_PARTIAL() */
        RRETURN(MATCH_NOMATCH);
        }
      if (ecode[1] != *eptr++) RRETURN(MATCH_NOMATCH);
      ecode += 2;
      }
