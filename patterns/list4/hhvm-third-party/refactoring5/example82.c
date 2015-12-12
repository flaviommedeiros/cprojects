#ifdef SUPPORT_UTF
if (utf)
          {
          while (start_match < end_subject && !WAS_NEWLINE(start_match))
            {
            start_match++;
            ACROSSCHAR(start_match < end_subject, *start_match,
              start_match++);
            }
          }
        else
#endif
        while (start_match < end_subject && !WAS_NEWLINE(start_match))
          start_match++;
