switch (type)
   {
      case DISPLAYLIST_NONE:
         break;
      case DISPLAYLIST_INFO:
         menu_entries_push(info->list, info->path, info->label, info->type, info->directory_ptr, 0);
         break;
      case DISPLAYLIST_GENERIC:
         {
            bool pending_push = true;
            menu_driver_list_cache(MENU_LIST_PLAIN, 0);

            menu_entries_push(info->list, info->path, info->label, info->type, info->directory_ptr, 0);
            menu_navigation_ctl(MENU_NAVIGATION_CTL_CLEAR, &pending_push);
            menu_entries_set_refresh(false);
         }
         break;
      case DISPLAYLIST_USER_BINDS_LIST:
         {
            char lbl[PATH_MAX_LENGTH];
            snprintf(lbl, sizeof(lbl),
                  "Input User %.1s Binds", info->path);
            ret = menu_displaylist_parse_settings(menu, info,
                  lbl, PARSE_NONE, true);
            info->need_refresh = true;
            info->need_push    = true;
         }
         break;
      case DISPLAYLIST_ACCOUNTS_LIST:
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_ACCOUNTS_LIST_END),
               PARSE_NONE, true);
         info->need_refresh = true;
         info->need_push    = true;
         break;
      case DISPLAYLIST_ACCOUNTS_CHEEVOS_LIST:
#ifdef HAVE_CHEEVOS
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_ACCOUNTS_CHEEVOS_SETTINGS),
               PARSE_NONE, true);
#else
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_NO_ITEMS),
               "", MENU_SETTING_NO_ITEM, 0, 0);
         ret = 0;
#endif
         info->need_refresh = true;
         info->need_push    = true;
         break;
      case DISPLAYLIST_HELP_SCREEN_LIST:
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_HELP_CONTROLS),
               menu_hash_to_str(MENU_LABEL_HELP_CONTROLS),
               0, 0, 0);
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_HELP_WHAT_IS_A_CORE),
               menu_hash_to_str(MENU_LABEL_HELP_WHAT_IS_A_CORE),
               0, 0, 0);
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_HELP_LOADING_CONTENT),
               menu_hash_to_str(MENU_LABEL_HELP_LOADING_CONTENT),
               0, 0, 0);
#ifdef HAVE_LIBRETRODB
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_HELP_SCANNING_CONTENT),
               menu_hash_to_str(MENU_LABEL_HELP_SCANNING_CONTENT),
               0, 0, 0);
#endif
#ifdef HAVE_OVERLAY
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_HELP_CHANGE_VIRTUAL_GAMEPAD),
               menu_hash_to_str(MENU_LABEL_HELP_CHANGE_VIRTUAL_GAMEPAD),
               0, 0, 0);
#endif
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_HELP_AUDIO_VIDEO_TROUBLESHOOTING),
               menu_hash_to_str(MENU_LABEL_HELP_AUDIO_VIDEO_TROUBLESHOOTING),
               0, 0, 0);
         info->need_refresh = true;
         info->need_push    = true;
         break;
      case DISPLAYLIST_HELP:
         menu_entries_push(info->list, info->path, info->label, info->type, info->directory_ptr, 0);
         menu->push_help_screen = false;
         break;
      case DISPLAYLIST_SETTINGS:
         ret = menu_displaylist_parse_settings(menu, info, info->label, PARSE_NONE, true);
         info->need_push    = true;
         break;
      case DISPLAYLIST_MAIN_MENU:
         if (global->inited.main && (global->inited.core.type != CORE_TYPE_DUMMY))
            menu_displaylist_parse_settings(menu, info,
                  menu_hash_to_str(MENU_LABEL_CONTENT_SETTINGS), PARSE_ACTION, false);

