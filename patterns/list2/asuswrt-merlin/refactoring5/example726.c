#ifdef SUPPORT_LIBBZ2
if (frtype == FR_LIBBZ2)
  {
  inbz2 = (BZFILE *)handle;
  bufflength = BZ2_bzread(inbz2, main_buffer, bufsize);
  if ((int)bufflength < 0) return 2;   /* Gotcha: bufflength is size_t; */
  }                                    /* without the cast it is unsigned. */
else
#endif

  {
  in = (FILE *)handle;
  if (is_file_tty(in)) input_line_buffered = TRUE;
  bufflength = input_line_buffered?
    read_one_line(main_buffer, bufsize, in) :
    fread(main_buffer, 1, bufsize, in);
  }
