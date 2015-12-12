switch (device)
      {
#ifdef HW_RVL
         case DEVICE_WIIMOTE:
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].joykey    = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_UP].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].joykey  = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_DOWN].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].joykey  = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_LEFT].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].joykey = platform_keys[GX_DEVICE_WIIMOTE_ID_JOYPAD_RIGHT].joykey;
            break;
         case DEVICE_NUNCHUK:
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].joykey    = platform_keys[GX_DEVICE_WIIMOTE_ID_LSTICK_UP_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].joykey  = platform_keys[GX_DEVICE_WIIMOTE_ID_LSTICK_DOWN_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].joykey  = platform_keys[GX_DEVICE_WIIMOTE_ID_LSTICK_LEFT_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].joykey = platform_keys[GX_DEVICE_WIIMOTE_ID_LSTICK_RIGHT_DPAD].joykey;
            break;
         case DEVICE_CLASSIC:
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].joykey    = platform_keys[GX_DEVICE_CLASSIC_ID_RSTICK_UP_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].joykey  = platform_keys[GX_DEVICE_CLASSIC_ID_RSTICK_DOWN_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].joykey  = platform_keys[GX_DEVICE_CLASSIC_ID_RSTICK_LEFT_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].joykey = platform_keys[GX_DEVICE_CLASSIC_ID_RSTICK_RIGHT_DPAD].joykey;
            break;
#endif
         case DEVICE_GAMECUBE:
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_UP].joykey    = platform_keys[GX_DEVICE_GC_ID_RSTICK_UP_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_DOWN].joykey  = platform_keys[GX_DEVICE_GC_ID_RSTICK_DOWN_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_LEFT].joykey  = platform_keys[GX_DEVICE_GC_ID_RSTICK_LEFT_DPAD].joykey;
            g_settings.input.binds[port][RETRO_DEVICE_ID_JOYPAD_RIGHT].joykey = platform_keys[GX_DEVICE_GC_ID_RSTICK_RIGHT_DPAD].joykey;
            break;
         default:
            break;
      }