#if defined(HAVE_DYNAMIC) || defined(HAVE_LIBRETRO_MANAGEMENT)
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_CORE_LIST), PARSE_ACTION, false);
#endif
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_LOAD_CONTENT_LIST), PARSE_ACTION, false);
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_LOAD_CONTENT_HISTORY), PARSE_ACTION, false);
#if defined(HAVE_NETWORKING)
#if defined(HAVE_LIBRETRODB)
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_ADD_CONTENT_LIST), PARSE_ACTION, false);
#endif
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_ONLINE_UPDATER), PARSE_ACTION, false);
#endif
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_SETTINGS), PARSE_ACTION, false);
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INFORMATION_LIST), PARSE_ACTION, false);
#ifndef HAVE_DYNAMIC
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_RESTART_RETROARCH), PARSE_ACTION, false);
#endif
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_CONFIGURATIONS), PARSE_ACTION, false);
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_SAVE_CURRENT_CONFIG), PARSE_ACTION, false);
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_SAVE_NEW_CONFIG), PARSE_ACTION, false);
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_HELP_LIST), PARSE_ACTION, false);
#if !defined(IOS)
         menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_QUIT_RETROARCH), PARSE_ACTION, false);
#endif
         info->need_push    = true;
         break;
      case DISPLAYLIST_PLAYLIST_SETTINGS_LIST:
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_HISTORY_LIST_ENABLE), PARSE_ONLY_BOOL, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_CONTENT_HISTORY_SIZE), PARSE_ONLY_UINT, false);
         {
            menu_displaylist_parse_playlist_associations(info);
         }
         info->need_push    = true;
         break;
      case DISPLAYLIST_INPUT_HOTKEY_BINDS_LIST:
         {
            unsigned i;

            for (i = 0; i < RARCH_BIND_LIST_END; i++)
            {
               const struct input_bind_map* keybind = (const struct input_bind_map*)
                  &input_config_bind_map[i];
               ret = menu_displaylist_parse_settings(menu, info,
                     keybind->base, PARSE_ONLY_BIND, false);
               (void)ret;
            }
         }
         info->need_push    = true;
         break;
      case DISPLAYLIST_INPUT_SETTINGS_LIST:
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_MAX_USERS), PARSE_ONLY_UINT, false);
#if TARGET_OS_IPHONE
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_SMALL_KEYBOARD_ENABLE), PARSE_ONLY_BOOL, false);
#endif
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_ICADE_ENABLE), PARSE_ONLY_BOOL, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_KEYBOARD_GAMEPAD_MAPPING_TYPE), PARSE_ONLY_UINT, false);
#ifdef ANDROID
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_BACK_AS_MENU_TOGGLE_ENABLE), PARSE_ONLY_BOOL, false);
#endif
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_MENU_TOGGLE_GAMEPAD_COMBO), PARSE_ONLY_UINT, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_REMAP_BINDS_ENABLE), PARSE_ONLY_BOOL, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_AUTODETECT_ENABLE), PARSE_ONLY_BOOL, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_DESCRIPTOR_LABEL_SHOW), PARSE_ONLY_BOOL, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_DESCRIPTOR_HIDE_UNBOUND), PARSE_ONLY_BOOL, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_AXIS_THRESHOLD), PARSE_ONLY_FLOAT, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_TURBO_PERIOD), PARSE_ONLY_UINT, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_DUTY_CYCLE), PARSE_ONLY_UINT, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_BIND_MODE), PARSE_ONLY_UINT, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_HOTKEY_BINDS), PARSE_ACTION, false);

         {
            unsigned user;
            for (user = 0; user < settings->input.max_users; user++)
            {
               char binds_list[PATH_MAX_LENGTH];
               snprintf(binds_list,  sizeof(binds_list), "%d_input_binds_list", user + 1);
               menu_displaylist_parse_settings(menu, info,
                     binds_list, PARSE_ACTION, false);
            }
         }

         info->need_refresh = true;
         info->need_push    = true;
         break;
      case DISPLAYLIST_SETTINGS_ALL:
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_DRIVER_SETTINGS),          PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_VIDEO_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_AUDIO_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_INPUT_SETTINGS),   PARSE_ACTION, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_INPUT_HOTKEY_BINDS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_CORE_SETTINGS),            PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_CONFIGURATION_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_SAVING_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_LOGGING_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_FRAME_THROTTLE_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_REWIND_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_RECORDING_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_ONSCREEN_DISPLAY_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_OVERLAY_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_MENU_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_UI_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_MENU_FILE_BROWSER_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_ACCOUNTS_RETRO_ACHIEVEMENTS),  PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_CORE_UPDATER_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_NETWORK_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_PLAYLIST_SETTINGS),   PARSE_ACTION, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_USER_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_DIRECTORY_SETTINGS),   PARSE_ONLY_GROUP, false);
         ret = menu_displaylist_parse_settings(menu, info,
               menu_hash_to_str(MENU_LABEL_VALUE_PRIVACY_SETTINGS),   PARSE_ONLY_GROUP, false);
         info->need_push    = true;
         break;
      case DISPLAYLIST_HORIZONTAL:
         ret = menu_displaylist_parse_horizontal_list(info);

         info->need_sort    = true;
         info->need_refresh = true;
         info->need_push    = true;
         break;
      case DISPLAYLIST_HORIZONTAL_CONTENT_ACTIONS:
         ret = menu_displaylist_parse_horizontal_content_actions(info);
         info->need_refresh = true;
         info->need_push    = true;
         break;
      case DISPLAYLIST_CONTENT_SETTINGS:
         ret = menu_displaylist_parse_load_content_settings(info);

         info->need_refresh = true;
         info->need_push    = true;
         break;
      case DISPLAYLIST_INFORMATION_LIST:
         ret = menu_displaylist_parse_information_list(info);

         info->need_push    = true;
         info->need_refresh = true;
         break;
      case DISPLAYLIST_ADD_CONTENT_LIST:
         ret = menu_displaylist_parse_add_content_list(info);

         info->need_push    = true;
         info->need_refresh = true;
         break;
      case DISPLAYLIST_SCAN_DIRECTORY_LIST:
         ret = menu_displaylist_parse_scan_directory_list(info);

         info->need_push    = true;
         info->need_refresh = true;
         break;
      case DISPLAYLIST_LOAD_CONTENT_LIST:
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_LOAD_CONTENT),
               menu_hash_to_str(MENU_LABEL_LOAD_CONTENT),
               MENU_SETTING_ACTION, 0, 0);

         if (core_info_list_num_info_files(global->core_info.list))
         {
            menu_entries_push(info->list,
                  menu_hash_to_str(MENU_LABEL_VALUE_DETECT_CORE_LIST),
                  menu_hash_to_str(MENU_LABEL_DETECT_CORE_LIST),
                  MENU_SETTING_ACTION, 0, 0);

            menu_entries_push(info->list,
                  menu_hash_to_str(MENU_LABEL_VALUE_DOWNLOADED_FILE_DETECT_CORE_LIST),
                  menu_hash_to_str(MENU_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST),
                  MENU_SETTING_ACTION, 0, 0);
         }

