switch (menu->help_screen_type)
   {
      case MENU_HELP_WELCOME:
         {
            static int64_t timeout_end;
            int64_t timeout;
            static bool timer_begin = false;
            static bool timer_end   = false;
            int64_t current         = retro_get_time_usec();

            if (!timer_begin)
            {
               timeout_end = retro_get_time_usec() +
                  3 /* seconds */ * 1000000;
               timer_begin = true;
               timer_end   = false;
            }

            timeout = (timeout_end - current) / 1000000;

            menu_hash_get_help(MENU_LABEL_WELCOME_TO_RETROARCH,
                  s, len);

            if (!timer_end && timeout <= 0)
            {
               timer_end   = true;
               timer_begin = false;
               timeout_end = 0;
               menu->help_screen_type = MENU_HELP_NONE;
               return 1;
            }
         }
         break;
      case MENU_HELP_CONTROLS:
         {
            unsigned i;
            char s2[PATH_MAX_LENGTH];
            const unsigned binds[] = {
               RETRO_DEVICE_ID_JOYPAD_UP,
               RETRO_DEVICE_ID_JOYPAD_DOWN,
               RETRO_DEVICE_ID_JOYPAD_A,
               RETRO_DEVICE_ID_JOYPAD_B,
               RETRO_DEVICE_ID_JOYPAD_SELECT,
               RETRO_DEVICE_ID_JOYPAD_START,
               RARCH_MENU_TOGGLE,
               RARCH_QUIT_KEY,
               RETRO_DEVICE_ID_JOYPAD_X,
               RETRO_DEVICE_ID_JOYPAD_Y,
            };
            char desc[ARRAY_SIZE(binds)][64] = {{0}};

            for (i = 0; i < ARRAY_SIZE(binds); i++)
            {
               const struct retro_keybind *keybind = (const struct retro_keybind*)
                  &settings->input.binds[0][binds[i]];
               const struct retro_keybind *auto_bind = (const struct retro_keybind*)
                  input_get_auto_bind(0, binds[i]);

               input_get_bind_string(desc[i], keybind, auto_bind, sizeof(desc[i]));
            }

            menu_hash_get_help(MENU_LABEL_VALUE_MENU_CONTROLS_PROLOG,
                  s2, sizeof(s2));

            snprintf(s, len,
                  "%s"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n",
                  s2,
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_SCROLL_UP),    desc[0],
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_SCROLL_DOWN),  desc[1],
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_CONFIRM),      desc[2],
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_BACK),         desc[3],
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_INFO),         desc[4],
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_START),        desc[5],
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_TOGGLE_MENU),  desc[6],
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_QUIT),         desc[7],
                  menu_hash_to_str(MENU_LABEL_VALUE_BASIC_MENU_CONTROLS_TOGGLE_KEYBOARD), desc[8]
                  );
         }
         break;
         
#ifdef HAVE_CHEEVOS
      case MENU_HELP_CHEEVOS_DESCRIPTION:
         cheevos_get_description(menu->help_screen_id, s, len);
         break;
#endif

      case MENU_HELP_WHAT_IS_A_CORE:
         menu_hash_get_help(MENU_LABEL_VALUE_WHAT_IS_A_CORE_DESC,
               s, len);
         break;
      case MENU_HELP_LOADING_CONTENT:
         menu_hash_get_help(MENU_LABEL_LOAD_CONTENT,
               s, len);
         break;
      case MENU_HELP_CHANGE_VIRTUAL_GAMEPAD:
         menu_hash_get_help(MENU_LABEL_VALUE_HELP_CHANGE_VIRTUAL_GAMEPAD_DESC,
               s, len);
         break;
      case MENU_HELP_AUDIO_VIDEO_TROUBLESHOOTING:
         menu_hash_get_help(MENU_LABEL_VALUE_HELP_AUDIO_VIDEO_TROUBLESHOOTING_DESC,
               s, len);
         break;
      case MENU_HELP_SCANNING_CONTENT:
         menu_hash_get_help(MENU_LABEL_VALUE_HELP_SCANNING_CONTENT_DESC,
               s, len);
         break;
      case MENU_HELP_EXTRACT:
         menu_hash_get_help(MENU_LABEL_VALUE_EXTRACTING_PLEASE_WAIT,
               s, len);
         break;
      case MENU_HELP_NONE:
      default:
         break;
   }
