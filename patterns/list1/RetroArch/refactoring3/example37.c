switch (hash)
   {
      case MENU_LABEL_OPEN_ARCHIVE_DETECT_CORE:
         BIND_ACTION_OK(cbs, action_ok_open_archive_detect_core);
         break;
      case MENU_LABEL_OPEN_ARCHIVE:
         BIND_ACTION_OK(cbs, action_ok_open_archive);
         break;
      case MENU_LABEL_LOAD_ARCHIVE_DETECT_CORE:
         BIND_ACTION_OK(cbs, action_ok_load_archive_detect_core);
         break;
      case MENU_LABEL_LOAD_ARCHIVE:
         BIND_ACTION_OK(cbs, action_ok_load_archive);
         break;
      case MENU_LABEL_CUSTOM_BIND_ALL:
         BIND_ACTION_OK(cbs, action_ok_lookup_setting);
         break;
      case MENU_LABEL_SAVESTATE:
         BIND_ACTION_OK(cbs, action_ok_save_state);
         break;
      case MENU_LABEL_LOADSTATE:
         BIND_ACTION_OK(cbs, action_ok_load_state);
         break;
      case MENU_LABEL_RESUME_CONTENT:
         BIND_ACTION_OK(cbs, action_ok_resume_content);
         break;
      case MENU_LABEL_RESTART_CONTENT:
         BIND_ACTION_OK(cbs, action_ok_restart_content);
         break;
      case MENU_LABEL_TAKE_SCREENSHOT:
         BIND_ACTION_OK(cbs, action_ok_screenshot);
         break;
      case MENU_LABEL_FILE_LOAD_OR_RESUME:
         BIND_ACTION_OK(cbs, action_ok_file_load_or_resume);
         break;
      case MENU_LABEL_QUIT_RETROARCH:
         BIND_ACTION_OK(cbs, action_ok_quit);
         break;
      case MENU_LABEL_CLOSE_CONTENT:
         BIND_ACTION_OK(cbs, action_ok_close_content);
         break;
      case MENU_LABEL_SAVE_NEW_CONFIG:
         BIND_ACTION_OK(cbs, action_ok_save_new_config);
         break;
      case MENU_LABEL_HELP:
         BIND_ACTION_OK(cbs, action_ok_help);
         break;
      case MENU_LABEL_HELP_CONTROLS:
         BIND_ACTION_OK(cbs, action_ok_help_controls);
         break;
      case MENU_LABEL_HELP_WHAT_IS_A_CORE:
         BIND_ACTION_OK(cbs, action_ok_help_what_is_a_core);
         break;
      case MENU_LABEL_HELP_CHANGE_VIRTUAL_GAMEPAD:
         BIND_ACTION_OK(cbs, action_ok_help_change_virtual_gamepad);
         break;
      case MENU_LABEL_HELP_AUDIO_VIDEO_TROUBLESHOOTING:
         BIND_ACTION_OK(cbs, action_ok_help_audio_video_troubleshooting);
         break;
      case MENU_LABEL_HELP_SCANNING_CONTENT:
         BIND_ACTION_OK(cbs, action_ok_help_scanning_content);
         break;
      case MENU_LABEL_HELP_LOADING_CONTENT:
         BIND_ACTION_OK(cbs, action_ok_help_load_content);
         break;
      case MENU_LABEL_VIDEO_SHADER_PASS:
         BIND_ACTION_OK(cbs, action_ok_shader_pass);
         break;
      case MENU_LABEL_VIDEO_SHADER_PRESET:
         BIND_ACTION_OK(cbs, action_ok_shader_preset);
         break;
      case MENU_LABEL_CHEAT_FILE_LOAD:
         BIND_ACTION_OK(cbs, action_ok_cheat_file);
         break;
      case MENU_LABEL_AUDIO_DSP_PLUGIN:
         BIND_ACTION_OK(cbs, action_ok_audio_dsp_plugin);
         break;
      case MENU_LABEL_REMAP_FILE_LOAD:
         BIND_ACTION_OK(cbs, action_ok_remap_file);
         break;
      case MENU_LABEL_RECORD_CONFIG:
         BIND_ACTION_OK(cbs, action_ok_record_configfile);
         break;
#ifdef HAVE_NETWORKING
      case MENU_LABEL_DOWNLOAD_CORE_CONTENT:
         BIND_ACTION_OK(cbs, action_ok_core_content_list);
         break;
      case MENU_LABEL_VALUE_CORE_UPDATER_LIST:
         BIND_ACTION_OK(cbs, action_ok_core_updater_list);
         break;
#endif
      case MENU_LABEL_VIDEO_SHADER_PARAMETERS:
      case MENU_LABEL_VIDEO_SHADER_PRESET_PARAMETERS:
         BIND_ACTION_OK(cbs, action_ok_shader_parameters);
         break;
      case MENU_LABEL_ACCOUNTS_LIST:
         BIND_ACTION_OK(cbs, action_ok_push_accounts_list);
         break;
      case MENU_LABEL_INPUT_SETTINGS:
         BIND_ACTION_OK(cbs, action_ok_push_input_settings_list);
         break;
      case MENU_LABEL_PLAYLIST_SETTINGS:
         BIND_ACTION_OK(cbs, action_ok_push_playlist_settings_list);
         break;
      case MENU_LABEL_INPUT_HOTKEY_BINDS:
         BIND_ACTION_OK(cbs, action_ok_push_input_hotkey_binds_list);
         break;
      case MENU_LABEL_ACCOUNTS_RETRO_ACHIEVEMENTS:
         BIND_ACTION_OK(cbs, action_ok_push_accounts_cheevos_list);
         break;
      case MENU_LABEL_SHADER_OPTIONS:
      case MENU_VALUE_INPUT_SETTINGS:
      case MENU_LABEL_CORE_OPTIONS:
      case MENU_LABEL_CORE_CHEAT_OPTIONS:
      case MENU_LABEL_CORE_INPUT_REMAPPING_OPTIONS:
      case MENU_LABEL_CORE_INFORMATION:
      case MENU_LABEL_SYSTEM_INFORMATION:
      case MENU_LABEL_DEBUG_INFORMATION:
      case MENU_LABEL_ACHIEVEMENT_LIST:
      case MENU_LABEL_DISK_OPTIONS:
      case MENU_LABEL_SETTINGS:
      case MENU_LABEL_FRONTEND_COUNTERS:
      case MENU_LABEL_CORE_COUNTERS:
      case MENU_LABEL_MANAGEMENT:
      case MENU_LABEL_ONLINE_UPDATER:
      case MENU_LABEL_LOAD_CONTENT_LIST:
      case MENU_LABEL_ADD_CONTENT_LIST:
      case MENU_LABEL_HELP_LIST:
      case MENU_LABEL_INFORMATION_LIST:
      case MENU_LABEL_CONTENT_SETTINGS:
         BIND_ACTION_OK(cbs, action_ok_push_default);
         break;
      case MENU_LABEL_SCAN_FILE:
      case MENU_LABEL_SCAN_DIRECTORY:
      case MENU_LABEL_LOAD_CONTENT:
      case MENU_LABEL_DETECT_CORE_LIST:
         BIND_ACTION_OK(cbs, action_ok_push_content_list);
         break;
      case MENU_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST:
         BIND_ACTION_OK(cbs, action_ok_push_downloads_dir);
         break;
      case MENU_LABEL_DETECT_CORE_LIST_OK:
         BIND_ACTION_OK(cbs, action_ok_file_load_detect_core);
         break;
      case MENU_LABEL_LOAD_CONTENT_HISTORY:
      case MENU_LABEL_CURSOR_MANAGER_LIST:
      case MENU_LABEL_DATABASE_MANAGER_LIST:
         BIND_ACTION_OK(cbs, action_ok_push_generic_list);
         break;
      case MENU_LABEL_SHADER_APPLY_CHANGES:
         BIND_ACTION_OK(cbs, action_ok_shader_apply_changes);
         break;
      case MENU_LABEL_CHEAT_APPLY_CHANGES:
         BIND_ACTION_OK(cbs, action_ok_cheat_apply_changes);
         break;
      case MENU_LABEL_VIDEO_SHADER_PRESET_SAVE_AS:
         BIND_ACTION_OK(cbs, action_ok_shader_preset_save_as);
         break;
      case MENU_LABEL_CHEAT_FILE_SAVE_AS:
         BIND_ACTION_OK(cbs, action_ok_cheat_file_save_as);
         break;
      case MENU_LABEL_REMAP_FILE_SAVE_CORE:
         BIND_ACTION_OK(cbs, action_ok_remap_file_save_core);
         break;
      case MENU_LABEL_REMAP_FILE_SAVE_GAME:
         BIND_ACTION_OK(cbs, action_ok_remap_file_save_game);
         break;
      case MENU_LABEL_CONTENT_COLLECTION_LIST:
         BIND_ACTION_OK(cbs, action_ok_content_collection_list);
         break;
      case MENU_LABEL_CORE_LIST:
         BIND_ACTION_OK(cbs, action_ok_core_list);
         break;
      case MENU_LABEL_DISK_IMAGE_APPEND:
         BIND_ACTION_OK(cbs, action_ok_disk_image_append_list);
         break;
      case MENU_LABEL_CONFIGURATIONS:
         BIND_ACTION_OK(cbs, action_ok_configurations_list);
         break;
      case MENU_LABEL_SCREEN_RESOLUTION:
         BIND_ACTION_OK(cbs, action_ok_video_resolution);
         break;
      case MENU_LABEL_UPDATE_ASSETS:
         BIND_ACTION_OK(cbs, action_ok_update_assets);
         break;
      case MENU_LABEL_UPDATE_CORE_INFO_FILES:
         BIND_ACTION_OK(cbs, action_ok_update_core_info_files);
         break;
      case MENU_LABEL_UPDATE_OVERLAYS:
         BIND_ACTION_OK(cbs, action_ok_update_overlays);
         break;
      case MENU_LABEL_UPDATE_DATABASES:
         BIND_ACTION_OK(cbs, action_ok_update_databases);
         break;
      case MENU_LABEL_UPDATE_GLSL_SHADERS:
         BIND_ACTION_OK(cbs, action_ok_update_shaders_glsl);
         break;
      case MENU_LABEL_UPDATE_CG_SHADERS:
         BIND_ACTION_OK(cbs, action_ok_update_shaders_cg);
         break;
      case MENU_LABEL_UPDATE_CHEATS:
         BIND_ACTION_OK(cbs, action_ok_update_cheats);
         break;
      case MENU_LABEL_UPDATE_AUTOCONFIG_PROFILES:
         BIND_ACTION_OK(cbs, action_ok_update_autoconfig_profiles);
         break;
      case MENU_LABEL_UPDATE_AUTOCONFIG_PROFILES_HID:
         BIND_ACTION_OK(cbs, action_ok_update_autoconfig_profiles_hid);
         break;
      default:
         return -1;
   }
