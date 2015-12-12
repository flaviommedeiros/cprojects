switch (rgui->menu_type)
   {
      case INGAME_MENU:
         first_setting = FIRST_INGAME_MENU_SETTING;
         max_settings = MAX_NO_OF_INGAME_MENU_SETTINGS;
         break;
      case INGAME_MENU_SETTINGS:
         first_setting = FIRST_SETTING;
         max_settings = MAX_NO_OF_SETTINGS;
         break;
      case INGAME_MENU_INPUT_OPTIONS:
         first_setting = FIRST_CONTROLS_SETTING_PAGE_1;
         max_settings = MAX_NO_OF_CONTROLS_SETTINGS;
         break;
      case INGAME_MENU_PATH_OPTIONS:
         first_setting = FIRST_PATH_SETTING;
         max_settings = MAX_NO_OF_PATH_SETTINGS;
         break;
      case INGAME_MENU_AUDIO_OPTIONS:
         first_setting = FIRST_AUDIO_SETTING;
         max_settings = MAX_NO_OF_AUDIO_SETTINGS;
         break;
      case INGAME_MENU_VIDEO_OPTIONS:
         first_setting = FIRST_VIDEO_SETTING;
         max_settings = MAX_NO_OF_VIDEO_SETTINGS;
         break;
#ifdef HAVE_SHADER_MANAGER
      case INGAME_MENU_SHADER_OPTIONS:
         first_setting = FIRST_SHADERMAN_SETTING;
         switch (rgui->shader.passes)
         {
            case 0:
               max_settings = MAX_NO_OF_SHADERMAN_SETTINGS;
               break;
            case 1:
               max_settings = SHADERMAN_SHADER_0_SCALE+1;
               break;
            case 2:
               max_settings = SHADERMAN_SHADER_1_SCALE+1;
               break;
            case 3:
               max_settings = SHADERMAN_SHADER_2_SCALE+1;
               break;
            case 4:
               max_settings = SHADERMAN_SHADER_3_SCALE+1;
               break;
            case 5:
               max_settings = SHADERMAN_SHADER_4_SCALE+1;
               break;
            case 6:
               max_settings = SHADERMAN_SHADER_5_SCALE+1;
               break;
            case 7:
               max_settings = SHADERMAN_SHADER_6_SCALE+1;
               break;
            case 8:
               max_settings = SHADERMAN_SHADER_7_SCALE+1;
               break;
         }
         break;
#endif
   }
