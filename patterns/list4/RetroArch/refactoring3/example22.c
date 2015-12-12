switch (switchvalue)
   {
#ifdef __CELLOS_LV2__
      case SETTING_CHANGE_RESOLUTION:
         if (input & (1ULL << DEVICE_NAV_RIGHT))
            settings_set(1ULL << S_RESOLUTION_NEXT);
         if (input & (1ULL << DEVICE_NAV_LEFT))
            settings_set(1ULL << S_RESOLUTION_PREVIOUS);
         if (input & (1ULL << DEVICE_NAV_B))
         {
            if (g_extern.console.screen.resolutions.list[g_extern.console.screen.resolutions.current.idx] == CELL_VIDEO_OUT_RESOLUTION_576)
            {
               if (g_extern.console.screen.pal_enable)
                  g_extern.lifecycle_mode_state |= (1ULL<< MODE_VIDEO_PAL_ENABLE);
            }
            else
            {
               g_extern.lifecycle_mode_state &= ~(1ULL << MODE_VIDEO_PAL_ENABLE);
               g_extern.lifecycle_mode_state &= ~(1ULL << MODE_VIDEO_PAL_TEMPORAL_ENABLE);
            }


            driver.video->restart();
            rgui_init_textures();
         }
         break;
      case SETTING_PAL60_MODE:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            if (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_PAL_ENABLE))
            {
               if (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_PAL_TEMPORAL_ENABLE))
               {
                  g_extern.lifecycle_mode_state &= ~(1ULL << MODE_VIDEO_PAL_TEMPORAL_ENABLE);
               }
               else
               {
                  g_extern.lifecycle_mode_state |= (1ULL << MODE_VIDEO_PAL_TEMPORAL_ENABLE);
               }

               driver.video->restart();
               rgui_init_textures();
            }
         }

         if (input & (1ULL << DEVICE_NAV_START))
         {
            if (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_PAL_ENABLE))
            {
               g_extern.lifecycle_mode_state &= ~(1ULL << MODE_VIDEO_PAL_TEMPORAL_ENABLE);

               driver.video->restart();
               rgui_init_textures();
            }
         }
         break;
#endif
      case SETTING_EMU_SKIN:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            menu_stack_push(BORDER_CHOICE, true);
            filebrowser_set_root_and_ext(rgui->browser, EXT_IMAGES, default_paths.border_dir);
         }
         if (input & (1ULL << DEVICE_NAV_START))
         {
            if (!texture_image_load(default_paths.menu_border_file, menu_texture))
            {
               RARCH_ERR("Failed to load texture image for menu.\n");
               return false;
            }
         }
         break;
      case SETTING_FONT_SIZE:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            if (g_settings.video.font_size > 0) 
               g_settings.video.font_size -= 0.01f;
         }
         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            if ((g_settings.video.font_size < 2.0f))
               g_settings.video.font_size += 0.01f;
         }
         if (input & (1ULL << DEVICE_NAV_START))
            g_settings.video.font_size = 1.0f;
         break;
      case SETTING_ASPECT_RATIO:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            settings_set(1ULL << S_ASPECT_RATIO_DECREMENT);

            if (driver.video_poke->set_aspect_ratio)
               driver.video_poke->set_aspect_ratio(driver.video_data, g_settings.video.aspect_ratio_idx);
         }
         if (input & (1ULL << DEVICE_NAV_RIGHT))
         {
            settings_set(1ULL << S_ASPECT_RATIO_INCREMENT);

            if (driver.video_poke->set_aspect_ratio)
               driver.video_poke->set_aspect_ratio(driver.video_data, g_settings.video.aspect_ratio_idx);
         }
         if (input & (1ULL << DEVICE_NAV_START))
         {
            settings_set(1ULL << S_DEF_ASPECT_RATIO);

            if (driver.video_poke->set_aspect_ratio)
               driver.video_poke->set_aspect_ratio(driver.video_data, g_settings.video.aspect_ratio_idx);
         }
         break;
      case SETTING_HW_TEXTURE_FILTER:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            settings_set(1ULL << S_HW_TEXTURE_FILTER);

            if (driver.video_poke->set_filtering)
               driver.video_poke->set_filtering(driver.video_data, 1, g_settings.video.smooth);
         }
         if (input & (1ULL << DEVICE_NAV_START))
         {
            settings_set(1ULL << S_DEF_HW_TEXTURE_FILTER);

            if (driver.video_poke->set_filtering)
               driver.video_poke->set_filtering(driver.video_data, 1, g_settings.video.smooth);
         }
         break;
