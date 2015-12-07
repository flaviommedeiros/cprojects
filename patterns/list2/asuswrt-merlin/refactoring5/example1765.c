#ifdef SUPPORT_UTF
if (utf)
        {
        while (t < md->end_subject && !IS_NEWLINE(t))
          {
          t++;
          ACROSSCHAR(t < end_subject, *t, t++);
          }
        }
      else
#endif
      while (t < md->end_subject && !IS_NEWLINE(t)) t++;
