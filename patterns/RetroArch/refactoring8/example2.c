bool rarch_main_ctl(enum rarch_main_ctl_state state, void *data)
{
   driver_t     *driver  = driver_get_ptr();
   settings_t *settings  = config_get_ptr();
   global_t     *global  = global_get_ptr();

   switch (state)
   {
      case RARCH_MAIN_CTL_SET_WINDOWED_SCALE:
         {
            unsigned *idx = (unsigned*)data;
            if (!idx)
               return false;
            global->pending.windowed_scale = *idx;
         }
         break;
      case RARCH_MAIN_CTL_SET_LIBRETRO_PATH:
         {
            const char *fullpath = (const char*)data;
            if (!fullpath)
               return false;
            strlcpy(settings->libretro, fullpath, sizeof(settings->libretro));
         }
         break;
      case RARCH_MAIN_CTL_CLEAR_CONTENT_PATH:
         *global->path.fullpath = '\0';
         break;
      case RARCH_MAIN_CTL_GET_CONTENT_PATH:
         {
            char **fullpath = (char**)data;
            if (!fullpath)
               return false;
            *fullpath       = (char*)global->path.fullpath;
         }
         break;
      case RARCH_MAIN_CTL_SET_CONTENT_PATH:
         {
            const char *fullpath = (const char*)data;
            if (!fullpath)
               return false;
            strlcpy(global->path.fullpath, fullpath, sizeof(global->path.fullpath));
         }
         break;
      case RARCH_MAIN_CTL_CHECK_STATE:
         {
            event_cmd_state_t *cmd    = (event_cmd_state_t*)data;

            if (!cmd || main_is_idle)
               return false;

            if (cmd->screenshot_pressed)
               event_command(EVENT_CMD_TAKE_SCREENSHOT);

            if (cmd->mute_pressed)
               event_command(EVENT_CMD_AUDIO_MUTE_TOGGLE);

            if (cmd->osk_pressed)
               driver->keyboard_linefeed_enable = !driver->keyboard_linefeed_enable;

            if (cmd->volume_up_pressed)
               event_command(EVENT_CMD_VOLUME_UP);
            else if (cmd->volume_down_pressed)
               event_command(EVENT_CMD_VOLUME_DOWN);

#ifdef HAVE_NETPLAY
            if (driver->netplay_data)
            {
               if (cmd->netplay_flip_pressed)
                  event_command(EVENT_CMD_NETPLAY_FLIP_PLAYERS);

               if (cmd->fullscreen_toggle)
                  event_command(EVENT_CMD_FULLSCREEN_TOGGLE);
               break;
            }
#endif

            check_pause(driver, settings,
                  cmd->pause_pressed, cmd->frameadvance_pressed);

            if (!rarch_main_ctl(RARCH_MAIN_CTL_CHECK_PAUSE_STATE, cmd))
               return false;

            check_fast_forward_button(driver,
                  cmd->fastforward_pressed,
                  cmd->hold_pressed, cmd->old_hold_pressed);
            check_stateslots(settings, cmd->state_slot_increase,
                  cmd->state_slot_decrease);

            if (cmd->save_state_pressed)
               event_command(EVENT_CMD_SAVE_STATE);
            else if (cmd->load_state_pressed)
               event_command(EVENT_CMD_LOAD_STATE);

            check_rewind(settings, global, cmd->rewind_pressed);

            rarch_main_ctl(RARCH_MAIN_CTL_CHECK_SLOWMOTION, &cmd->slowmotion_pressed);

            if (cmd->movie_record)
               rarch_main_ctl(RARCH_MAIN_CTL_CHECK_MOVIE, NULL);

            check_shader_dir(global, cmd->shader_next_pressed,
                  cmd->shader_prev_pressed);

            if (cmd->disk_eject_pressed)
               event_command(EVENT_CMD_DISK_EJECT_TOGGLE);
            else if (cmd->disk_next_pressed)
               event_command(EVENT_CMD_DISK_NEXT);
            else if (cmd->disk_prev_pressed)
               event_command(EVENT_CMD_DISK_PREV);

            if (cmd->reset_pressed)
               event_command(EVENT_CMD_RESET);

            if (global->cheat)
            {
               if (cmd->cheat_index_plus_pressed)
                  cheat_manager_index_next(global->cheat);
               else if (cmd->cheat_index_minus_pressed)
                  cheat_manager_index_prev(global->cheat);
               else if (cmd->cheat_toggle_pressed)
                  cheat_manager_toggle(global->cheat);
            }
         }
         break;
      case RARCH_MAIN_CTL_CHECK_PAUSE_STATE:
         {
            bool check_is_oneshot;
            event_cmd_state_t *cmd    = (event_cmd_state_t*)data;

            if (!cmd)
               return false;

            check_is_oneshot     = cmd->frameadvance_pressed || cmd->rewind_pressed;

            if (!main_is_paused)
               return true;

            if (cmd->fullscreen_toggle)
            {
               event_command(EVENT_CMD_FULLSCREEN_TOGGLE);
               video_driver_ctl(RARCH_DISPLAY_CTL_CACHED_FRAME_RENDER, NULL);
            }

            if (!check_is_oneshot)
               return false;
         }
         break;
      case RARCH_MAIN_CTL_CHECK_SLOWMOTION:
         {
            bool *ptr            = (bool*)data;

            if (!ptr)
               return false;

            main_is_slowmotion   = *ptr;

            if (!main_is_slowmotion)
               return false;

            if (settings->video.black_frame_insertion)
               video_driver_ctl(RARCH_DISPLAY_CTL_CACHED_FRAME_RENDER, NULL);

            if (state_manager_frame_is_reversed())
               rarch_main_msg_queue_push_new(MSG_SLOW_MOTION_REWIND, 0, 30, true);
            else
               rarch_main_msg_queue_push_new(MSG_SLOW_MOTION, 0, 30, true);
         }
         break;
      case RARCH_MAIN_CTL_CHECK_MOVIE:
         if (global->bsv.movie_playback)
            return rarch_main_ctl(RARCH_MAIN_CTL_CHECK_MOVIE_PLAYBACK, NULL);
         if (!global->bsv.movie)
            return rarch_main_ctl(RARCH_MAIN_CTL_CHECK_MOVIE_INIT, NULL);
         return rarch_main_ctl(RARCH_MAIN_CTL_CHECK_MOVIE_RECORD, NULL);
      case RARCH_MAIN_CTL_CHECK_MOVIE_RECORD:
         if (!global->bsv.movie)
            return false;

         rarch_main_msg_queue_push_new(
               MSG_MOVIE_RECORD_STOPPED, 2, 180, true);
         RARCH_LOG("%s\n", msg_hash_to_str(MSG_MOVIE_RECORD_STOPPED));

         event_command(EVENT_CMD_BSV_MOVIE_DEINIT);
         break;
      case RARCH_MAIN_CTL_CHECK_MOVIE_INIT:
         if (global->bsv.movie)
            return false;
         {
            char path[PATH_MAX_LENGTH], msg[PATH_MAX_LENGTH];

            settings->rewind_granularity = 1;

            if (settings->state_slot > 0)
               snprintf(path, sizeof(path), "%s%d",
                     global->bsv.movie_path, settings->state_slot);
            else
               strlcpy(path, global->bsv.movie_path, sizeof(path));

            strlcat(path, ".bsv", sizeof(path));

            snprintf(msg, sizeof(msg), "%s \"%s\".",
                  msg_hash_to_str(MSG_STARTING_MOVIE_RECORD_TO),
                  path);

            global->bsv.movie = bsv_movie_init(path, RARCH_MOVIE_RECORD);

            if (!global->bsv.movie)
               return false;
            else if (global->bsv.movie)
            {
               rarch_main_msg_queue_push(msg, 1, 180, true);
               RARCH_LOG("%s \"%s\".\n",
                     msg_hash_to_str(MSG_STARTING_MOVIE_RECORD_TO),
                     path);
            }
            else
            {
               rarch_main_msg_queue_push_new(
                     MSG_FAILED_TO_START_MOVIE_RECORD,
                     1, 180, true);
               RARCH_ERR("%s\n", msg_hash_to_str(MSG_FAILED_TO_START_MOVIE_RECORD));
            }
         }
         break;
      case RARCH_MAIN_CTL_CHECK_MOVIE_PLAYBACK:
         if (!global->bsv.movie_end)
            return false;

         rarch_main_msg_queue_push_new(
               MSG_MOVIE_PLAYBACK_ENDED, 1, 180, false);
         RARCH_LOG("%s\n", msg_hash_to_str(MSG_MOVIE_PLAYBACK_ENDED));

         event_command(EVENT_CMD_BSV_MOVIE_DEINIT);

         global->bsv.movie_end      = false;
         global->bsv.movie_playback = false;
         break;
      case RARCH_MAIN_CTL_STATE_FREE:
         main_is_idle               = false;
         main_is_paused             = false;
         main_is_slowmotion         = false;
         frame_limit_last_time      = 0.0;
         main_max_frames            = 0;
         break;
      case RARCH_MAIN_CTL_GLOBAL_FREE:
         event_command(EVENT_CMD_TEMPORARY_CONTENT_DEINIT);
         event_command(EVENT_CMD_SUBSYSTEM_FULLPATHS_DEINIT);
         event_command(EVENT_CMD_RECORD_DEINIT);
         event_command(EVENT_CMD_LOG_FILE_DEINIT);

         memset(&g_extern, 0, sizeof(g_extern));
         break;
      case RARCH_MAIN_CTL_CLEAR_STATE:
         driver_clear_state();
         rarch_main_ctl(RARCH_MAIN_CTL_STATE_FREE,  NULL);
         rarch_main_ctl(RARCH_MAIN_CTL_GLOBAL_FREE, NULL);
         break;
      case RARCH_MAIN_CTL_SET_MAX_FRAMES:
         {
            unsigned *ptr = (unsigned*)data;
            if (!ptr)
               return false;
            main_max_frames = *ptr;
         }
         break;
      case RARCH_MAIN_CTL_SET_FRAME_LIMIT_LAST_TIME:
         {
            struct retro_system_av_info *av_info = video_viewport_get_system_av_info();
            float fastforward_ratio              = settings->fastforward_ratio;

            if (fastforward_ratio == 0.0f)
               fastforward_ratio = 1.0f;

            frame_limit_last_time    = retro_get_time_usec();
            frame_limit_minimum_time = (retro_time_t)roundf(1000000.0f / (av_info->timing.fps * fastforward_ratio));
         }
         break;
      case RARCH_MAIN_CTL_IS_IDLE:
         {
            bool *ptr = (bool*)data;
            if (!ptr)
               return false;
            *ptr = main_is_idle;
         }
         break;
      case RARCH_MAIN_CTL_SET_IDLE:
         {
            bool *ptr = (bool*)data;
            if (!ptr)
               return false;
            main_is_idle = *ptr;
         }
         break;
      case RARCH_MAIN_CTL_IS_SLOWMOTION:
         {
            bool *ptr = (bool*)data;
            if (!ptr)
               return false;
            *ptr = main_is_slowmotion;
         }
         break;
      case RARCH_MAIN_CTL_SET_SLOWMOTION:
         {
            bool *ptr = (bool*)data;
            if (!ptr)
               return false;
            main_is_slowmotion = *ptr;
         }
         break;
      case RARCH_MAIN_CTL_SET_PAUSED:
         {
            bool *ptr = (bool*)data;
            if (!ptr)
               return false;
            main_is_paused = *ptr;
         }
         break;
      case RARCH_MAIN_CTL_IS_PAUSED:
         {
            bool *ptr = (bool*)data;
            if (!ptr)
               return false;
            *ptr = main_is_paused;
         }
         break;
      default:
         return false;
   }

   return true;
}
