static cfg_opt_t sec_audio[] =
  {
    CFG_STR("nickname", "Computer", CFGF_NONE),
    CFG_STR("type", NULL, CFGF_NONE),
#ifdef __linux__
    CFG_STR("card", "default", CFGF_NONE),
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
    CFG_STR("card", "/dev/dsp", CFGF_NONE),
#endif
    CFG_STR("mixer", NULL, CFGF_NONE),
    CFG_END()
  };
