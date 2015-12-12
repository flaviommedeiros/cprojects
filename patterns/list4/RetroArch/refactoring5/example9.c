#ifdef HAVE_MULTIMAN
if (g_extern.lifecycle_mode_state & (1ULL << MODE_EXITSPAWN_MULTIMAN))
   {
      RARCH_LOG("Boot Multiman: %s.\n", MULTIMAN_SELF_FILE);
      strlcpy(core_launch, MULTIMAN_SELF_FILE, sizeof(core_launch));
   }
   else
#endif
   strlcpy(core_launch, g_settings.libretro, sizeof(core_launch));
