#ifdef JFRIEDL_DEBUG
if (S_arg >= 0 && S_arg < mrc)
        {
        int first = S_arg * 2;
        int last  = first + 1;
        FWRITE(ptr, 1, offsets[first], stdout);
        fprintf(stdout, "X");
        FWRITE(ptr + offsets[last], 1, linelength - offsets[last], stdout);
        }
      else
#endif

      /* We have to split the line(s) up if colouring, and search for further
      matches, but not of course if the line is a non-match. */

      if (do_colour && !invert)
        {
        int plength;
        FWRITE(ptr, 1, offsets[0], stdout);
        fprintf(stdout, "%c[%sm", 0x1b, colour_string);
        FWRITE(ptr + offsets[0], 1, offsets[1] - offsets[0], stdout);
        fprintf(stdout, "%c[00m", 0x1b);
        for (;;)
          {
          startoffset = offsets[1];
          if (startoffset >= (int)linelength + endlinelength ||
              !match_patterns(matchptr, length, options, startoffset, offsets,
                &mrc))
            break;
          FWRITE(matchptr + startoffset, 1, offsets[0] - startoffset, stdout);
          fprintf(stdout, "%c[%sm", 0x1b, colour_string);
          FWRITE(matchptr + offsets[0], 1, offsets[1] - offsets[0], stdout);
          fprintf(stdout, "%c[00m", 0x1b);
          }

        /* In multiline mode, we may have already printed the complete line
        and its line-ending characters (if they matched the pattern), so there
        may be no more to print. */

        plength = (int)((linelength + endlinelength) - startoffset);
        if (plength > 0) FWRITE(ptr + startoffset, 1, plength, stdout);
        }

      /* Not colouring; no need to search for further matches */

      else FWRITE(ptr, 1, linelength + endlinelength, stdout);