#ifdef _XBOX1
      case SETTING_FLICKER_FILTER:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            if (g_extern.console.screen.flicker_filter_index > 0)
               g_extern.console.screen.flicker_filter_index--;
         }
         if (input & (1ULL << DEVICE_NAV_RIGHT))
         {
            if (g_extern.console.screen.flicker_filter_index < 5)
               g_extern.console.screen.flicker_filter_index++;
         }
         if (input & (1ULL << DEVICE_NAV_START))
            g_extern.console.screen.flicker_filter_index = 0;
         break;
      case SETTING_SOFT_DISPLAY_FILTER:
         if (input & (1ULL << DEVICE_NAV_LEFT) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            if (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_SOFT_FILTER_ENABLE))
               g_extern.lifecycle_mode_state &= ~(1ULL << MODE_VIDEO_SOFT_FILTER_ENABLE);
            else
               g_extern.lifecycle_mode_state |= (1ULL << MODE_VIDEO_SOFT_FILTER_ENABLE);
         }
         if (input & (1ULL << DEVICE_NAV_START))
            g_extern.lifecycle_mode_state |= (1ULL << MODE_VIDEO_SOFT_FILTER_ENABLE);
         break;
#endif
      case SETTING_REFRESH_RATE:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            settings_set(1ULL << S_REFRESH_RATE_DECREMENT);
            driver_set_monitor_refresh_rate(g_settings.video.refresh_rate);
         }
         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            settings_set(1ULL << S_REFRESH_RATE_INCREMENT);
            driver_set_monitor_refresh_rate(g_settings.video.refresh_rate);
         }
         if (input & (1ULL << DEVICE_NAV_START))
         {
            settings_set(1ULL << S_DEF_REFRESH_RATE);
            driver_set_monitor_refresh_rate(g_settings.video.refresh_rate);
         }
         break;
      case SETTING_TRIPLE_BUFFERING:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            settings_set(1ULL << S_TRIPLE_BUFFERING);

            driver.video->restart();
            rgui_init_textures();
         }
         if (input & (1ULL << DEVICE_NAV_START))
         {
            settings_set(1ULL << S_DEF_TRIPLE_BUFFERING);

            if (!(g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_TRIPLE_BUFFERING_ENABLE)))
            {
               driver.video->restart();
               rgui_init_textures();
            }
         }
         break;
      case SETTING_SOUND_MODE:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            if (g_extern.console.sound.mode != SOUND_MODE_NORMAL)
               g_extern.console.sound.mode--;
         }
         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            if (g_extern.console.sound.mode < (SOUND_MODE_LAST-1))
               g_extern.console.sound.mode++;
         }
         if ((input & (1ULL << DEVICE_NAV_UP)) || (input & (1ULL << DEVICE_NAV_DOWN)))
         {
#ifdef HAVE_RSOUND
            if (g_extern.console.sound.mode != SOUND_MODE_RSOUND)
               rarch_rsound_stop();
            else
               rarch_rsound_start(g_settings.audio.device);
#endif
         }
         if (input & (1ULL << DEVICE_NAV_START))
         {
            g_extern.console.sound.mode = SOUND_MODE_NORMAL;
#ifdef HAVE_RSOUND
            rarch_rsound_stop();
#endif
         }
         break;
#ifdef HAVE_RSOUND
      case SETTING_RSOUND_SERVER_IP_ADDRESS:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
#ifdef HAVE_OSKUTIL
            rgui->osk_init = osk_callback_enter_rsound_init;
            rgui->osk_callback = osk_callback_enter_rsound;
#endif
         }
         if (input & (1ULL << DEVICE_NAV_START))
            strlcpy(g_settings.audio.device, "0.0.0.0", sizeof(g_settings.audio.device));
         break;
