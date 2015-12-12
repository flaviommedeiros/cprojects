switch (device)
      {
#ifdef HW_RVL
         case DEVICE_WIIMOTE:
            g_settings.input.device[port] = device;
            strlcpy(g_settings.input.device_names[port], "Wiimote", sizeof(g_settings.input.device_names[port]));
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_1].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_A].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_MINUS].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_PLUS].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_UP].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_DOWN].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_LEFT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_RIGHT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_2].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_B].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = NO_BTN;
            break;
         case DEVICE_NUNCHUK:
            g_settings.input.device[port] = device;
            strlcpy(g_settings.input.device_names[port], "Wiimote + Nunchuk", sizeof(g_settings.input.device_names[port]));
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_B].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_2].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_MINUS].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_PLUS].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_UP].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_DOWN].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_LEFT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_RIGHT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_A].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_1].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_Z].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_C].joykey;;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = NO_BTN; break;
         case DEVICE_CLASSIC:
            g_settings.input.device[port] = device;
            strlcpy(g_settings.input.device_names[port], "Classic Controller", sizeof(g_settings.input.device_names[port]));
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_B].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_Y].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_MINUS].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_PLUS].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_UP].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_DOWN].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey   = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_LEFT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_RIGHT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_A].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_X].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_L_TRIGGER].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_R_TRIGGER].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_ZL_TRIGGER].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = platform_keys[GX_DEVICE_CLASSIC_ID_JOYPAD_ZR_TRIGGER].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = NO_BTN;
            break;
#endif
         case DEVICE_GAMECUBE:
            g_settings.input.device[port] = device;
            strlcpy(g_settings.input.device_names[port], "Gamecube Controller", sizeof(g_settings.input.device_names[port]));
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_B].def_joykey      = platform_keys[GX_DEVICE_GC_ID_JOYPAD_B].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_Y].def_joykey      = platform_keys[GX_DEVICE_GC_ID_JOYPAD_Y].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_SELECT].def_joykey = platform_keys[GX_DEVICE_GC_ID_JOYPAD_Z_TRIGGER].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_START].def_joykey  = platform_keys[GX_DEVICE_GC_ID_JOYPAD_START].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].def_joykey     = platform_keys[GX_DEVICE_GC_ID_JOYPAD_UP].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].def_joykey   = platform_keys[GX_DEVICE_GC_ID_JOYPAD_DOWN].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].def_joykey  = platform_keys[GX_DEVICE_GC_ID_JOYPAD_LEFT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].def_joykey  = platform_keys[GX_DEVICE_GC_ID_JOYPAD_RIGHT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_A].def_joykey      = platform_keys[GX_DEVICE_GC_ID_JOYPAD_A].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_X].def_joykey      = platform_keys[GX_DEVICE_GC_ID_JOYPAD_X].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L].def_joykey      = platform_keys[GX_DEVICE_GC_ID_JOYPAD_L_TRIGGER].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R].def_joykey      = platform_keys[GX_DEVICE_GC_ID_JOYPAD_R_TRIGGER].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R2].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_L3].def_joykey     = NO_BTN;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_R3].def_joykey     = NO_BTN;
            break;
         default:
            break;
      }
