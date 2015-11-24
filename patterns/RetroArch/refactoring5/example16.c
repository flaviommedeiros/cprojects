#ifdef HAVE_THREADS
if (audio_data.audio_callback.callback)
   {
      RARCH_LOG("Starting threaded audio driver ...\n");
      if (!rarch_threaded_audio_init(&driver->audio, &driver->audio_data,
               *settings->audio.device ? settings->audio.device : NULL,
               settings->audio.out_rate, settings->audio.latency,
               driver->audio))
      {
         RARCH_ERR("Cannot open threaded audio driver ... Exiting ...\n");
         retro_fail(1, "init_audio()");
      }
   }
   else
#endif
   {
      driver->audio_data = driver->audio->init(*settings->audio.device ?
            settings->audio.device : NULL,
            settings->audio.out_rate, settings->audio.latency);
   }