#endif
      case SETTING_EMU_SHOW_DEBUG_INFO_MSG:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
            settings_set(1ULL << S_INFO_DEBUG_MSG_TOGGLE);
         if (input & (1ULL << DEVICE_NAV_START))
            settings_set(1ULL << S_DEF_INFO_DEBUG_MSG);
         break;
      case SETTING_EMU_SHOW_INFO_MSG:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
            settings_set(1ULL << S_INFO_MSG_TOGGLE);
         if (input & (1ULL << DEVICE_NAV_START))
            settings_set(1ULL << S_DEF_INFO_MSG);
         break;
      case SETTING_REWIND_ENABLED:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            settings_set(1ULL << S_REWIND);

            if (g_settings.rewind_enable)
               rarch_init_rewind();
            else
               rarch_deinit_rewind();
         }

         if (input & (1ULL << DEVICE_NAV_START))
         {
            if (g_settings.rewind_enable)
            {
               g_settings.rewind_enable = false;
               rarch_deinit_rewind();
            }
         }
         break;
      case SETTING_REWIND_GRANULARITY:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            if (g_settings.rewind_granularity > 1)
               g_settings.rewind_granularity--;
         }
         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
            g_settings.rewind_granularity++;
         if (input & (1ULL << DEVICE_NAV_START))
            g_settings.rewind_granularity = 1;
         break;
      case SETTING_EMU_AUDIO_MUTE:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
            settings_set(1ULL << S_AUDIO_MUTE);

         if (input & (1ULL << DEVICE_NAV_START))
            settings_set(1ULL << S_DEF_AUDIO_MUTE);
         break;
#ifdef _XBOX1
      case SETTING_EMU_AUDIO_SOUND_VOLUME_LEVEL:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            g_extern.console.sound.volume_level = !g_extern.console.sound.volume_level;
            if (g_extern.lifecycle_mode_state & (1ULL << MODE_INFO_DRAW))
               msg_queue_push(g_extern.msg_queue, "INFO - You need to restart RetroArch.", 1, 180);
         }

         if (input & (1ULL << DEVICE_NAV_START))
         {
            g_extern.console.sound.volume_level = 0;
            if (g_extern.lifecycle_mode_state & (1ULL << MODE_INFO_DRAW))
               msg_queue_push(g_extern.msg_queue, "INFO - You need to restart RetroArch.", 1, 180);
         }
         break;
#endif
      case SETTING_ENABLE_CUSTOM_BGM:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
#if (CELL_SDK_VERSION > 0x340000)
            if (g_extern.lifecycle_mode_state & (1ULL << MODE_AUDIO_CUSTOM_BGM_ENABLE))
               g_extern.lifecycle_mode_state &= ~(1ULL << MODE_AUDIO_CUSTOM_BGM_ENABLE);
            else
               g_extern.lifecycle_mode_state |= (1ULL << MODE_AUDIO_CUSTOM_BGM_ENABLE);
            if (g_extern.lifecycle_mode_state & (1ULL << MODE_AUDIO_CUSTOM_BGM_ENABLE))
               cellSysutilEnableBgmPlayback();
            else
               cellSysutilDisableBgmPlayback();

#endif
         }
         if (input & (1ULL << DEVICE_NAV_START))
         {
#if (CELL_SDK_VERSION > 0x340000)
            g_extern.lifecycle_mode_state |= (1ULL << MODE_AUDIO_CUSTOM_BGM_ENABLE);
#endif
         }
         break;
      case SETTING_PATH_DEFAULT_ROM_DIRECTORY:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            menu_stack_push(PATH_DEFAULT_ROM_DIR_CHOICE, true);
            filebrowser_set_root_and_ext(rgui->browser, "empty", default_paths.filesystem_root_dir);
         }

         if (input & (1ULL << DEVICE_NAV_START))
            strlcpy(g_settings.rgui_browser_directory,
                  default_paths.filesystem_root_dir, sizeof(g_settings.rgui_browser_directory));
         break;
      case SETTING_PATH_SAVESTATES_DIRECTORY:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            menu_stack_push(PATH_SAVESTATES_DIR_CHOICE, true);
            filebrowser_set_root_and_ext(rgui->browser, "empty", default_paths.filesystem_root_dir);
         }

         if (input & (1ULL << DEVICE_NAV_START))
            strlcpy(g_extern.savestate_dir, default_paths.savestate_dir, sizeof(g_extern.savestate_dir));

         break;
      case SETTING_PATH_SRAM_DIRECTORY:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            menu_stack_push(PATH_SRAM_DIR_CHOICE, true);
            filebrowser_set_root_and_ext(rgui->browser, "empty", default_paths.filesystem_root_dir);
         }

         if (input & (1ULL << DEVICE_NAV_START))
            strlcpy(g_extern.savefile_dir, default_paths.sram_dir, sizeof(g_extern.savefile_dir));
         break;
