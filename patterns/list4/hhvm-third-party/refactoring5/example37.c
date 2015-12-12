#ifdef SUPPORT_PCRE8
if (pcre_mode == PCRE8_MODE)
        {
#ifndef NOUTF
        if (use_utf)
          {
          if (c > 0x7fffffff)
            {
            fprintf(outfile, "** Character \\x{%x} is greater than 0x7fffffff "
              "and so cannot be converted to UTF-8\n", c);
            goto NEXT_DATA;
            }
          q8 += ord2utf8(c, q8);
          }
        else
#endif
          {
          if (c > 0xffu)
            {
            fprintf(outfile, "** Character \\x{%x} is greater than 255 "
              "and UTF-8 mode is not enabled.\n", c);
            fprintf(outfile, "** Truncation will probably give the wrong "
              "result.\n");
            }
          *q8++ = c;
          }
        }
