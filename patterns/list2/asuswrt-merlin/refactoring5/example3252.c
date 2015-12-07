#ifdef SUPPORT_LIBBZ2
if (frtype == FR_LIBBZ2)
      bufflength = 2*bufthird +
        BZ2_bzread(inbz2, main_buffer + 2*bufthird, bufthird);
    else
#endif

    bufflength = 2*bufthird +
      (input_line_buffered?
       read_one_line(main_buffer + 2*bufthird, bufthird, in) :
       fread(main_buffer + 2*bufthird, 1, bufthird, in));