#ifdef HAVE_XML
      case SETTING_PATH_CHEATS:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            menu_stack_push(PATH_CHEATS_DIR_CHOICE, true);
            filebrowser_set_root_and_ext(rmenu->browser, "empty", default_paths.filesystem_root_dir);
         }

         if (input & (1ULL << DEVICE_NAV_START))
            strlcpy(g_settings.cheat_database, default_paths.port_dir, sizeof(g_settings.cheat_database));
         break;
#endif
      case SETTING_PATH_SYSTEM:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            menu_stack_push(PATH_SYSTEM_DIR_CHOICE, true);
            filebrowser_set_root_and_ext(rgui->browser, "empty", default_paths.system_dir);
         }

         if (input & (1ULL << DEVICE_NAV_START))
            strlcpy(g_settings.system_directory, default_paths.system_dir, sizeof(g_settings.system_directory));
         break;
      case SETTING_CONTROLS_SCHEME:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)) || (input & (1ULL << DEVICE_NAV_START)))
         {
            menu_stack_push(INPUT_PRESET_CHOICE, true);
            filebrowser_set_root_and_ext(rgui->browser, EXT_INPUT_PRESETS, default_paths.input_presets_dir);
         }
         break;
      case SETTING_CONTROLS_NUMBER:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            if (rgui->current_pad != 0)
               rgui->current_pad--;
         }

         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            if (rgui->current_pad < 6)
               rgui->current_pad++;
         }

         if (input & (1ULL << DEVICE_NAV_START))
            rgui->current_pad = 0;
         break; 
      case SETTING_DPAD_EMULATION:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            if (driver.input->set_keybinds)
            {
               unsigned keybind_action = 0;

               switch(g_settings.input.dpad_emulation[rgui->current_pad])
               {
                  case ANALOG_DPAD_NONE:
                     break;
                  case ANALOG_DPAD_LSTICK:
                     keybind_action = (1ULL << KEYBINDS_ACTION_SET_ANALOG_DPAD_NONE);
                     break;
                  case ANALOG_DPAD_RSTICK:
                     keybind_action = (1ULL << KEYBINDS_ACTION_SET_ANALOG_DPAD_LSTICK);
                     break;
                  default:
                     break;
               }

               if (keybind_action)
                  driver.input->set_keybinds(driver.input_data, g_settings.input.device[rgui->current_pad], rgui->current_pad, 0, keybind_action);
            }
         }

         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            if (driver.input->set_keybinds)
            {
               unsigned keybind_action = 0;

               switch(g_settings.input.dpad_emulation[rgui->current_pad])
               {
                  case ANALOG_DPAD_NONE:
                     keybind_action = (1ULL << KEYBINDS_ACTION_SET_ANALOG_DPAD_LSTICK);
                     break;
                  case ANALOG_DPAD_LSTICK:
                     keybind_action = (1ULL << KEYBINDS_ACTION_SET_ANALOG_DPAD_RSTICK);
                     break;
                  case ANALOG_DPAD_RSTICK:
                     break;
               }

               if (keybind_action)
                  driver.input->set_keybinds(driver.input_data, g_settings.input.device[rgui->current_pad], rgui->current_pad, 0, keybind_action);
            }
         }

         if (input & (1ULL << DEVICE_NAV_START))
            if (driver.input->set_keybinds)
                  driver.input->set_keybinds(driver.input_data, g_settings.input.device[rgui->current_pad], rgui->current_pad, 0, (1ULL << KEYBINDS_ACTION_SET_ANALOG_DPAD_LSTICK));
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_UP:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_UP, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_DOWN:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_DOWN, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_LEFT:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_LEFT, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_RIGHT:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_RIGHT, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_A:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_A, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_B:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_B, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_X:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_X, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_Y:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_Y, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_SELECT:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_SELECT, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_START:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_START, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_L:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_L, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_R:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_R, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_L2:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_L2, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_R2:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_R2, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_L3:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_L3, input);
         break;
      case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_R3:
         set_keybind_digital(RETRO_DEVICE_ID_JOYPAD_R3, input);
         break;
