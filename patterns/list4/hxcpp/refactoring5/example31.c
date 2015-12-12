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

      /* We have to split the line(s) up if colouring. */

      if (do_colour)
        {
        fwrite(ptr, 1, offsets[0], stdout);
        fprintf(stdout, "%c[%sm", 0x1b, colour_string);
        fwrite(ptr + offsets[0], 1, offsets[1] - offsets[0], stdout);
        fprintf(stdout, "%c[00m", 0x1b);
        fwrite(ptr + offsets[1], 1, (linelength + endlinelength) - offsets[1],
          stdout);
        }
      else fwrite(ptr, 1, linelength + endlinelength, stdout);
