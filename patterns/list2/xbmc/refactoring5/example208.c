#ifdef JFRIEDL_DEBUG
if (S_arg >= 0 && S_arg < mrc)
        {
        int first = S_arg * 2;
        int last  = first + 1;
        fwrite(ptr, 1, offsets[first], stdout);
        fprintf(stdout, "X");
        fwrite(ptr + offsets[last], 1, linelength - offsets[last], stdout);
        }
      else
#endif

      /* We have to split the line(s) up if colouring, and search for further
      matches. */

      if (do_colour)
        {
        int last_offset = 0;
        fwrite(ptr, 1, offsets[0], stdout);
        fprintf(stdout, "%c[%sm", 0x1b, colour_string);
        fwrite(ptr + offsets[0], 1, offsets[1] - offsets[0], stdout);
        fprintf(stdout, "%c[00m", 0x1b);
        for (;;)
          {
          last_offset += offsets[1];
          matchptr += offsets[1];
          length -= offsets[1];
          if (!match_patterns(matchptr, length, offsets, &mrc)) break;
          fwrite(matchptr, 1, offsets[0], stdout);
          fprintf(stdout, "%c[%sm", 0x1b, colour_string);
          fwrite(matchptr + offsets[0], 1, offsets[1] - offsets[0], stdout);
          fprintf(stdout, "%c[00m", 0x1b);
          }
        fwrite(ptr + last_offset, 1, (linelength + endlinelength) - last_offset,
          stdout);
        }

      /* Not colouring; no need to search for further matches */

      else fwrite(ptr, 1, linelength + endlinelength, stdout);
