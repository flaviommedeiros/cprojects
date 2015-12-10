#ifdef SUPPORT_UTF
if (utf)
            {
            while (current_subject < end_subject &&
                   !WAS_NEWLINE(current_subject))
              {
              current_subject++;
              ACROSSCHAR(current_subject < end_subject, *current_subject,
                current_subject++);
              }
            }
          else
#endif
          while (current_subject < end_subject && !WAS_NEWLINE(current_subject))
            current_subject++;