#ifdef HAVE_OSKUTIL
      case SETTING_CONTROLS_SAVE_CUSTOM_CONTROLS:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)) || (input & (1ULL << DEVICE_NAV_START)))
         {
            rgui->osk_param = INPUT_PRESET_FILE;
            rgui->osk_init = osk_callback_enter_filename_init;
            rgui->osk_callback = osk_callback_enter_filename;
         }
         break;
#endif
      case SETTING_CONTROLS_DEFAULT_ALL:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)) || (input & (1ULL << DEVICE_NAV_START)))
            if (driver.input->set_keybinds)
               driver.input->set_keybinds(driver.input_data, g_settings.input.device[rgui->current_pad], rgui->current_pad, 0,
                     (1ULL << KEYBINDS_ACTION_SET_DEFAULT_BINDS));
         break;
      case INGAME_MENU_LOAD_STATE:
         if (input & (1ULL << DEVICE_NAV_B))
         {
            rarch_load_state();
            g_extern.lifecycle_mode_state |= (1ULL << MODE_GAME);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_MENU_INGAME_EXIT);
            return -1;
         }
         if (input & (1ULL << DEVICE_NAV_LEFT))
            rarch_state_slot_decrease();
         if (input & (1ULL << DEVICE_NAV_RIGHT))
            rarch_state_slot_increase();

         break;
      case INGAME_MENU_SAVE_STATE:
         if (input & (1ULL << DEVICE_NAV_B))
         {
            rarch_save_state();
            g_extern.lifecycle_mode_state |= (1ULL << MODE_GAME);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_MENU_INGAME_EXIT);
            return -1;
         }

         if (input & (1ULL << DEVICE_NAV_LEFT))
            rarch_state_slot_decrease();
         if (input & (1ULL << DEVICE_NAV_RIGHT))
            rarch_state_slot_increase();

         break;
      case SETTING_ROTATION:
         if (input & (1ULL << DEVICE_NAV_LEFT))
         {
            settings_set(1ULL << S_ROTATION_DECREMENT);
            video_set_rotation_func(g_extern.console.screen.orientation);
         }

         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            settings_set(1ULL << S_ROTATION_INCREMENT);
            video_set_rotation_func(g_extern.console.screen.orientation);
         }

         if (input & (1ULL << DEVICE_NAV_START))
         {
            settings_set(1ULL << S_DEF_ROTATION);
            video_set_rotation_func(g_extern.console.screen.orientation);
         }
         break;
      case INGAME_MENU_FRAME_ADVANCE:
         if ((input & (1ULL << DEVICE_NAV_B)) || (input & (1ULL << DEVICE_NAV_R2)) || (input & (1ULL << DEVICE_NAV_L2)))
         {
            g_extern.lifecycle_state |= (1ULL << RARCH_FRAMEADVANCE);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_MENU_INGAME_EXIT);
            settings_set(1ULL << S_FRAME_ADVANCE);
            return -1;
         }
         break;
      case SETTING_CUSTOM_VIEWPORT:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_CUSTOM_RATIO, false);
         break;
      case INGAME_MENU_CORE_OPTIONS_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_CORE_OPTIONS, false);
         break;
      case INGAME_MENU_LOAD_GAME_HISTORY_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_LOAD_GAME_HISTORY, false);
         break;
      case INGAME_MENU_SCREENSHOT_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_SCREENSHOT, false);
         break;
      case INGAME_MENU_RETURN_TO_GAME:
         if (input & (1ULL << DEVICE_NAV_B))
         {
            g_extern.lifecycle_mode_state |= (1ULL << MODE_GAME);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_MENU_INGAME_EXIT);
            return -1;
         }
         break;
      case INGAME_MENU_CHANGE_GAME:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(FILE_BROWSER_MENU, false);
         break;
      case INGAME_MENU_SETTINGS_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_SETTINGS, false);
         break;
      case INGAME_MENU_RESET:
         if (input & (1ULL << DEVICE_NAV_B))
         {
            rarch_game_reset();
            g_extern.lifecycle_mode_state |= (1ULL << MODE_GAME);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_MENU_INGAME_EXIT);
            return -1;
         }
         break;
      case INGAME_MENU_CHANGE_LIBRETRO_CORE:
         if (input & (1ULL << DEVICE_NAV_B))
         {
            menu_stack_push(LIBRETRO_CHOICE, true);
            filebrowser_set_root_and_ext(rgui->browser, EXT_EXECUTABLES, default_paths.core_dir);
         }
         break;
