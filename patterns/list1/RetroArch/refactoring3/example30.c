switch (cmd)
   {
      case EVENT_CMD_SET_PER_GAME_RESOLUTION:
#if defined(GEKKO)
         {
            unsigned width = 0, height = 0;

            event_command(EVENT_CMD_VIDEO_SET_ASPECT_RATIO);

            if (video_driver_get_video_output_size(&width, &height))
            {
               video_driver_set_video_mode(width, height, true);

               char msg[PATH_MAX_LENGTH] = {0};
               snprintf(msg, sizeof(msg),"Resolution: %dx%d",width, height);
               rarch_main_msg_queue_push(msg, 1, 100, true);
            }
         }
#endif
         break;
      case EVENT_CMD_LOAD_CONTENT_PERSIST:
#ifdef HAVE_DYNAMIC
         event_command(EVENT_CMD_LOAD_CORE);
#endif
         rarch_ctl(RARCH_ACTION_STATE_LOAD_CONTENT, NULL);
         break;
#ifdef HAVE_FFMPEG
      case EVENT_CMD_LOAD_CONTENT_FFMPEG:
         rarch_ctl(RARCH_ACTION_STATE_LOAD_CONTENT_FFMPEG, NULL);
         break;
#endif
      case EVENT_CMD_LOAD_CONTENT_IMAGEVIEWER:
         rarch_ctl(RARCH_ACTION_STATE_LOAD_CONTENT_IMAGEVIEWER, NULL);
         break;
      case EVENT_CMD_LOAD_CONTENT:
         {
#ifdef HAVE_DYNAMIC
            event_command(EVENT_CMD_LOAD_CONTENT_PERSIST);
#else
            char *fullpath = NULL;
            rarch_main_ctl(RARCH_MAIN_CTL_GET_CONTENT_PATH, &fullpath);
            rarch_environment_cb(RETRO_ENVIRONMENT_SET_LIBRETRO_PATH,
                  (void*)settings->libretro);
            rarch_environment_cb(RETRO_ENVIRONMENT_EXEC, (void*)fullpath);
            event_command(EVENT_CMD_QUIT);
#endif
         }
         break;
      case EVENT_CMD_LOAD_CORE_DEINIT:
#ifdef HAVE_DYNAMIC
#ifdef HAVE_MENU
         libretro_free_system_info(&global->menu.info);
#endif
#endif
         break;
      case EVENT_CMD_LOAD_CORE_PERSIST:
         event_command(EVENT_CMD_LOAD_CORE_DEINIT);
         {
#ifdef HAVE_MENU
            menu_handle_t *menu = menu_driver_get_ptr();
            if (menu)
               event_update_system_info(&global->menu.info,
                     &menu->load_no_content);
#endif
         }
         break;
      case EVENT_CMD_LOAD_CORE:
         event_command(EVENT_CMD_LOAD_CORE_PERSIST);
#ifndef HAVE_DYNAMIC
         event_command(EVENT_CMD_QUIT);
#endif
         break;
      case EVENT_CMD_LOAD_STATE:
         /* Immutable - disallow savestate load when
          * we absolutely cannot change game state. */
         if (global->bsv.movie)
            return false;

#ifdef HAVE_NETPLAY
         if (driver->netplay_data)
            return false;
#endif
         event_main_state(cmd);
         break;
      case EVENT_CMD_RESIZE_WINDOWED_SCALE:
         {
            unsigned idx = 0;
            if (global->pending.windowed_scale == 0)
               return false;

            settings->video.scale = global->pending.windowed_scale;

            if (!settings->video.fullscreen)
               event_command(EVENT_CMD_REINIT);

            rarch_main_ctl(RARCH_MAIN_CTL_SET_WINDOWED_SCALE, &idx);
         }
         break;
      case EVENT_CMD_MENU_TOGGLE:
#ifdef HAVE_MENU
         if (menu_driver_alive())
            rarch_ctl(RARCH_ACTION_STATE_MENU_RUNNING_FINISHED, NULL);
         else
            rarch_ctl(RARCH_ACTION_STATE_MENU_RUNNING, NULL);
#endif
         break;
      case EVENT_CMD_CONTROLLERS_INIT:
         event_init_controllers();
         break;
      case EVENT_CMD_RESET:
         RARCH_LOG("%s.\n", msg_hash_to_str(MSG_RESET));
         rarch_main_msg_queue_push_new(MSG_RESET, 1, 120, true);

#ifdef HAVE_CHEEVOS
         cheevos_globals.cheats_were_enabled = cheevos_globals.cheats_are_enabled;
#endif
         core.retro_reset();

         /* bSNES since v073r01 resets controllers to JOYPAD
          * after a reset, so just enforce it here. */
         event_command(EVENT_CMD_CONTROLLERS_INIT);
         break;
      case EVENT_CMD_SAVE_STATE:
         if (settings->savestate_auto_index)
            settings->state_slot++;

         event_main_state(cmd);
         break;
      case EVENT_CMD_SAVE_STATE_DECREMENT:
         /* Slot -1 is (auto) slot. */
         if (settings->state_slot >= 0)
            settings->state_slot--;
         break;
      case EVENT_CMD_SAVE_STATE_INCREMENT:
         settings->state_slot++;
         break;
      case EVENT_CMD_TAKE_SCREENSHOT:
         if (!take_screenshot())
            return false;
         break;
      case EVENT_CMD_PREPARE_DUMMY:
         {
#ifdef HAVE_MENU
            menu_handle_t *menu = menu_driver_get_ptr();
            if (menu)
               menu->load_no_content = false;
#endif
            rarch_main_data_deinit();

            rarch_main_ctl(RARCH_MAIN_CTL_CLEAR_CONTENT_PATH, NULL);

            rarch_ctl(RARCH_ACTION_STATE_LOAD_CONTENT, NULL);
         }
         break;
      case EVENT_CMD_UNLOAD_CORE:
         event_command(EVENT_CMD_PREPARE_DUMMY);
         event_command(EVENT_CMD_LOAD_CORE_DEINIT);
         break;
      case EVENT_CMD_QUIT:
         rarch_ctl(RARCH_ACTION_STATE_QUIT, NULL);
         break;
      case EVENT_CMD_REINIT:
         {
            const struct retro_hw_render_callback *hw_render =
               (const struct retro_hw_render_callback*)video_driver_callback();
            const input_driver_t *input     = driver ?
               (const input_driver_t*)driver->input : NULL;

            driver->video_cache_context     = hw_render->cache_context;
            driver->video_cache_context_ack = false;
            event_command(EVENT_CMD_RESET_CONTEXT);
            driver->video_cache_context     = false;

            /* Poll input to avoid possibly stale data to corrupt things. */
            input->poll(driver->input_data);

#ifdef HAVE_MENU
            menu_display_ctl(MENU_DISPLAY_CTL_SET_FRAMEBUFFER_DIRTY_FLAG, NULL);

            if (menu_driver_alive())
               event_command(EVENT_CMD_VIDEO_SET_BLOCKING_STATE);
#endif
         }
         break;
      case EVENT_CMD_CHEATS_DEINIT:
         if (!global)
            break;

         if (global->cheat)
            cheat_manager_free(global->cheat);
         global->cheat = NULL;
         break;
      case EVENT_CMD_CHEATS_INIT:
         event_command(EVENT_CMD_CHEATS_DEINIT);
         event_init_cheats();
         break;
      case EVENT_CMD_CHEATS_APPLY:
         if (!global->cheat)
            break;

         cheat_manager_apply_cheats(global->cheat);
         break;
      case EVENT_CMD_REMAPPING_DEINIT:
         break;
      case EVENT_CMD_REMAPPING_INIT:
         event_command(EVENT_CMD_REMAPPING_DEINIT);
         event_init_remapping();
         break;
      case EVENT_CMD_REWIND_DEINIT:
         if (!global)
            break;
#ifdef HAVE_NETPLAY
         if (driver->netplay_data)
            return false;
#endif
         if (global->rewind.state)
            state_manager_free(global->rewind.state);
         global->rewind.state = NULL;
         break;
      case EVENT_CMD_REWIND_INIT:
         if (!driver->netplay_data)
            init_rewind();
         break;
      case EVENT_CMD_REWIND_TOGGLE:
         if (settings->rewind_enable)
            event_command(EVENT_CMD_REWIND_INIT);
         else
            event_command(EVENT_CMD_REWIND_DEINIT);
         break;
      case EVENT_CMD_AUTOSAVE_DEINIT:
#ifdef HAVE_THREADS
         event_deinit_autosave();
#endif
         break;
      case EVENT_CMD_AUTOSAVE_INIT:
         event_command(EVENT_CMD_AUTOSAVE_DEINIT);
#ifdef HAVE_THREADS
         event_init_autosave();
#endif
         break;
      case EVENT_CMD_AUTOSAVE_STATE:
         event_save_auto_state();
         break;
      case EVENT_CMD_AUDIO_STOP:
         if (!driver->audio_data)
            return false;
         if (!audio_driver_ctl(RARCH_AUDIO_CTL_ALIVE, NULL))
            return false;

         if (!audio_driver_ctl(RARCH_AUDIO_CTL_STOP, NULL))
            return false;
         break;
      case EVENT_CMD_AUDIO_START:
         if (!driver->audio_data || audio_driver_ctl(RARCH_AUDIO_CTL_ALIVE, NULL))
            return false;

         if (!settings->audio.mute_enable && !audio_driver_ctl(RARCH_AUDIO_CTL_START, NULL))
         {
            RARCH_ERR("Failed to start audio driver. Will continue without audio.\n");
            driver->audio_active = false;
         }
         break;
      case EVENT_CMD_AUDIO_MUTE_TOGGLE:
         {
            const char *msg = !settings->audio.mute_enable ?
               msg_hash_to_str(MSG_AUDIO_MUTED):
               msg_hash_to_str(MSG_AUDIO_UNMUTED);

            if (!audio_driver_ctl(RARCH_AUDIO_CTL_MUTE_TOGGLE, NULL))
            {
               RARCH_ERR("%s.\n",
                     msg_hash_to_str(MSG_FAILED_TO_UNMUTE_AUDIO));
               return false;
            }

            rarch_main_msg_queue_push(msg, 1, 180, true);
            RARCH_LOG("%s\n", msg);
         }
         break;
      case EVENT_CMD_OVERLAY_DEINIT:
#ifdef HAVE_OVERLAY
         input_overlay_free_ptr();
#endif
         break;
      case EVENT_CMD_OVERLAY_INIT:
         event_command(EVENT_CMD_OVERLAY_DEINIT);
#ifdef HAVE_OVERLAY
         if (input_overlay_new_ptr() == -1)
            RARCH_ERR("%s.\n", msg_hash_to_str(MSG_FAILED_TO_LOAD_OVERLAY));
#endif
         break;
      case EVENT_CMD_OVERLAY_NEXT:
#ifdef HAVE_OVERLAY
         input_overlay_next(settings->input.overlay_opacity);
#endif
         break;
      case EVENT_CMD_DSP_FILTER_DEINIT:
         if (!global)
            break;

         audio_driver_dsp_filter_free();
         break;
      case EVENT_CMD_DSP_FILTER_INIT:
         event_command(EVENT_CMD_DSP_FILTER_DEINIT);
         if (!*settings->audio.dsp_plugin)
            break;
         audio_driver_dsp_filter_init(settings->audio.dsp_plugin);
         break;
      case EVENT_CMD_GPU_RECORD_DEINIT:
         if (!global)
            break;

         if (global->record.gpu_buffer)
            free(global->record.gpu_buffer);
         global->record.gpu_buffer = NULL;
         break;
      case EVENT_CMD_RECORD_DEINIT:
         if (!recording_deinit())
            return false;
         break;
      case EVENT_CMD_RECORD_INIT:
         event_command(EVENT_CMD_HISTORY_DEINIT);
         if (!recording_init())
            return false;
         break;
      case EVENT_CMD_HISTORY_DEINIT:
         if (g_defaults.history)
         {
            content_playlist_write_file(g_defaults.history);
            content_playlist_free(g_defaults.history);
         }
         g_defaults.history = NULL;
         break;
      case EVENT_CMD_HISTORY_INIT:
         event_command(EVENT_CMD_HISTORY_DEINIT);
         if (!settings->history_list_enable)
            return false;
         RARCH_LOG("%s: [%s].\n",
               msg_hash_to_str(MSG_LOADING_HISTORY_FILE),
               settings->content_history_path);
         g_defaults.history = content_playlist_init(
               settings->content_history_path,
               settings->content_history_size);
         break;
      case EVENT_CMD_CORE_INFO_DEINIT:
         if (!global)
            break;

         if (global->core_info.list)
            core_info_list_free(global->core_info.list);
         global->core_info.list = NULL;
         break;
      case EVENT_CMD_DATA_RUNLOOP_FREE:
         rarch_main_data_free();
         break;
      case EVENT_CMD_CORE_INFO_INIT:
         event_command(EVENT_CMD_CORE_INFO_DEINIT);

         if (*settings->libretro_directory)
            global->core_info.list = core_info_list_new();
         break;
      case EVENT_CMD_CORE_DEINIT:
         {
            struct retro_hw_render_callback *cb = video_driver_callback();
            event_deinit_core(true);

            if (cb)
               memset(cb, 0, sizeof(*cb));

            break;
         }
      case EVENT_CMD_CORE_INIT:
         if (!event_init_core())
            return false;
         break;
      case EVENT_CMD_VIDEO_APPLY_STATE_CHANGES:
         video_driver_ctl(RARCH_DISPLAY_CTL_APPLY_STATE_CHANGES, NULL);
         break;
      case EVENT_CMD_VIDEO_SET_NONBLOCKING_STATE:
         boolean = true; /* fall-through */
      case EVENT_CMD_VIDEO_SET_BLOCKING_STATE:
         video_driver_ctl(RARCH_DISPLAY_CTL_SET_NONBLOCK_STATE, &boolean);
         break;
      case EVENT_CMD_VIDEO_SET_ASPECT_RATIO:
         video_driver_ctl(RARCH_DISPLAY_CTL_SET_ASPECT_RATIO, NULL);
         break;
      case EVENT_CMD_AUDIO_SET_NONBLOCKING_STATE:
         boolean = true; /* fall-through */
      case EVENT_CMD_AUDIO_SET_BLOCKING_STATE:
         audio_driver_set_nonblocking_state(boolean);
         break;
      case EVENT_CMD_OVERLAY_SET_SCALE_FACTOR:
#ifdef HAVE_OVERLAY
         input_overlay_set_scale_factor(settings->input.overlay_scale);
#endif
         break;
      case EVENT_CMD_OVERLAY_SET_ALPHA_MOD:
#ifdef HAVE_OVERLAY
         input_overlay_set_alpha_mod(settings->input.overlay_opacity);
#endif
         break;
      case EVENT_CMD_DRIVERS_DEINIT:
         uninit_drivers(DRIVERS_CMD_ALL);
         break;
      case EVENT_CMD_DRIVERS_INIT:
         init_drivers(DRIVERS_CMD_ALL);
         break;
      case EVENT_CMD_AUDIO_REINIT:
         uninit_drivers(DRIVER_AUDIO);
         init_drivers(DRIVER_AUDIO);
         break;
      case EVENT_CMD_RESET_CONTEXT:
         event_command(EVENT_CMD_DRIVERS_DEINIT);
         event_command(EVENT_CMD_DRIVERS_INIT);
         break;
      case EVENT_CMD_QUIT_RETROARCH:
         rarch_ctl(RARCH_ACTION_STATE_FORCE_QUIT, NULL);
         break;
      case EVENT_CMD_SHUTDOWN:
#if defined(__linux__) && !defined(ANDROID)
         rarch_main_msg_queue_push("Shutting down...", 1, 180, true);
         rarch_ctl(RARCH_ACTION_STATE_FORCE_QUIT, NULL);
         system("shutdown -P now");
#endif
         break;
      case EVENT_CMD_RESUME:
         rarch_ctl(RARCH_ACTION_STATE_MENU_RUNNING_FINISHED, NULL);
         break;
      case EVENT_CMD_RESTART_RETROARCH:
         {
#if defined(GEKKO) && defined(HW_RVL)
            char new_path[PATH_MAX_LENGTH];
            fill_pathname_join(new_path, g_defaults.dir.core, SALAMANDER_FILE, sizeof(new_path));
            rarch_main_ctl(RARCH_MAIN_CTL_SET_CONTENT_PATH, new_path);
#endif
            if (driver->frontend_ctx && driver->frontend_ctx->set_fork)
               driver->frontend_ctx->set_fork(true, false);
         }
         break;
      case EVENT_CMD_MENU_SAVE_CURRENT_CONFIG:
         event_save_current_config();
         break;
      case EVENT_CMD_MENU_SAVE_CONFIG:
         if (!event_save_core_config())
            return false;
         break;
      case EVENT_CMD_SHADERS_APPLY_CHANGES:
#ifdef HAVE_MENU
         menu_shader_manager_apply_changes();
#endif
         break;
      case EVENT_CMD_PAUSE_CHECKS:
         rarch_main_ctl(RARCH_MAIN_CTL_IS_PAUSED, &boolean);

         if (boolean)
         {
            RARCH_LOG("%s\n", msg_hash_to_str(MSG_PAUSED));
            event_command(EVENT_CMD_AUDIO_STOP);

            if (settings->video.black_frame_insertion)
               video_driver_ctl(RARCH_DISPLAY_CTL_CACHED_FRAME_RENDER, NULL);
         }
         else
         {
            RARCH_LOG("%s\n", msg_hash_to_str(MSG_UNPAUSED));
            event_command(EVENT_CMD_AUDIO_START);
         }
         break;
      case EVENT_CMD_PAUSE_TOGGLE:
         rarch_main_ctl(RARCH_MAIN_CTL_IS_PAUSED,  &boolean);
         boolean = !boolean;
         rarch_main_ctl(RARCH_MAIN_CTL_SET_PAUSED, &boolean);
         event_command(EVENT_CMD_PAUSE_CHECKS);
         break;
      case EVENT_CMD_UNPAUSE:
         boolean = false;

         rarch_main_ctl(RARCH_MAIN_CTL_SET_PAUSED, &boolean);
         event_command(EVENT_CMD_PAUSE_CHECKS);
         break;
      case EVENT_CMD_PAUSE:
         boolean = true;

         rarch_main_ctl(RARCH_MAIN_CTL_SET_PAUSED, &boolean);
         event_command(EVENT_CMD_PAUSE_CHECKS);
         break;
      case EVENT_CMD_MENU_PAUSE_LIBRETRO:
#ifdef HAVE_MENU
         if (menu_driver_alive())
         {
            if (settings->menu.pause_libretro)
               event_command(EVENT_CMD_AUDIO_STOP);
            else
               event_command(EVENT_CMD_AUDIO_START);
         }
         else
         {
            if (settings->menu.pause_libretro)
               event_command(EVENT_CMD_AUDIO_START);
         }
#endif
         break;
      case EVENT_CMD_SHADER_DIR_DEINIT:
         if (!global)
            break;

         dir_list_free(global->dir.shader_dir.list);
         global->dir.shader_dir.list = NULL;
         global->dir.shader_dir.ptr  = 0;
         break;
      case EVENT_CMD_SHADER_DIR_INIT:
         event_command(EVENT_CMD_SHADER_DIR_DEINIT);

         if (!*settings->video.shader_dir)
            return false;

         global->dir.shader_dir.list = dir_list_new_special(NULL, DIR_LIST_SHADERS, NULL);

         if (!global->dir.shader_dir.list || global->dir.shader_dir.list->size == 0)
         {
            event_command(EVENT_CMD_SHADER_DIR_DEINIT);
            return false;
         }

         global->dir.shader_dir.ptr  = 0;
         dir_list_sort(global->dir.shader_dir.list, false);

         for (i = 0; i < global->dir.shader_dir.list->size; i++)
            RARCH_LOG("%s \"%s\"\n",
                  msg_hash_to_str(MSG_FOUND_SHADER),
                  global->dir.shader_dir.list->elems[i].data);
         break;
      case EVENT_CMD_SAVEFILES:
         event_save_files();
         break;
      case EVENT_CMD_SAVEFILES_DEINIT:
         if (!global)
            break;

         if (global->savefiles)
            string_list_free(global->savefiles);
         global->savefiles = NULL;
         break;
      case EVENT_CMD_SAVEFILES_INIT:
         global->sram.use = global->sram.use && !global->sram.save_disable
#ifdef HAVE_NETPLAY
            && (!driver->netplay_data || !global->netplay.is_client)
#endif
            ;

         if (!global->sram.use)
            RARCH_LOG("%s\n",
                  msg_hash_to_str(MSG_SRAM_WILL_NOT_BE_SAVED));

         if (global->sram.use)
            event_command(EVENT_CMD_AUTOSAVE_INIT);
         break;
      case EVENT_CMD_MSG_QUEUE_DEINIT:
         rarch_main_msg_queue_free();
         break;
      case EVENT_CMD_MSG_QUEUE_INIT:
         event_command(EVENT_CMD_MSG_QUEUE_DEINIT);
         rarch_main_msg_queue_init();
         rarch_main_data_init_queues();
         break;
      case EVENT_CMD_BSV_MOVIE_DEINIT:
         if (!global)
            break;

         if (global->bsv.movie)
            bsv_movie_free(global->bsv.movie);
         global->bsv.movie = NULL;
         break;
      case EVENT_CMD_BSV_MOVIE_INIT:
         event_command(EVENT_CMD_BSV_MOVIE_DEINIT);
         event_init_movie();
         break;
      case EVENT_CMD_NETPLAY_DEINIT:
#ifdef HAVE_NETPLAY
         deinit_netplay();
#endif
         break;
      case EVENT_CMD_NETWORK_DEINIT:
#ifdef HAVE_NETWORKING
         network_deinit();
#endif
         break;
      case EVENT_CMD_NETWORK_INIT:
#ifdef HAVE_NETWORKING
         network_init();
#endif
         break;
      case EVENT_CMD_NETPLAY_INIT:
         event_command(EVENT_CMD_NETPLAY_DEINIT);
#ifdef HAVE_NETPLAY
         if (!init_netplay())
            return false;
#endif
         break;
      case EVENT_CMD_NETPLAY_FLIP_PLAYERS:
#ifdef HAVE_NETPLAY
         {
            netplay_t *netplay = (netplay_t*)driver->netplay_data;
            if (!netplay)
               return false;
            netplay_flip_users(netplay);
         }
#endif
         break;
      case EVENT_CMD_FULLSCREEN_TOGGLE:
         if (!video_driver_ctl(RARCH_DISPLAY_CTL_HAS_WINDOWED, NULL))
            return false;

         /* If we go fullscreen we drop all drivers and
          * reinitialize to be safe. */
         settings->video.fullscreen = !settings->video.fullscreen;
         event_command(EVENT_CMD_REINIT);
         break;
      case EVENT_CMD_COMMAND_DEINIT:
#ifdef HAVE_COMMAND
         if (driver->command)
            rarch_cmd_free(driver->command);
         driver->command = NULL;
#endif
         break;
      case EVENT_CMD_COMMAND_INIT:
         event_command(EVENT_CMD_COMMAND_DEINIT);

#ifdef HAVE_COMMAND
         event_init_command();
#endif
         break;
      case EVENT_CMD_TEMPORARY_CONTENT_DEINIT:
         if (!global)
            break;

         if (global->temporary_content)
            event_free_temporary_content();
         global->temporary_content = NULL;
         break;
      case EVENT_CMD_SUBSYSTEM_FULLPATHS_DEINIT:
         if (!global)
            break;

         if (global->subsystem_fullpaths)
            string_list_free(global->subsystem_fullpaths);
         global->subsystem_fullpaths = NULL;
         break;
      case EVENT_CMD_LOG_FILE_DEINIT:
         if (!global)
            break;

         if (global->log_file && global->log_file != stderr)
            fclose(global->log_file);
         global->log_file = NULL;
         break;
      case EVENT_CMD_DISK_EJECT_TOGGLE:
         if (info && info->disk_control.get_num_images)
         {
            const struct retro_disk_control_callback *control =
               (const struct retro_disk_control_callback*)
               &info->disk_control;

            if (control)
               event_check_disk_eject(control);
         }
         else
            rarch_main_msg_queue_push_new(
                  MSG_CORE_DOES_NOT_SUPPORT_DISK_OPTIONS,
                  1, 120, true);
         break;
      case EVENT_CMD_DISK_NEXT:
         if (info && info->disk_control.get_num_images)
         {
            const struct retro_disk_control_callback *control =
               (const struct retro_disk_control_callback*)
               &info->disk_control;

            if (!control)
               return false;

            if (!control->get_eject_state())
               return false;

            event_check_disk_next(control);
         }
         else
            rarch_main_msg_queue_push_new(
                  MSG_CORE_DOES_NOT_SUPPORT_DISK_OPTIONS,
                  1, 120, true);
         break;
      case EVENT_CMD_DISK_PREV:
         if (info && info->disk_control.get_num_images)
         {
            const struct retro_disk_control_callback *control =
               (const struct retro_disk_control_callback*)
               &info->disk_control;

            if (!control)
               return false;

            if (!control->get_eject_state())
               return false;

            event_check_disk_prev(control);
         }
         else
            rarch_main_msg_queue_push_new(
                  MSG_CORE_DOES_NOT_SUPPORT_DISK_OPTIONS,
                  1, 120, true);
         break;
      case EVENT_CMD_RUMBLE_STOP:
         for (i = 0; i < MAX_USERS; i++)
         {
            input_driver_set_rumble_state(i, RETRO_RUMBLE_STRONG, 0);
            input_driver_set_rumble_state(i, RETRO_RUMBLE_WEAK, 0);
         }
         break;
      case EVENT_CMD_GRAB_MOUSE_TOGGLE:
         {
            static bool grab_mouse_state  = false;
            bool grab_mouse_state_tmp;

            grab_mouse_state = !grab_mouse_state;

            if (!driver->input || !input_driver_grab_mouse(grab_mouse_state))
               return false;

            RARCH_LOG("%s: %s.\n",
                  msg_hash_to_str(MSG_GRAB_MOUSE_STATE),
                  grab_mouse_state ? "yes" : "no");

            grab_mouse_state_tmp = !grab_mouse_state;
            video_driver_ctl(RARCH_DISPLAY_CTL_SHOW_MOUSE, &grab_mouse_state_tmp);
         }
         break;
      case EVENT_CMD_PERFCNT_REPORT_FRONTEND_LOG:
         rarch_perf_log();
         break;
      case EVENT_CMD_VOLUME_UP:
         event_set_volume(0.5f);
         break;
      case EVENT_CMD_VOLUME_DOWN:
         event_set_volume(-0.5f);
         break;
      case EVENT_CMD_SET_FRAME_LIMIT:
         rarch_main_ctl(RARCH_MAIN_CTL_SET_FRAME_LIMIT_LAST_TIME, NULL);
         break;
      case EVENT_CMD_NONE:
      default:
         return false;
   }
