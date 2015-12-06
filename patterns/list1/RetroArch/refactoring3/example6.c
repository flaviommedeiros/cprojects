switch (mode)
   {
      case ID_M_LOAD_CORE:
      case ID_M_LOAD_CONTENT:
         {
            char win32_file[PATH_MAX_LENGTH] = {0};
            const char *extensions  = NULL;
            const char *title       = NULL;
            const char *initial_dir = NULL;

            switch (mode)
            {
               case ID_M_LOAD_CORE:
                  extensions  = "All Files\0*.*\0 Libretro core(.dll)\0*.dll\0";
#ifdef HAVE_MENU
                  title       = menu_hash_to_str(MENU_LABEL_VALUE_CORE_LIST);
#else
                  title       = "Load Core";
#endif
                  initial_dir = settings->libretro_directory;
                  cmd         = EVENT_CMD_LOAD_CORE;
                  break;
               case ID_M_LOAD_CONTENT:
                  extensions  = "All Files\0*.*\0\0";
#ifdef HAVE_MENU
                  title       = menu_hash_to_str(MENU_LABEL_VALUE_LOAD_CONTENT_LIST);
#else
                  title       = "Load Content";
#endif
                  initial_dir = settings->menu_content_directory;
                  cmd         = EVENT_CMD_LOAD_CONTENT;
                  break;
            }

            if (win32_browser(owner, win32_file, extensions, title, initial_dir))
            {
               switch (mode)
               {
                  case ID_M_LOAD_CORE:
                     rarch_main_ctl(RARCH_MAIN_CTL_SET_LIBRETRO_PATH, win32_file);
                     break;
                  case ID_M_LOAD_CONTENT:
                     rarch_main_ctl(RARCH_MAIN_CTL_SET_CONTENT_PATH, win32_file);
                     do_wm_close = true;
                     break;
               }
            }
         }
         break;
      case ID_M_RESET:
         cmd = EVENT_CMD_RESET;
         break;
      case ID_M_MUTE_TOGGLE:
         cmd = EVENT_CMD_AUDIO_MUTE_TOGGLE;
         break;
      case ID_M_MENU_TOGGLE:
         cmd = EVENT_CMD_MENU_TOGGLE;
         break;
      case ID_M_PAUSE_TOGGLE:
         cmd = EVENT_CMD_PAUSE_TOGGLE;
         break;
      case ID_M_LOAD_STATE:
         cmd = EVENT_CMD_LOAD_STATE;
         break;
      case ID_M_SAVE_STATE:
         cmd = EVENT_CMD_SAVE_STATE;
         break;
      case ID_M_DISK_CYCLE:
         cmd = EVENT_CMD_DISK_EJECT_TOGGLE;
         break;
      case ID_M_DISK_NEXT:
         cmd = EVENT_CMD_DISK_NEXT;
         break;
      case ID_M_DISK_PREV:
         cmd = EVENT_CMD_DISK_PREV;
         break;
      case ID_M_FULL_SCREEN:
         cmd = EVENT_CMD_FULLSCREEN_TOGGLE;
         break;
#ifndef _XBOX
      case ID_M_SHADER_PARAMETERS:
         shader_dlg_show(owner);
         break;
#endif
      case ID_M_MOUSE_GRAB:
         cmd = EVENT_CMD_GRAB_MOUSE_TOGGLE;
         break;
      case ID_M_TAKE_SCREENSHOT:
         cmd = EVENT_CMD_TAKE_SCREENSHOT;
         break;
      case ID_M_QUIT:
         do_wm_close = true;
         break;
      default:
         if (mode >= ID_M_WINDOW_SCALE_1X && mode <= ID_M_WINDOW_SCALE_10X)
         {
            unsigned idx = (mode - (ID_M_WINDOW_SCALE_1X-1));
            rarch_main_ctl(RARCH_MAIN_CTL_SET_WINDOWED_SCALE, &idx);
            cmd = EVENT_CMD_RESIZE_WINDOWED_SCALE;
         }
         else if (mode == ID_M_STATE_INDEX_AUTO)
         {
            signed idx = -1;
            settings->state_slot = idx;
         }
         else if (mode >= (ID_M_STATE_INDEX_AUTO+1) && mode <= (ID_M_STATE_INDEX_AUTO+10))
         {
            signed idx = (mode - (ID_M_STATE_INDEX_AUTO+1));
            settings->state_slot = idx;
         }
         break;
   }
