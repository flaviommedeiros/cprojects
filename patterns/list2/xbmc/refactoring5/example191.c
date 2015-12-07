#ifdef SUPPORT_UTF8
if (utf8)
          {
          while (start_match < end_subject && !WAS_NEWLINE(start_match))
            {
            start_match++;
            while(start_match < end_subject && (*start_match & 0xc0) == 0x80)
              start_match++;
            }
          }
        else
#endif
        while (start_match < end_subject && !WAS_NEWLINE(start_match))
          start_match++;
