if (rgui->need_refresh && !(menu_type == RGUI_FILE_DIRECTORY ||
#ifdef HAVE_SHADER_MANAGER
            menu_type_is_shader_browser(menu_type) ||
#endif
            menu_type_is_directory_browser(menu_type) ||
#ifdef HAVE_OVERLAY
            menu_type == RGUI_SETTINGS_OVERLAY_PRESET ||
#endif
            menu_type == RGUI_SETTINGS_CORE || menu_type == RGUI_SETTINGS_DISK_APPEND ||
            menu_type == RGUI_SETTINGS_OPEN_HISTORY))
   {
      rgui->need_refresh = false;
      if (menu_type == RGUI_SETTINGS_INPUT_OPTIONS)
         rgui_settings_controller_populate_entries(rgui);
      else if (menu_type == RGUI_SETTINGS_PATH_OPTIONS)
         rgui_settings_path_populate_entries(rgui);
      else if (menu_type == RGUI_SETTINGS_OPTIONS)
         rgui_settings_options_populate_entries(rgui);
      else if (menu_type == RGUI_SETTINGS_CORE_OPTIONS)
         rgui_settings_core_options_populate_entries(rgui);
      else if (menu_type == RGUI_SETTINGS_AUDIO_OPTIONS)
         rgui_settings_audio_options_populate_entries(rgui);
      else if (menu_type == RGUI_SETTINGS_DISK_OPTIONS)
         rgui_settings_disc_options_populate_entries(rgui);
      else if (menu_type == RGUI_SETTINGS_VIDEO_OPTIONS)
         rgui_settings_video_options_populate_entries(rgui);
#ifdef HAVE_SHADER_MANAGER
      else if (menu_type == RGUI_SETTINGS_SHADER_OPTIONS)
         rgui_settings_shader_manager_populate_entries(rgui);
#endif
      else
         rgui_settings_populate_entries(rgui);
   }
