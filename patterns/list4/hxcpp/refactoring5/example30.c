#ifdef SUPPORT_LIBBZ2
if (frtype == FR_LIBBZ2)
  {
  inbz2 = (BZFILE *)handle;
  bufflength = BZ2_bzread(inbz2, buffer, 3*MBUFTHIRD);
  if ((int)bufflength < 0) return 2;   /* Gotcha: bufflength is size_t; */
  }                                    /* without the cast it is unsigned. */
else
#endif

  {
  in = (FILE *)handle;
  bufflength = fread(buffer, 1, 3*MBUFTHIRD, in);
  }
