switch(state)
   {
      case RARCH_ACTION_STATE_REPLACE_CONFIG:
         {
            char *path = (char*)data;

            if (!path)
               return false;

            /* If config file to be replaced is the same as the
             * current config file, exit. */
            if (!strcmp(path, global->path.config))
               return false;

            if (settings->config_save_on_exit && *global->path.config)
               config_save_file(global->path.config);

            strlcpy(global->path.config, path, sizeof(global->path.config));
            global->block_config_read = false;
            *settings->libretro = '\0'; /* Load core in new config. */
         }
         event_command(EVENT_CMD_PREPARE_DUMMY);
         return true;
      case RARCH_ACTION_STATE_MENU_RUNNING:
#ifdef HAVE_MENU
         menu_driver_toggle(true);
#endif
#ifdef HAVE_OVERLAY
         if (settings->input.overlay_hide_in_menu)
            event_command(EVENT_CMD_OVERLAY_DEINIT);
#endif
         break;
      case RARCH_ACTION_STATE_LOAD_CONTENT:
#ifdef HAVE_MENU
         /* If content loading fails, we go back to menu. */
         if (!menu_load_content(CORE_TYPE_PLAIN))
            rarch_ctl(RARCH_ACTION_STATE_MENU_RUNNING, NULL);
#endif
         if (driver->frontend_ctx && driver->frontend_ctx->content_loaded)
            driver->frontend_ctx->content_loaded();
         break;
#ifdef HAVE_FFMPEG
      case RARCH_ACTION_STATE_LOAD_CONTENT_FFMPEG:
#ifdef HAVE_MENU
         /* If content loading fails, we go back to menu. */
         if (!menu_load_content(CORE_TYPE_FFMPEG))
            rarch_ctl(RARCH_ACTION_STATE_MENU_RUNNING, NULL);
#endif
         if (driver->frontend_ctx && driver->frontend_ctx->content_loaded)
            driver->frontend_ctx->content_loaded();
         break;
#endif
      case RARCH_ACTION_STATE_LOAD_CONTENT_IMAGEVIEWER:
#ifdef HAVE_MENU
         /* If content loading fails, we go back to menu. */
         if (!menu_load_content(CORE_TYPE_IMAGEVIEWER))
            rarch_ctl(RARCH_ACTION_STATE_MENU_RUNNING, NULL);
#endif
         if (driver->frontend_ctx && driver->frontend_ctx->content_loaded)
            driver->frontend_ctx->content_loaded();
         break;
      case RARCH_ACTION_STATE_MENU_RUNNING_FINISHED:
#ifdef HAVE_MENU
         menu_driver_toggle(false);
#endif
         video_driver_set_texture_enable(false, false);
#ifdef HAVE_OVERLAY
         if (settings && settings->input.overlay_hide_in_menu)
            event_command(EVENT_CMD_OVERLAY_INIT);
#endif
         break;
      case RARCH_ACTION_STATE_QUIT:
         if (global)
            system->shutdown = true;
         rarch_ctl(RARCH_ACTION_STATE_MENU_RUNNING_FINISHED, NULL);
         break;
      case RARCH_ACTION_STATE_FORCE_QUIT:
         rarch_ctl(RARCH_ACTION_STATE_QUIT, NULL);
         break;
      case RARCH_ACTION_STATE_VALIDATE_CPU_FEATURES:
         {
            uint64_t cpu = retro_get_cpu_features();
            (void)cpu;

#ifdef __SSE__
            if (!(cpu & RETRO_SIMD_SSE))
               FAIL_CPU("SSE");
#endif
#ifdef __SSE2__
            if (!(cpu & RETRO_SIMD_SSE2))
               FAIL_CPU("SSE2");
#endif
#ifdef __AVX__
            if (!(cpu & RETRO_SIMD_AVX))
               FAIL_CPU("AVX");
#endif
         }
         break;
      case RARCH_ACTION_STATE_VERIFY_API_VERSION:
         RARCH_LOG("Version of libretro API: %u\n", core.retro_api_version());
         RARCH_LOG("Compiled against API: %u\n",    RETRO_API_VERSION);

         if (core.retro_api_version() != RETRO_API_VERSION)
            RARCH_WARN("%s\n", msg_hash_to_str(MSG_LIBRETRO_ABI_BREAK));
         break;
      case RARCH_ACTION_STATE_FILL_PATHNAMES:
         rarch_init_savefile_paths();
         strlcpy(global->bsv.movie_path, global->name.savefile,
               sizeof(global->bsv.movie_path));

         if (!*global->name.base)
            return false;

         if (!*global->name.ups)
            fill_pathname_noext(global->name.ups, global->name.base, ".ups",
                  sizeof(global->name.ups));
         if (!*global->name.bps)
            fill_pathname_noext(global->name.bps, global->name.base, ".bps",
                  sizeof(global->name.bps));
         if (!*global->name.ips)
            fill_pathname_noext(global->name.ips, global->name.base, ".ips",
                  sizeof(global->name.ips));
         break;
      case RARCH_ACTION_STATE_NONE:
      default:
         return false;
   }
