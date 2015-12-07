#ifdef WCHAR
if (pos < 0 || pos > csize1 + csize2)
#else /* BYTE */
  if (pos < 0 || pos > size1 + size2)
#endif
    {
      FREE_VARIABLES ();
      return -1;
    }
