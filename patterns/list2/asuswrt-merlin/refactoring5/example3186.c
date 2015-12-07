#ifdef SUPPORT_UCP
if (md->utf)
    {
    /* Match characters up to the end of the reference. NOTE: the number of
    bytes matched may differ, because there are some characters whose upper and
    lower case versions code as different numbers of bytes. For example, U+023A
    (2 bytes in UTF-8) is the upper case version of U+2C65 (3 bytes in UTF-8);
    a sequence of 3 of the former uses 6 bytes, as does a sequence of two of
    the latter. It is important, therefore, to check the length along the
    reference, not along the subject (earlier code did this wrong). */

    PCRE_PUCHAR endptr = p + length;
    while (p < endptr)
      {
      int c, d;
      if (eptr >= md->end_subject) return -2;   /* Partial match */
      GETCHARINC(c, eptr);
      GETCHARINC(d, p);
      if (c != d && c != UCD_OTHERCASE(d)) return -1;
      }
    }
  else
#endif
#endif

  /* The same code works when not in UTF-8 mode and in UTF-8 mode when there
  is no UCP support. */
    {
    while (length-- > 0)
      {
      if (eptr >= md->end_subject) return -2;   /* Partial match */
      if (TABLE_GET(*p, md->lcc, *p) != TABLE_GET(*eptr, md->lcc, *eptr)) return -1;
      p++;
      eptr++;
      }
    }
