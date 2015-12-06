switch (id)
   {
      case ACTION_OK_LOAD_WALLPAPER:
         flush_char = NULL;
         flush_type = 49;
         if (path_file_exists(action_path))
         {
            strlcpy(settings->menu.wallpaper, action_path, sizeof(settings->menu.wallpaper));

            rarch_main_data_msg_queue_push(DATA_TYPE_IMAGE, action_path, "cb_menu_wallpaper", 0, 1,
                  true);
         }
         break;
      case ACTION_OK_LOAD_CORE:
         flush_char = NULL;
         flush_type = MENU_SETTINGS;
         rarch_main_ctl(RARCH_MAIN_CTL_SET_LIBRETRO_PATH, action_path);
         event_command(EVENT_CMD_LOAD_CORE);

#if defined(HAVE_DYNAMIC)
         /* No content needed for this core, load core immediately. */
         if (menu->load_no_content && settings->core.set_supports_no_game_enable)
         {
            rarch_main_ctl(RARCH_MAIN_CTL_CLEAR_CONTENT_PATH, NULL);
            ret = menu_common_load_content(NULL, NULL, false, CORE_TYPE_PLAIN);
            if (ret == -1)
               action_ok_push_quick_menu();
         }
         else
            ret = 0;
#elif defined(RARCH_CONSOLE)
         /* Core selection on non-console just updates directory listing.
          * Will take effect on new content load. */
         ret = -1;
         event_command(EVENT_CMD_RESTART_RETROARCH);
#endif

         break;

      case ACTION_OK_LOAD_CONFIG_FILE:
         flush_char      = NULL;
         flush_type      = MENU_SETTINGS;
         msg_force       = true;
         menu_display_ctl(MENU_DISPLAY_CTL_SET_MSG_FORCE, &msg_force);

         if (rarch_ctl(RARCH_ACTION_STATE_REPLACE_CONFIG, action_path))
         {
            bool pending_push = false;
            menu_navigation_ctl(MENU_NAVIGATION_CTL_CLEAR, &pending_push);
            ret = -1;
         }
         break;
#ifdef HAVE_SHADER_MANAGER
      case ACTION_OK_LOAD_PRESET:
         menu_shader_manager_set_preset(menu->shader,
               video_shader_parse_type(action_path, RARCH_SHADER_NONE),
               action_path);
         break;
      case ACTION_OK_LOAD_SHADER_PASS:
         strlcpy(
               menu->shader->pass[hack_shader_pass].source.path,
               action_path,
               sizeof(menu->shader->pass[hack_shader_pass].source.path));
         video_shader_resolve_parameters(NULL, menu->shader);
         break;
#endif
      case ACTION_OK_LOAD_RECORD_CONFIGFILE:
         strlcpy(global->record.config, action_path,
               sizeof(global->record.config));
         break;
      case ACTION_OK_LOAD_REMAPPING_FILE:
         {
            config_file_t *conf = config_file_new(action_path);

            if (conf)
               input_remapping_load_file(conf, action_path);
         }
         break;
      case ACTION_OK_LOAD_CHEAT_FILE:
         if (global->cheat)
            cheat_manager_free(global->cheat);

         global->cheat = cheat_manager_load(action_path);

         if (!global->cheat)
            goto error;
         break;
      case ACTION_OK_APPEND_DISK_IMAGE:
         flush_char = NULL;
         flush_type = 49;
         event_disk_control_append_image(action_path);
         event_command(EVENT_CMD_RESUME);
         break;
      case ACTION_OK_SET_PATH:
         flush_char = NULL;
         flush_type = 49;
         {
            menu_file_list_cbs_t *cbs = menu_entries_get_last_stack_actiondata();

            if (cbs)
            {
               menu_setting_set_with_string_representation(cbs->setting, action_path);
               ret = menu_setting_generic(cbs->setting, false);
            }
         }
         break;
      default:
         break;
   }
