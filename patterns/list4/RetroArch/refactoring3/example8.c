switch (device)
      {
#ifdef HAVE_BB10
         case DEVICE_WIIMOTE:
            //TODO:Have enum lookup for string
            strlcpy(g_settings.input.device_names[port], "Wiimote",
               sizeof(g_settings.input.device_names[port]));
            g_settings.input.device[port] = device;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = SCREEN_X_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = SCREEN_B_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = SCREEN_MENU1_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = SCREEN_MENU2_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = SCREEN_DPAD_UP_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = SCREEN_DPAD_DOWN_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = SCREEN_DPAD_LEFT_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = SCREEN_DPAD_RIGHT_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = SCREEN_Y_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = SCREEN_A_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = SCREEN_L1_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = SCREEN_R1_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = SCREEN_L2_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = SCREEN_R2_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = SCREEN_L3_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = SCREEN_R3_GAME_BUTTON;
            g_settings.input.binds[port][RARCH_MENU_TOGGLE].def_joykey             = SCREEN_MENU3_GAME_BUTTON;
            g_settings.input.dpad_emulation[port] = ANALOG_DPAD_NONE;
            controller->port = port;
            port_device[port] = controller;
            break;
         case DEVICE_KEYPAD:
            strlcpy(g_settings.input.device_names[port], "BlackBerry Q10 Keypad",
               sizeof(g_settings.input.device_names[port]));
            g_settings.input.device[port] = device;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = KEYCODE_M & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = KEYCODE_J & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = KEYCODE_RIGHT_SHIFT & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = KEYCODE_RETURN & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = KEYCODE_W & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = KEYCODE_S & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = KEYCODE_A & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = KEYCODE_D & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = KEYCODE_N & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = KEYCODE_K & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = KEYCODE_U & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = KEYCODE_I & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RARCH_MENU_TOGGLE].def_joykey             = KEYCODE_P & 0xFF;
            g_settings.input.dpad_emulation[port] = ANALOG_DPAD_NONE;
            controller->port = port;
            port_device[port] = controller;
            break;
#endif
         case DEVICE_KEYBOARD:
            strlcpy(g_settings.input.device_names[port], "BlackBerry BT Keyboard",
               sizeof(g_settings.input.device_names[port]));
            g_settings.input.device[port] = device;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = KEYCODE_Z & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = KEYCODE_A & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = KEYCODE_RIGHT_SHIFT & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = KEYCODE_RETURN & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = KEYCODE_UP & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = KEYCODE_DOWN & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = KEYCODE_LEFT & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = KEYCODE_RIGHT & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = KEYCODE_X & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = KEYCODE_S & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = KEYCODE_Q & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = KEYCODE_W & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RARCH_MENU_TOGGLE].def_joykey             = KEYCODE_TILDE;
            g_settings.input.dpad_emulation[port] = ANALOG_DPAD_NONE;
            controller->port = port;
            port_device[port] = controller;
            break;
         case DEVICE_IPEGA:
            strlcpy(g_settings.input.device_names[port], "iPega PG-9017",
               sizeof(g_settings.input.device_names[port]));
            g_settings.input.device[port] = device;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = KEYCODE_J & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = KEYCODE_M & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = KEYCODE_R & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = KEYCODE_Y & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = KEYCODE_UP & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = KEYCODE_DOWN & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = KEYCODE_LEFT & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = KEYCODE_RIGHT & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = KEYCODE_K & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = KEYCODE_I & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = KEYCODE_Q & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = KEYCODE_P & 0xFF;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = 0;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = 0;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = 0;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = 0;
            g_settings.input.binds[port][RARCH_MENU_TOGGLE].def_joykey             = 0;
            g_settings.input.dpad_emulation[port] = ANALOG_DPAD_NONE;
            controller->port = port;
            port_device[port] = controller;
            break;
#ifdef HAVE_BB10
         case DEVICE_UNKNOWN:
            strlcpy(g_settings.input.device_names[port], "Unknown",
               sizeof(g_settings.input.device_names[port]));
            g_settings.input.device[port] = device;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = SCREEN_B_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = SCREEN_Y_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = SCREEN_MENU1_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = SCREEN_MENU2_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = SCREEN_DPAD_UP_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = SCREEN_DPAD_DOWN_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = SCREEN_DPAD_LEFT_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = SCREEN_DPAD_RIGHT_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = SCREEN_A_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = SCREEN_X_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = SCREEN_L1_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = SCREEN_R1_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = SCREEN_L2_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = SCREEN_R2_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = SCREEN_L3_GAME_BUTTON;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = SCREEN_R3_GAME_BUTTON;
            g_settings.input.binds[port][RARCH_MENU_TOGGLE].def_joykey             = NO_BTN; //TODO: Find a good mappnig
            g_settings.input.dpad_emulation[port] = ANALOG_DPAD_NONE;
            controller->port = port;
            port_device[port] = controller;
            break;
         case DEVICE_NONE:
         default:
            strlcpy(g_settings.input.device_names[port], "None",
               sizeof(g_settings.input.device_names[port]));
            g_settings.input.device[port] = device;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RARCH_MENU_TOGGLE].def_joykey     = NO_BTN;
            controller->port = -1;
            port_device[port] = 0;
            break;
#endif
      }
