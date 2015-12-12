switch(rgui->menu_type)
   {
      case INGAME_MENU_CUSTOM_RATIO:
         return ingame_menu_resize(rgui, rgui->trigger_state);
      case INGAME_MENU_CORE_OPTIONS:
         return ingame_menu_core_options(rgui, rgui->trigger_state);
      case INGAME_MENU_LOAD_GAME_HISTORY:
         return ingame_menu_history_options(rgui, rgui->trigger_state);
      case INGAME_MENU_SCREENSHOT:
         return ingame_menu_screenshot(rgui, rgui->trigger_state);
      case FILE_BROWSER_MENU:
         return select_rom(rgui, rgui->trigger_state);
      case LIBRETRO_CHOICE:
#ifdef HAVE_SHADER_MANAGER
      case CGP_CHOICE:
      case SHADER_CHOICE:
#endif
      case INPUT_PRESET_CHOICE:
      case BORDER_CHOICE:
         return select_file(rgui, rgui->trigger_state);
      case PATH_DEFAULT_ROM_DIR_CHOICE:
      case PATH_SAVESTATES_DIR_CHOICE:
      case PATH_SRAM_DIR_CHOICE:
#ifdef HAVE_XML
      case PATH_CHEATS_DIR_CHOICE:
#endif
      case PATH_SYSTEM_DIR_CHOICE:
         return select_directory(rgui, rgui->trigger_state);
      case INGAME_MENU:
      case INGAME_MENU_SETTINGS:
      case INGAME_MENU_VIDEO_OPTIONS:
      case INGAME_MENU_SHADER_OPTIONS:
      case INGAME_MENU_AUDIO_OPTIONS:
      case INGAME_MENU_INPUT_OPTIONS:
      case INGAME_MENU_PATH_OPTIONS:
         return select_setting(rgui, rgui->trigger_state);
   }