#ifdef HAVE_MULTIMAN
      case INGAME_MENU_RETURN_TO_MULTIMAN:
         if (input & (1ULL << DEVICE_NAV_B))
         {
            g_extern.lifecycle_mode_state &= ~(1ULL << MODE_GAME);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_MENU_INGAME_EXIT);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_EXITSPAWN);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_EXITSPAWN_MULTIMAN);
            return -1;
         }
         break;
#endif
      case INGAME_MENU_QUIT_RETROARCH:
         if (input & (1ULL << DEVICE_NAV_B))
         {
            g_extern.lifecycle_mode_state &= ~(1ULL << MODE_GAME);
            g_extern.lifecycle_mode_state |= (1ULL << MODE_MENU_INGAME_EXIT);
            return -1;
         }
         break;
      case INGAME_MENU_VIDEO_OPTIONS_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_VIDEO_OPTIONS, false);
         break;
#ifdef HAVE_SHADER_MANAGER
      case INGAME_MENU_SHADER_OPTIONS_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_SHADER_OPTIONS, false);
         break;
#endif
      case INGAME_MENU_AUDIO_OPTIONS_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_AUDIO_OPTIONS, false);
         break;
      case INGAME_MENU_INPUT_OPTIONS_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_INPUT_OPTIONS, false);
         break;
      case INGAME_MENU_PATH_OPTIONS_MODE:
         if (input & (1ULL << DEVICE_NAV_B))
            menu_stack_push(INGAME_MENU_PATH_OPTIONS, false);
         break;
#ifdef HAVE_SHADER_MANAGER
      case SHADERMAN_LOAD_CGP:
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            menu_stack_push(CGP_CHOICE, true);
            filebrowser_set_root_and_ext(rgui->browser, EXT_CGP_PRESETS, g_settings.video.shader_dir);
         }
         if (input & (1ULL << DEVICE_NAV_START))
         {
            g_settings.video.shader_path[0] = '\0';
            video_set_shader_func(RARCH_SHADER_CG, NULL);
            g_settings.video.shader_enable = false;
         }
         break;
      case SHADERMAN_SAVE_CGP:
