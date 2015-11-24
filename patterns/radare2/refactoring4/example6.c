#ifndef MODE_USTAR
if (hd.magic != MAGIC_BCPIO)
#else
  if (grub_memcmp (hd.magic, MAGIC_USTAR,
		   sizeof (MAGIC_USTAR) - 1))
#endif
    goto fail;
