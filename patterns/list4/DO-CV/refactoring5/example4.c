#           ifdef PNG_FORMAT_AFIRST_SUPPORTED
if (format & PNG_FORMAT_FLAG_AFIRST)
               {
                  where = PNG_FILLER_BEFORE;
                  change &= ~PNG_FORMAT_FLAG_AFIRST;
               }

               else
#           endif
               where = PNG_FILLER_AFTER;
