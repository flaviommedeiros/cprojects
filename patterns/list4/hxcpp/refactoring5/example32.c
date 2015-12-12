#ifdef SUPPORT_LIBZ
if (frtype == FR_LIBZ)
      bufflength = 2*MBUFTHIRD +
        gzread (ingz, buffer + 2*MBUFTHIRD, MBUFTHIRD);
    else
#endif

#ifdef SUPPORT_LIBBZ2
    if (frtype == FR_LIBBZ2)
      bufflength = 2*MBUFTHIRD +
        BZ2_bzread(inbz2, buffer + 2*MBUFTHIRD, MBUFTHIRD);
    else
#endif

    bufflength = 2*MBUFTHIRD + fread(buffer + 2*MBUFTHIRD, 1, MBUFTHIRD, in);
