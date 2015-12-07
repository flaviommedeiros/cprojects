#if WEBP_ENCODER_ABI_VERSION > 0x0204
if (config->preprocessing < 0 || config->preprocessing > 7)
#else
  if (config->preprocessing < 0 || config->preprocessing > 3)
#endif
    return 0;
