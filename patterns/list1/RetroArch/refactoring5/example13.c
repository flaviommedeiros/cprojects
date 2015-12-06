#ifdef HAVE_THREADS
if (settings->video.threaded && !video_state.hw_render_callback.context_type)
   {
      /* Can't do hardware rendering with threaded driver currently. */
      RARCH_LOG("Starting threaded video driver ...\n");

      if (!rarch_threaded_video_init(&driver->video, &driver->video_data,
               &driver->input, &driver->input_data,
               driver->video, &video))
      {
         RARCH_ERR("Cannot open threaded video driver ... Exiting ...\n");
         goto error;
      }
   }
   else
#endif
      driver->video_data = driver->video->init(&video, &driver->input,
            &driver->input_data);
