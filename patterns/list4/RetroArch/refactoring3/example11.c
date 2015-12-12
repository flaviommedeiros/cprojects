switch(menu_type)
   {
      case LIBRETRO_CHOICE:
      case INGAME_MENU_CORE_OPTIONS:
      case INGAME_MENU_LOAD_GAME_HISTORY:
      case INGAME_MENU_CUSTOM_RATIO:
      case INGAME_MENU_SCREENSHOT:
         rgui->frame_buf_show = true;
         break;
      case INGAME_MENU_SETTINGS:
      case INGAME_MENU_VIDEO_OPTIONS:
      case INGAME_MENU_AUDIO_OPTIONS:
      case INGAME_MENU_INPUT_OPTIONS:
      case INGAME_MENU_PATH_OPTIONS:
         selected = FIRST_INGAME_MENU_SETTING;
         rgui->frame_buf_show = true;
         break;
      case INGAME_MENU_SHADER_OPTIONS:
         selected = FIRST_VIDEO_SETTING;
         break;
#ifdef HAVE_SHADER_MANAGER
      case CGP_CHOICE:
         selected = FIRST_SHADERMAN_SETTING;
         break;
#endif
      default:
         break;
   }
