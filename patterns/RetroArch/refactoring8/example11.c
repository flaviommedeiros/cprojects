static const record_driver_t *record_drivers[] = {
#ifdef HAVE_FFMPEG
   &ffemu_ffmpeg,
#endif
   &ffemu_null,
   NULL,
};