#ifdef HAVE_LIBRETRODB
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_CONTENT_COLLECTION_LIST),
               menu_hash_to_str(MENU_LABEL_CONTENT_COLLECTION_LIST),
               MENU_SETTING_ACTION, 0, 0);
#endif

         info->need_push    = true;
         info->need_refresh = true;
         break;
      case DISPLAYLIST_OPTIONS:
         ret = menu_displaylist_parse_options(info);

         info->need_push    = true;
         break;
      case DISPLAYLIST_OPTIONS_CHEATS:
         ret = menu_displaylist_parse_options_cheats(info);

         info->need_push    = true;
         break;
      case DISPLAYLIST_OPTIONS_REMAPPINGS:
         ret = menu_displaylist_parse_options_remappings(info);

         info->need_push    = true;
         break;
      case DISPLAYLIST_SHADER_PARAMETERS:
      case DISPLAYLIST_SHADER_PARAMETERS_PRESET:
#ifdef HAVE_SHADER_MANAGER
         if (shader)
            ret = deferred_push_video_shader_parameters_common(info, shader,
                  (type == DISPLAYLIST_SHADER_PARAMETERS)
                  ? MENU_SETTINGS_SHADER_PARAMETER_0 : MENU_SETTINGS_SHADER_PRESET_PARAMETER_0
                  );
         else
         {
            menu_entries_push(info->list,
                  menu_hash_to_str(MENU_LABEL_VALUE_NO_SHADER_PARAMETERS),
                  "", 0, 0, 0);
            ret = 0;
         }

         info->need_push = true;