#ifdef HAVE_OSKUTIL
         if ((input & (1ULL << DEVICE_NAV_LEFT)) || (input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
         {
            rgui->osk_param = SHADER_PRESET_FILE;
            rgui->osk_init = osk_callback_enter_filename_init;
            rgui->osk_callback = osk_callback_enter_filename;
         }
#endif
         break;
      case SHADERMAN_SHADER_PASSES:
         if (input & (1ULL << DEVICE_NAV_LEFT))
            if (rgui->shader.passes)
               rgui->shader.passes--;
         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
            if (rgui->shader.passes < RGUI_MAX_SHADERS)
               rgui->shader.passes++;
         if (input & (1ULL << DEVICE_NAV_START))
            rgui->shader.passes= 0;
         break;
      case SHADERMAN_AUTOSTART_CGP_ON_STARTUP:
         break;
      case SHADERMAN_SHADER_0:
      case SHADERMAN_SHADER_1:
      case SHADERMAN_SHADER_2:
      case SHADERMAN_SHADER_3:
      case SHADERMAN_SHADER_4:
      case SHADERMAN_SHADER_5:
      case SHADERMAN_SHADER_6:
      case SHADERMAN_SHADER_7:
         {
            uint8_t index = (switchvalue - SHADERMAN_SHADER_0) / 3;
            struct gfx_shader_pass *pass = &rgui->shader.pass[index];

            if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)) ||
                  (input & (1ULL << DEVICE_NAV_LEFT)))
            {
               shader_choice_set_shader_slot = index;
               menu_stack_push(SHADER_CHOICE, true);
               filebrowser_set_root_and_ext(rgui->browser, EXT_SHADERS, g_settings.video.shader_dir);
            }

            if (input & (1ULL << DEVICE_NAV_START))
               *pass->source.cg = '\0';
         }
         break;
      case SHADERMAN_SHADER_0_FILTER:
      case SHADERMAN_SHADER_1_FILTER:
      case SHADERMAN_SHADER_2_FILTER:
      case SHADERMAN_SHADER_3_FILTER:
      case SHADERMAN_SHADER_4_FILTER:
      case SHADERMAN_SHADER_5_FILTER:
      case SHADERMAN_SHADER_6_FILTER:
      case SHADERMAN_SHADER_7_FILTER:
         {
            uint8_t index = (switchvalue - SHADERMAN_SHADER_0) / 3;

            if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)) ||
                  (input & (1ULL << DEVICE_NAV_LEFT)))
            {
               unsigned delta = (input & (1ULL << DEVICE_NAV_LEFT)) ? 2 : 1;
               rgui->shader.pass[index].filter = (enum gfx_filter_type)((rgui->shader.pass[index].filter + delta) % 3);
            }

            if (input & (1ULL << DEVICE_NAV_START))
               rgui->shader.pass[index].filter = RARCH_FILTER_UNSPEC;
         }
         break;
      case SHADERMAN_SHADER_0_SCALE:
      case SHADERMAN_SHADER_1_SCALE:
      case SHADERMAN_SHADER_2_SCALE:
      case SHADERMAN_SHADER_3_SCALE:
      case SHADERMAN_SHADER_4_SCALE:
      case SHADERMAN_SHADER_5_SCALE:
      case SHADERMAN_SHADER_6_SCALE:
      case SHADERMAN_SHADER_7_SCALE:
         {
            uint8_t index = (switchvalue - SHADERMAN_SHADER_0) / 3;
            unsigned scale = rgui->shader.pass[index].fbo.scale_x;

            if (input & (1ULL << DEVICE_NAV_LEFT))
            {
               if (scale)
               {
                  rgui->shader.pass[index].fbo.scale_x = rgui->shader.pass[index].fbo.scale_y = scale - 1;
                  rgui->shader.pass[index].fbo.valid = scale - 1;
               }
            }

            if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)))
            {
               if (scale < 5)
               {
                  rgui->shader.pass[index].fbo.scale_x = rgui->shader.pass[index].fbo.scale_y = scale + 1;
                  rgui->shader.pass[index].fbo.valid = scale + 1;
               }
            }

            if (input & (1ULL << DEVICE_NAV_START))
            {
               rgui->shader.pass[index].fbo.scale_x = rgui->shader.pass[index].fbo.scale_y = 0;
               rgui->shader.pass[index].fbo.valid = false;
            }
         }
         break;
      case SHADERMAN_APPLY_CHANGES:
         if ((input & (1ULL << DEVICE_NAV_RIGHT)) || (input & (1ULL << DEVICE_NAV_B)) ||
               (input & (1ULL << DEVICE_NAV_START)) || (input & (1ULL << DEVICE_NAV_LEFT)))
         {
            bool ret = false;
            char cgp_path[PATH_MAX];

            if (rgui->shader.passes)
            {
               const char *shader_dir = *g_settings.video.shader_dir ?
                  g_settings.video.shader_dir : g_settings.system_directory;
               fill_pathname_join(cgp_path, shader_dir, "rgui.cgp", sizeof(cgp_path));
               config_file_t *conf = config_file_new(NULL);
               if (!conf)
                  return 0;
               gfx_shader_write_conf_cgp(conf, &rgui->shader);
               config_file_write(conf, cgp_path);
               config_file_free(conf);
            }
            else
               cgp_path[0] = '\0';

            ret = video_set_shader_func(RARCH_SHADER_CG, (cgp_path[0] != '\0') ? cgp_path : NULL); 

            if (ret)
               g_settings.video.shader_enable = true;
            else
            {
               RARCH_ERR("Setting RGUI CGP failed.\n");
               g_settings.video.shader_enable = false;
            }
         }
         break;
#endif
   }
