switch (type)
   {
      case CORE_TYPE_PLAIN:
         {
#ifdef HAVE_DYNAMIC
            settings_t *settings = config_get_ptr();
            function_t sym       = dylib_proc(NULL, "retro_init");

            if (sym)
            {
               /* Try to verify that -lretro was not linked in from other modules
                * since loading it dynamically and with -l will fail hard. */
               RARCH_ERR("Serious problem. RetroArch wants to load libretro cores dyamically, but it is already linked.\n");
               RARCH_ERR("This could happen if other modules RetroArch depends on link against libretro directly.\n");
               RARCH_ERR("Proceeding could cause a crash. Aborting ...\n");
               retro_fail(1, "init_libretro_sym()");
            }

            if (!*settings->libretro)
            {
               RARCH_ERR("RetroArch is built for dynamic libretro cores, but libretro_path is not set. Cannot continue.\n");
               retro_fail(1, "init_libretro_sym()");
            }

            /* Need to use absolute path for this setting. It can be
             * saved to content history, and a relative path would
             * break in that scenario. */
            path_resolve_realpath(settings->libretro,
                  sizeof(settings->libretro));

            RARCH_LOG("Loading dynamic libretro core from: \"%s\"\n",
                  settings->libretro);
            lib_handle = dylib_load(settings->libretro);
            if (!lib_handle)
            {
               RARCH_ERR("Failed to open libretro core: \"%s\"\n",
                     settings->libretro);
               RARCH_ERR("Error(s): %s\n", dylib_error());
               retro_fail(1, "load_dynamic()");
            }
#endif
         }

         SYMBOL(retro_init);
         SYMBOL(retro_deinit);

         SYMBOL(retro_api_version);
         SYMBOL(retro_get_system_info);
         SYMBOL(retro_get_system_av_info);

         SYMBOL(retro_set_environment);
         SYMBOL(retro_set_video_refresh);
         SYMBOL(retro_set_audio_sample);
         SYMBOL(retro_set_audio_sample_batch);
         SYMBOL(retro_set_input_poll);
         SYMBOL(retro_set_input_state);

         SYMBOL(retro_set_controller_port_device);

         SYMBOL(retro_reset);
         SYMBOL(retro_run);

         SYMBOL(retro_serialize_size);
         SYMBOL(retro_serialize);
         SYMBOL(retro_unserialize);

         SYMBOL(retro_cheat_reset);
         SYMBOL(retro_cheat_set);

         SYMBOL(retro_load_game);
         SYMBOL(retro_load_game_special);

         SYMBOL(retro_unload_game);
         SYMBOL(retro_get_region);
         SYMBOL(retro_get_memory_data);
         SYMBOL(retro_get_memory_size);
         break;
      case CORE_TYPE_DUMMY:
         SYMBOL_DUMMY(retro_init);
         SYMBOL_DUMMY(retro_deinit);

         SYMBOL_DUMMY(retro_api_version);
         SYMBOL_DUMMY(retro_get_system_info);
         SYMBOL_DUMMY(retro_get_system_av_info);

         SYMBOL_DUMMY(retro_set_environment);
         SYMBOL_DUMMY(retro_set_video_refresh);
         SYMBOL_DUMMY(retro_set_audio_sample);
         SYMBOL_DUMMY(retro_set_audio_sample_batch);
         SYMBOL_DUMMY(retro_set_input_poll);
         SYMBOL_DUMMY(retro_set_input_state);

         SYMBOL_DUMMY(retro_set_controller_port_device);

         SYMBOL_DUMMY(retro_reset);
         SYMBOL_DUMMY(retro_run);

         SYMBOL_DUMMY(retro_serialize_size);
         SYMBOL_DUMMY(retro_serialize);
         SYMBOL_DUMMY(retro_unserialize);

         SYMBOL_DUMMY(retro_cheat_reset);
         SYMBOL_DUMMY(retro_cheat_set);

         SYMBOL_DUMMY(retro_load_game);
         SYMBOL_DUMMY(retro_load_game_special);

         SYMBOL_DUMMY(retro_unload_game);
         SYMBOL_DUMMY(retro_get_region);
         SYMBOL_DUMMY(retro_get_memory_data);
         SYMBOL_DUMMY(retro_get_memory_size);
         break;
#ifdef HAVE_FFMPEG
      case CORE_TYPE_FFMPEG:
         SYMBOL_FFMPEG(retro_init);
         SYMBOL_FFMPEG(retro_deinit);

         SYMBOL_FFMPEG(retro_api_version);
         SYMBOL_FFMPEG(retro_get_system_info);
         SYMBOL_FFMPEG(retro_get_system_av_info);

         SYMBOL_FFMPEG(retro_set_environment);
         SYMBOL_FFMPEG(retro_set_video_refresh);
         SYMBOL_FFMPEG(retro_set_audio_sample);
         SYMBOL_FFMPEG(retro_set_audio_sample_batch);
         SYMBOL_FFMPEG(retro_set_input_poll);
         SYMBOL_FFMPEG(retro_set_input_state);

         SYMBOL_FFMPEG(retro_set_controller_port_device);

         SYMBOL_FFMPEG(retro_reset);
         SYMBOL_FFMPEG(retro_run);

         SYMBOL_FFMPEG(retro_serialize_size);
         SYMBOL_FFMPEG(retro_serialize);
         SYMBOL_FFMPEG(retro_unserialize);

         SYMBOL_FFMPEG(retro_cheat_reset);
         SYMBOL_FFMPEG(retro_cheat_set);

         SYMBOL_FFMPEG(retro_load_game);
         SYMBOL_FFMPEG(retro_load_game_special);

         SYMBOL_FFMPEG(retro_unload_game);
         SYMBOL_FFMPEG(retro_get_region);
         SYMBOL_FFMPEG(retro_get_memory_data);
         SYMBOL_FFMPEG(retro_get_memory_size);
         break;
#endif
      case CORE_TYPE_IMAGEVIEWER:
#ifdef HAVE_IMAGEVIEWER
         SYMBOL_IMAGEVIEWER(retro_init);
         SYMBOL_IMAGEVIEWER(retro_deinit);

         SYMBOL_IMAGEVIEWER(retro_api_version);
         SYMBOL_IMAGEVIEWER(retro_get_system_info);
         SYMBOL_IMAGEVIEWER(retro_get_system_av_info);

         SYMBOL_IMAGEVIEWER(retro_set_environment);
         SYMBOL_IMAGEVIEWER(retro_set_video_refresh);
         SYMBOL_IMAGEVIEWER(retro_set_audio_sample);
         SYMBOL_IMAGEVIEWER(retro_set_audio_sample_batch);
         SYMBOL_IMAGEVIEWER(retro_set_input_poll);
         SYMBOL_IMAGEVIEWER(retro_set_input_state);

         SYMBOL_IMAGEVIEWER(retro_set_controller_port_device);

         SYMBOL_IMAGEVIEWER(retro_reset);
         SYMBOL_IMAGEVIEWER(retro_run);

         SYMBOL_IMAGEVIEWER(retro_serialize_size);
         SYMBOL_IMAGEVIEWER(retro_serialize);
         SYMBOL_IMAGEVIEWER(retro_unserialize);

         SYMBOL_IMAGEVIEWER(retro_cheat_reset);
         SYMBOL_IMAGEVIEWER(retro_cheat_set);

         SYMBOL_IMAGEVIEWER(retro_load_game);
         SYMBOL_IMAGEVIEWER(retro_load_game_special);

         SYMBOL_IMAGEVIEWER(retro_unload_game);
         SYMBOL_IMAGEVIEWER(retro_get_region);
         SYMBOL_IMAGEVIEWER(retro_get_memory_data);
         SYMBOL_IMAGEVIEWER(retro_get_memory_size);
#endif
         break;
   }
