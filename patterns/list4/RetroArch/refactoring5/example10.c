#ifdef HAVE_NETPLAY
if (!g_extern.netplay)
   {
#endif
#if !defined(RARCH_PERFORMANCE_MODE)
      check_pause();
      check_oneshot();

      if (check_fullscreen() && g_extern.is_paused)
         rarch_render_cached_frame();

      if (g_extern.is_paused && !g_extern.is_oneshot)
         return;
#endif

      check_fast_forward_button();

      check_stateslots();
#ifdef HAVE_BSV_MOVIE
      check_savestates(g_extern.bsv.movie);
#else
      check_savestates(false);
#endif

      check_rewind();
      check_slowmotion();

#ifdef HAVE_BSV_MOVIE
      check_movie();
#endif
     
      check_shader_dir();
      check_cheats();
      check_disk();

#ifdef HAVE_DYLIB
      check_dsp_config();
#endif
      check_reset();
#ifdef HAVE_NETPLAY
   }
   else
   {
      check_netplay_flip();
#if !defined(RARCH_PERFORMANCE_MODE)
      check_fullscreen();
#endif
   }
