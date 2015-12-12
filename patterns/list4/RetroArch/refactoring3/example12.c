switch (menu_type)
   {
      case INGAME_MENU:
         selected = FIRST_INGAME_MENU_SETTING;
         break;
      case INGAME_MENU_VIDEO_OPTIONS:
         selected = FIRST_VIDEO_SETTING;
         break;
#ifdef HAVE_SHADER_MANAGER
      case INGAME_MENU_SHADER_OPTIONS:
         selected = FIRST_SHADERMAN_SETTING;
         break;
#endif
      case INGAME_MENU_AUDIO_OPTIONS:
         selected = FIRST_AUDIO_SETTING;
         break;
      case INGAME_MENU_INPUT_OPTIONS:
         selected = FIRST_CONTROLS_SETTING_PAGE_1;
         break;
      case INGAME_MENU_PATH_OPTIONS:
         selected = FIRST_PATH_SETTING;
         break;
      case INGAME_MENU_SETTINGS:
         selected = FIRST_SETTING;
         break;
      default:
         break;
   }
