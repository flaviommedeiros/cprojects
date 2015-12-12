#ifdef SUPPORT_UTF8
if (utf8)
      {
      while (t < md->end_subject && !IS_NEWLINE(t))
        {
        t++;
        while (t < end_subject && (*t & 0xc0) == 0x80) t++;
        }
      }
    else
#endif
    while (t < md->end_subject && !IS_NEWLINE(t)) t++;
