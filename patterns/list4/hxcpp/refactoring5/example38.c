#ifdef SUPPORT_UCP
if (md->utf8)
    {
    USPTR endptr = eptr + length;
    while (eptr < endptr)
      {
      int c, d;
      GETCHARINC(c, eptr);
      GETCHARINC(d, p);
      if (c != d && c != UCD_OTHERCASE(d)) return FALSE;
      }
    }
  else
#endif
#endif

  /* The same code works when not in UTF-8 mode and in UTF-8 mode when there
  is no UCP support. */

  while (length-- > 0)
    { if (md->lcc[*p++] != md->lcc[*eptr++]) return FALSE; }
