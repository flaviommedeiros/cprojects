#ifdef HAVE_THREADS
if (g_settings.video.threaded && !g_extern.system.hw_render_callback.context_type) // Can't do hardware rendering with threaded driver currently.
   {
      find_video_driver(); // Need to grab the "real" video driver interface on a reinit.
      RARCH_LOG("Starting threaded video driver ...\n");
      if (!rarch_threaded_video_init(&driver.video, &driver.video_data,
               &driver.input, &driver.input_data,
               driver.video, &video))
      {
         RARCH_ERR("Cannot open threaded video driver ... Exiting ...\n");
         rarch_fail(1, "init_video_input()");
      }
   }
   else
#endif
      driver.video_data = video_init_func(&video, &driver.input, &driver.input_data);
