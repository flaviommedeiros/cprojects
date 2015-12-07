#ifdef SUPPORT_UTF8
if (utf8)
            {
            while (current_subject < end_subject &&
                   !WAS_NEWLINE(current_subject))
              {
              current_subject++;
              while(current_subject < end_subject &&
                    (*current_subject & 0xc0) == 0x80)
                current_subject++;
              }
            }
          else
#endif
          while (current_subject < end_subject && !WAS_NEWLINE(current_subject))
            current_subject++;
