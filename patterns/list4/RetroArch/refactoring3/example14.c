switch(menu_type)
   {
#ifdef HAVE_SHADER_MANAGER
      case SHADER_CHOICE:
         strlcpy(title, "Shaders", sizeof(title));
         break;
      case CGP_CHOICE:
         strlcpy(title, "CGP", sizeof(title));
         break;
#endif
      case BORDER_CHOICE:
         strlcpy(title, "Borders", sizeof(title));
         break;
      case LIBRETRO_CHOICE:
         strlcpy(title, "Libretro", sizeof(title));
         break;
      case INPUT_PRESET_CHOICE:
         strlcpy(title, "Input", sizeof(title));
         break;
      case PATH_SAVESTATES_DIR_CHOICE:
      case PATH_DEFAULT_ROM_DIR_CHOICE:
#ifdef HAVE_XML
      case PATH_CHEATS_DIR_CHOICE:
#endif
      case PATH_SRAM_DIR_CHOICE:
      case PATH_SYSTEM_DIR_CHOICE:
         strlcpy(title, "Path", sizeof(title));
         break;
      case INGAME_MENU:
         strlcpy(title, "Menu", sizeof(title));
         break;
      case INGAME_MENU_CORE_OPTIONS:
         strlcpy(title, "Core", sizeof(title));
         break;
      case INGAME_MENU_LOAD_GAME_HISTORY:
         strlcpy(title, "History", sizeof(title));
         break;
      case INGAME_MENU_VIDEO_OPTIONS:
      case INGAME_MENU_VIDEO_OPTIONS_MODE:
         strlcpy(title, "Video", sizeof(title));
         break;
#ifdef HAVE_SHADER_MANAGER
      case INGAME_MENU_SHADER_OPTIONS:
      case INGAME_MENU_SHADER_OPTIONS_MODE:
         strlcpy(title, "Shader", sizeof(title));
         break;
#endif
      case INGAME_MENU_INPUT_OPTIONS:
      case INGAME_MENU_INPUT_OPTIONS_MODE:
         strlcpy(title, "Input", sizeof(title));
         break;
      case INGAME_MENU_CUSTOM_RATIO:
         strlcpy(title, "Resize", sizeof(title));
         break;
      case INGAME_MENU_SCREENSHOT:
         strlcpy(title, "Menu", sizeof(title));
         break;
      case FILE_BROWSER_MENU:
         strlcpy(title, "Game", sizeof(title));
         break;
      case INGAME_MENU_SETTINGS:
      case INGAME_MENU_SETTINGS_MODE:
         strlcpy(title, "Settings", sizeof(title));
         break;
      case INGAME_MENU_AUDIO_OPTIONS:
      case INGAME_MENU_AUDIO_OPTIONS_MODE:
         strlcpy(title, "Audio", sizeof(title));
         break;
      case INGAME_MENU_PATH_OPTIONS:
      case INGAME_MENU_PATH_OPTIONS_MODE:
         strlcpy(title, "Path", sizeof(title));
         break;
   }