#endif
         break;
      case DISPLAYLIST_PERFCOUNTERS_CORE:
      case DISPLAYLIST_PERFCOUNTERS_FRONTEND:
         menu_displaylist_push_perfcounter(info,
               (type == DISPLAYLIST_PERFCOUNTERS_CORE) ?
               retro_get_perf_counter_libretro() : retro_get_perf_counter_rarch(),
               (type == DISPLAYLIST_PERFCOUNTERS_CORE) ?
               retro_get_perf_count_libretro()   : retro_get_perf_count_rarch(),
               (type == DISPLAYLIST_PERFCOUNTERS_CORE) ?
               MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_BEGIN :
               MENU_SETTINGS_PERF_COUNTERS_BEGIN);
         ret = 0;

         info->need_refresh = false;
         info->need_push    = true;
         break;
      case DISPLAYLIST_DATABASE_ENTRY:
         {
            struct string_list *str_list  = string_split(info->label, "|");

            if (!str_list)
               return -1;

            strlcpy(info->path_b,   str_list->elems[1].data, sizeof(info->path_b));
            strlcpy(info->label,    str_list->elems[0].data, sizeof(info->label));

            string_list_free(str_list);
         }
         ret = menu_displaylist_parse_database_entry(info);

         info->need_push    = true;
         break;
      case DISPLAYLIST_DATABASE_QUERY:
         ret = menu_database_parse_query(info->list,
               info->path, (info->path_c[0] == '\0') ? NULL : info->path_c);
         strlcpy(info->path, info->path_b, sizeof(info->path));

         info->need_sort    = true;
         info->need_refresh = true;
         info->need_push    = true;
         break;
      case DISPLAYLIST_OPTIONS_SHADERS:
         ret = menu_displaylist_parse_shader_options(info);

         info->need_push    = true;
         break;
      case DISPLAYLIST_CORE_CONTENT:
#ifdef HAVE_NETWORKING
         print_buf_lines(info->list, core_buf, core_len, MENU_FILE_DOWNLOAD_CORE_CONTENT);
         info->need_push    = true;
         info->need_refresh = true;
#endif
         break;
      case DISPLAYLIST_CORES_UPDATER:
#ifdef HAVE_NETWORKING
         print_buf_lines(info->list, core_buf, core_len, MENU_FILE_DOWNLOAD_CORE);
         info->need_push    = true;
         info->need_refresh = true;
#endif
         break;
      case DISPLAYLIST_PLAYLIST_COLLECTION:
         if (!strcmp(info->path, "content_history.lpl"))
         {
            if (menu_displaylist_push_list(info, DISPLAYLIST_HISTORY) == 0)
               menu_displaylist_push_list_process(info);
            return 0;
         }
         else
         {
            char path_playlist[PATH_MAX_LENGTH];
            content_playlist_t *playlist        = NULL;

            if (menu->playlist)
               content_playlist_free(menu->playlist);

            fill_pathname_join(path_playlist,
                  settings->playlist_directory, info->path,
                  sizeof(path_playlist));
            menu->playlist  = content_playlist_init(path_playlist,
                  COLLECTION_SIZE);
            strlcpy(menu->db_playlist_file, path_playlist, sizeof(menu->db_playlist_file));
            strlcpy(path_playlist,
                  menu_hash_to_str(MENU_LABEL_COLLECTION), sizeof(path_playlist));
            playlist = menu->playlist;

            content_playlist_qsort(playlist, menu_displaylist_sort_playlist);

            ret = menu_displaylist_parse_playlist(info, playlist, path_playlist, false);

            if (ret == 0)
            {
               info->need_sort    = true;
               info->need_refresh = true;
               info->need_push    = true;
            }
         }
         break;
      case DISPLAYLIST_HISTORY:
         {
            char path_playlist[PATH_MAX_LENGTH];
            content_playlist_t *playlist        = g_defaults.history;

            if (!playlist)
               event_command(EVENT_CMD_HISTORY_INIT);

            strlcpy(path_playlist, "history", sizeof(path_playlist));

            ret = menu_displaylist_parse_playlist(info, playlist, path_playlist, true);

            if (ret == 0)
            {
               info->need_refresh = true;
               info->need_push    = true;
            }
         }
         break;
      case DISPLAYLIST_OPTIONS_DISK:
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_DISK_INDEX),
               menu_hash_to_str(MENU_LABEL_DISK_INDEX),
               MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_INDEX, 0, 0);
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_DISK_CYCLE_TRAY_STATUS),
               menu_hash_to_str(MENU_LABEL_DISK_CYCLE_TRAY_STATUS),
               MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_CYCLE_TRAY_STATUS, 0, 0);
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_DISK_IMAGE_APPEND),
               menu_hash_to_str(MENU_LABEL_DISK_IMAGE_APPEND),
               MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_IMAGE_APPEND, 0, 0);

         info->need_push    = true;
         break;
      case DISPLAYLIST_SYSTEM_INFO:
         menu_displaylist_parse_system_info(info);
         info->need_push    = true;
         info->need_refresh = true;
         break;
      case DISPLAYLIST_DEBUG_INFO:
         menu_displaylist_parse_debug_info(info);
         info->need_push    = true;
         info->need_refresh = true;
         break;
         
