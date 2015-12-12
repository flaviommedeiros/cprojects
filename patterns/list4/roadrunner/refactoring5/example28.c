#ifdef SUPPORT_UTF8
if (utf8)
      {
      length = 1;
      ecode++;
      GETCHARLEN(fc, ecode, length);
      if (length > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
      while (length-- > 0) if (*ecode++ != *eptr++) RRETURN(MATCH_NOMATCH);
      }
    else
#endif

    /* Non-UTF-8 mode */
      {
      if (md->end_subject - eptr < 1) RRETURN(MATCH_NOMATCH);
      if (ecode[1] != *eptr++) RRETURN(MATCH_NOMATCH);
      ecode += 2;
      }
