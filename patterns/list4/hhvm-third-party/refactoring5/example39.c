#ifdef SUPPORT_PCRE16
if (pcre_mode == PCRE16_MODE)
        {
#ifndef NOUTF
        if (use_utf)
          {
          if (c > 0x10ffffu)
            {
            fprintf(outfile, "** Failed: character \\x{%x} is greater than "
              "0x10ffff and so cannot be converted to UTF-16\n", c);
            goto NEXT_DATA;
            }
          else if (c >= 0x10000u)
            {
            c-= 0x10000u;
            *q16++ = 0xD800 | (c >> 10);
            *q16++ = 0xDC00 | (c & 0x3ff);
            }
          else
            *q16++ = c;
          }
        else
#endif
          {
          if (c > 0xffffu)
            {
            fprintf(outfile, "** Character \\x{%x} is greater than 0xffff "
              "and UTF-16 mode is not enabled.\n", c);
            fprintf(outfile, "** Truncation will probably give the wrong "
              "result.\n");
            }

          *q16++ = c;
          }
        }
