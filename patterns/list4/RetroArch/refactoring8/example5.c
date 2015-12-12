const char drive_mappings[][32] = {
#if defined(_XBOX1)
   "C:",
   "D:",
   "E:",
   "F:",
   "G:"
#elif defined(__CELLOS_LV2__)
   "/app_home/",
   "/dev_hdd0/",
   "/dev_hdd1/",
   "/host_root/"
#endif
};
