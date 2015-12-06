static const struct strtab tab[] = {
    { N_("Not set"),                       -1 },
    { N_("Matroska (mkv)"),                MC_MATROSKA, },
    { N_("Same as source (pass through)"), MC_PASS, },
#if ENABLE_LIBAV
    { N_("MPEG-TS"),                       MC_MPEGTS },
    { N_("MPEG-PS (DVD)"),                 MC_MPEGPS },
#endif
  };
