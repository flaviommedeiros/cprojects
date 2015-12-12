if (setting >= RGUI_SETTINGS_VIDEO_OPTIONS_FIRST && setting <= RGUI_SETTINGS_VIDEO_OPTIONS_LAST)
      return video_option_toggle_setting(rgui, setting, action);
#ifdef HAVE_SHADER_MANAGER
   else if (setting >= RGUI_SETTINGS_SHADER_FILTER && setting <= RGUI_SETTINGS_SHADER_LAST)
      return shader_manager_toggle_setting(rgui, setting, action);
#endif