#ifdef HAVE_CHEEVOS
      case DISPLAYLIST_ACHIEVEMENT_LIST:
         cheevos_populate_menu(info);
         info->need_push    = true;
         info->need_refresh = true;
         break;
#endif

      case DISPLAYLIST_CORES_SUPPORTED:
      case DISPLAYLIST_CORES_COLLECTION_SUPPORTED:
         info->need_sort    = true;
         info->need_refresh = true;
         info->need_push    = true;

         {
            unsigned cores_names_len;
            size_t cores_names_size;
            unsigned cores_paths_len;
            size_t cores_paths_size;
            struct string_list *cores_names = string_list_new_special(STRING_LIST_SUPPORTED_CORES_NAMES,
                  (void*)menu->deferred_path, &cores_names_len, &cores_names_size);
            struct string_list *cores_paths = string_list_new_special(STRING_LIST_SUPPORTED_CORES_PATHS,
                  (void*)menu->deferred_path, &cores_paths_len, &cores_paths_size);

            if (cores_names_size == 0)
            {
               menu_entries_push(info->list,
                     menu_hash_to_str(MENU_LABEL_VALUE_NO_CORES_AVAILABLE),
                     "",
                     0, 0, 0);
            }
            else
            {
               for (i = 0; i < cores_names_size; i++)
               {
                  if (type == DISPLAYLIST_CORES_COLLECTION_SUPPORTED)
                     menu_entries_push(info->list, cores_paths->elems[i].data, "",
                           MENU_FILE_CORE, 0, 0);
                  else
                     menu_entries_push(info->list, cores_paths->elems[i].data,
                           menu_hash_to_str(MENU_LABEL_DETECT_CORE_LIST_OK),
                           MENU_FILE_CORE, 0, 0);
                  menu_entries_set_alt_at_offset(info->list, i,
                        cores_names->elems[i].data);
               }

               string_list_free(cores_names);
               string_list_free(cores_paths);
            }
         }
         break;
      case DISPLAYLIST_CORE_INFO:
         menu_displaylist_parse_core_info(info);
         info->need_push = true;
         break;
      case DISPLAYLIST_CORE_OPTIONS:
         if (system && system->core_options)
         {
            size_t opts = core_option_size(system->core_options);

            if (settings->game_specific_options)
            {
               menu_entries_push(info->list,
                     menu_hash_to_str(MENU_LABEL_VALUE_GAME_SPECIFIC_OPTIONS_CREATE), "",
                     MENU_SETTINGS_CORE_OPTION_CREATE, 0, 0);
            }
            if (opts == 0)
            {
               menu_entries_push(info->list,
                     menu_hash_to_str(MENU_LABEL_VALUE_NO_CORE_OPTIONS_AVAILABLE), "",
                     MENU_SETTINGS_CORE_OPTION_NONE, 0, 0);
            }
            else
            {
               for (i = 0; i < opts; i++)
                  menu_entries_push(info->list,
                        core_option_get_desc(system->core_options, i), "",
                        MENU_SETTINGS_CORE_OPTION_START + i, 0, 0);
            }
         }
         else
            menu_entries_push(info->list,
                  menu_hash_to_str(MENU_LABEL_VALUE_NO_CORE_OPTIONS_AVAILABLE), "",
                  MENU_SETTINGS_CORE_OPTION_NONE, 0, 0);
         info->need_push = true;
         break;
      case DISPLAYLIST_DATABASES:
         info->type_default = MENU_FILE_RDB;
         strlcpy(info->exts, "rdb", sizeof(info->exts));
         strlcpy(info->path, settings->content_database, sizeof(info->path));
         break;
      case DISPLAYLIST_ARCHIVE_ACTION:
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_OPEN_ARCHIVE),
               menu_hash_to_str(MENU_LABEL_OPEN_ARCHIVE),
               0, 0, 0);
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_LOAD_ARCHIVE),
               menu_hash_to_str(MENU_LABEL_LOAD_ARCHIVE),
               0, 0, 0);
         info->need_push = true;
         break;
      case DISPLAYLIST_ARCHIVE_ACTION_DETECT_CORE:
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_OPEN_ARCHIVE),
               menu_hash_to_str(MENU_LABEL_OPEN_ARCHIVE_DETECT_CORE),
               0, 0, 0);
         menu_entries_push(info->list,
               menu_hash_to_str(MENU_LABEL_VALUE_LOAD_ARCHIVE),
               menu_hash_to_str(MENU_LABEL_LOAD_ARCHIVE_DETECT_CORE),
               0, 0, 0);
         info->need_push = true;
         break;
      case DISPLAYLIST_DATABASE_CURSORS:
         info->type_default = MENU_FILE_CURSOR;
         strlcpy(info->exts, "dbc", sizeof(info->exts));
         strlcpy(info->path, settings->cursor_directory, sizeof(info->path));
         break;
      case DISPLAYLIST_DATABASE_PLAYLISTS:
         info->type_default = MENU_FILE_PLAIN;
         strlcpy(info->exts, "lpl", sizeof(info->exts));
         break;
      case DISPLAYLIST_CORES:
         info->type_default = MENU_FILE_PLAIN;
         strlcpy(info->exts, EXT_EXECUTABLES, sizeof(info->exts));
         break;
      case DISPLAYLIST_CONFIG_FILES:
         info->type_default = MENU_FILE_CONFIG;
         strlcpy(info->exts, "cfg", sizeof(info->exts));
         break;
      case DISPLAYLIST_SHADER_PRESET:
         info->type_default = MENU_FILE_SHADER_PRESET;
         strlcpy(info->exts, "cgp|glslp", sizeof(info->exts));
         break;
      case DISPLAYLIST_SHADER_PASS:
         info->type_default = MENU_FILE_SHADER;
         strlcpy(info->exts, "cg|glsl", sizeof(info->exts));
         break;
      case DISPLAYLIST_VIDEO_FILTERS:
         info->type_default = MENU_FILE_VIDEOFILTER;
         strlcpy(info->exts, "filt", sizeof(info->exts));
         break;
      case DISPLAYLIST_IMAGES:
         info->type_default = MENU_FILE_IMAGE;
         strlcpy(info->exts, "png", sizeof(info->exts));
         break;
      case DISPLAYLIST_AUDIO_FILTERS:
         info->type_default = MENU_FILE_AUDIOFILTER;
         strlcpy(info->exts, "dsp", sizeof(info->exts));
         break;
      case DISPLAYLIST_CHEAT_FILES:
         info->type_default = MENU_FILE_CHEAT;
         strlcpy(info->exts, "cht", sizeof(info->exts));
         break;
      case DISPLAYLIST_CONTENT_HISTORY:
         info->type_default = MENU_FILE_PLAIN;
         strlcpy(info->exts, "lpl", sizeof(info->exts));
         break;
      case DISPLAYLIST_FONTS:
         info->type_default = MENU_FILE_FONT;
         strlcpy(info->exts, "ttf", sizeof(info->exts));
         break;
      case DISPLAYLIST_OVERLAYS:
         info->type_default = MENU_FILE_OVERLAY;
         strlcpy(info->exts, "cfg", sizeof(info->exts));
         break;
      case DISPLAYLIST_RECORD_CONFIG_FILES:
         info->type_default = MENU_FILE_RECORD_CONFIG;
         strlcpy(info->exts, "cfg", sizeof(info->exts));
         break;
      case DISPLAYLIST_REMAP_FILES:
         info->type_default = MENU_FILE_REMAP;
         strlcpy(info->exts, "rmp", sizeof(info->exts));
         break;
   }
