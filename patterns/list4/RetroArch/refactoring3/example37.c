switch (i)
      {
#ifdef __CELLOS_LV2__
         case SETTING_CHANGE_RESOLUTION:
            {
               unsigned width = gfx_ctx_get_resolution_width(g_extern.console.screen.resolutions.list[g_extern.console.screen.resolutions.current.idx]);
               unsigned height = gfx_ctx_get_resolution_height(g_extern.console.screen.resolutions.list[g_extern.console.screen.resolutions.current.idx]);
               strlcpy(text, "Resolution", sizeof(text));
               strlcpy(comment, "INFO - Change the display resolution.", sizeof(comment));
               snprintf(setting_text, sizeof(setting_text), "%dx%d", width, height);
            }
            break;
         case SETTING_PAL60_MODE:
            strlcpy(text, "PAL60 Mode", sizeof(text));
            if (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_PAL_TEMPORAL_ENABLE))
            {
               strlcpy(setting_text, "ON", sizeof(setting_text));
               strlcpy(comment, "INFO - [PAL60 Mode is set to 'ON'.\nconverts frames from 60Hz to 50Hz.", sizeof(comment));
            }
            else
            {
               strlcpy(setting_text, "OFF", sizeof(setting_text));
               strlcpy(comment, "INFO - [PAL60 Mode is set to 'OFF'.\nframes are not converted.", sizeof(comment));
            }
            break;
#endif
         case SETTING_EMU_SKIN:
            fill_pathname_base(fname, g_extern.menu_texture_path, sizeof(fname));
            strlcpy(text, "Menu Skin", sizeof(text));
            strlcpy(setting_text, fname, sizeof(setting_text));
            strlcpy(comment, "INFO - Select a skin for the menu.", sizeof(comment));
            break;
         case SETTING_FONT_SIZE:
            strlcpy(text, "Font Size", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), "%f", g_settings.video.font_size);
            strlcpy(comment, "INFO - Increase or decrease the [Font Size].", sizeof(comment));
            break;
         case SETTING_HW_TEXTURE_FILTER:
            strlcpy(text, "Default Filter", sizeof(text));
            if (g_settings.video.smooth)
            {
               strlcpy(setting_text, "Linear", sizeof(setting_text));
               strlcpy(comment, "INFO - Default Filter is set to Linear.",
                     sizeof(comment));
            }
            else
            {
               strlcpy(setting_text, "Nearest", sizeof(setting_text));
               strlcpy(comment, "INFO - Default Filter is set to Nearest.",
                     sizeof(comment));
            }
            break;
#ifdef _XBOX1
         case SETTING_FLICKER_FILTER:
            strlcpy(text, "Flicker Filter", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), "%d", g_extern.console.screen.flicker_filter_index);
            strlcpy(comment, "INFO - Toggle the [Flicker Filter].", sizeof(comment));
            break;
         case SETTING_SOFT_DISPLAY_FILTER:
            strlcpy(text, "Soft Display Filter", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_SOFT_FILTER_ENABLE)) ? "ON" : "OFF");
            strlcpy(comment, "INFO - Toggle the [Soft Display Filter].", sizeof(comment));
            break;
#endif
         case SETTING_REFRESH_RATE:
            strlcpy(text, "Refresh rate", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), "%fHz", g_settings.video.refresh_rate);
            strlcpy(comment, "INFO - Adjust or decrease [Refresh Rate].", sizeof(comment));
            break;
         case SETTING_TRIPLE_BUFFERING:
            strlcpy(text, "Triple Buffering", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_TRIPLE_BUFFERING_ENABLE)) ? "ON" : "OFF");
            snprintf(comment, sizeof(comment), (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_TRIPLE_BUFFERING_ENABLE)) ? "INFO - [Triple Buffering] is set to 'ON'." : "INFO - [Triple Buffering] is set to 'OFF'.");
            break;
         case SETTING_SOUND_MODE:
            strlcpy(text, "Sound Output", sizeof(text));
            switch(g_extern.console.sound.mode)
            {
               case SOUND_MODE_NORMAL:
                  strlcpy(comment, "INFO - [Sound Output] is set to 'Normal'.", sizeof(comment));
                  strlcpy(setting_text, "Normal", sizeof(setting_text));
                  break;
#ifdef HAVE_RSOUND
               case SOUND_MODE_RSOUND:
                  strlcpy(comment, "INFO - [Sound Output] is set to 'RSound'.", sizeof(comment));
                  strlcpy(setting_text, "RSound", sizeof(setting_text));
                  break;
#endif
#ifdef HAVE_HEADSET
               case SOUND_MODE_HEADSET:
                  strlcpy(comment, "INFO - [Sound Output] is set to USB/Bluetooth Headset.", sizeof(comment));
                  strlcpy(setting_text, "USB/Bluetooth Headset", sizeof(setting_text));
                  break;
#endif
               default:
                  break;
            }
            break;
#ifdef HAVE_RSOUND
         case SETTING_RSOUND_SERVER_IP_ADDRESS:
            strlcpy(text, "RSound Server IP Address", sizeof(text));
            strlcpy(setting_text, g_settings.audio.device, sizeof(setting_text));
            strlcpy(comment, "INFO - Enter the IP Address of the [RSound Audio Server]. IP address\nmust be an IPv4 32-bits address, eg: '192.168.1.7'.", sizeof(comment));
            break;
#endif
         case SETTING_EMU_SHOW_DEBUG_INFO_MSG:
            strlcpy(text, "Debug Info Messages", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), (g_extern.lifecycle_mode_state & (1ULL << MODE_FPS_DRAW)) ? "ON" : "OFF");
            strlcpy(comment, "INFO - Show onscreen debug messages.", sizeof(comment));
            break;
         case SETTING_EMU_SHOW_INFO_MSG:
            strlcpy(text, "Info Messages", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), (g_extern.lifecycle_mode_state & (1ULL << MODE_INFO_DRAW)) ? "ON" : "OFF");
            strlcpy(comment, "INFO - Show onscreen info messages in the menu.", sizeof(comment));
            break;
         case SETTING_REWIND_ENABLED:
            strlcpy(text, "Rewind", sizeof(text));
            if (g_settings.rewind_enable)
            {
               strlcpy(setting_text, "ON", sizeof(setting_text));
               strlcpy(comment, "INFO - [Rewind] feature is set to 'ON'.",
                     sizeof(comment));
            }
            else
            {
               strlcpy(setting_text, "OFF", sizeof(setting_text));
               strlcpy(comment, "INFO - [Rewind] feature is set to 'OFF'.",
                     sizeof(comment));
            }
            break;
         case SETTING_REWIND_GRANULARITY:
            strlcpy(text, "Rewind Granularity", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), "%d", g_settings.rewind_granularity);
            strlcpy(comment, "INFO - Set the amount of frames to 'rewind'.", sizeof(comment));
            break;
         case SETTING_EMU_AUDIO_MUTE:
            strlcpy(text, "Mute Audio", sizeof(text));
            if (g_extern.audio_data.mute)
            {
               strlcpy(comment, "INFO - the game audio will be muted.", sizeof(comment));
               strlcpy(setting_text, "ON", sizeof(setting_text));
            }
            else
            {
               strlcpy(comment, "INFO - game audio will be on.", sizeof(comment));
               strlcpy(setting_text, "OFF", sizeof(setting_text));
            }
            break;
#ifdef _XBOX1
         case SETTING_EMU_AUDIO_SOUND_VOLUME_LEVEL:
            strlcpy(text, "Volume Level", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), g_extern.console.sound.volume_level ? "Loud" : "Normal");
            if (g_extern.audio_data.mute)
               strlcpy(comment, "INFO - Volume level is set to Loud.", sizeof(comment));
            else
               strlcpy(comment, "INFO - Volume level is set to Normal.", sizeof(comment));
            break;
#endif
         case SETTING_ENABLE_CUSTOM_BGM:
            strlcpy(text, "Custom BGM Option", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), (g_extern.lifecycle_mode_state & (1ULL << MODE_AUDIO_CUSTOM_BGM_ENABLE)) ? "ON" : "OFF");
            snprintf(comment, sizeof(comment), "INFO - [Custom BGM] is set to '%s'.", (g_extern.lifecycle_mode_state & (1ULL << MODE_AUDIO_CUSTOM_BGM_ENABLE)) ? "ON" : "OFF");
            break;
         case SETTING_PATH_DEFAULT_ROM_DIRECTORY:
            strlcpy(text, "Browser Directory", sizeof(text));
            strlcpy(setting_text, g_settings.rgui_browser_directory, sizeof(setting_text));
            strlcpy(comment, "INFO - Set the default startup browser directory path.", sizeof(comment));
            break;
         case SETTING_PATH_SAVESTATES_DIRECTORY:
            strlcpy(text, "Savestate Directory", sizeof(text));
            strlcpy(setting_text, g_extern.savestate_dir, sizeof(setting_text));
            strlcpy(comment, "INFO - Directory where savestates will be saved to.", sizeof(comment));
            break;
         case SETTING_PATH_SRAM_DIRECTORY:
            strlcpy(text, "Savefile Directory", sizeof(text));
            strlcpy(setting_text, g_extern.savefile_dir, sizeof(setting_text));
            strlcpy(comment, "INFO - Set the default SaveRAM directory path.", sizeof(comment));
            break;
#ifdef HAVE_XML
         case SETTING_PATH_CHEATS:
            strlcpy(text, "Cheatfile Directory", sizeof(text));
            strlcpy(setting_text, g_settings.cheat_database, sizeof(setting_text));
            strlcpy(comment, "INFO - Set the default Cheatfile directory path.", sizeof(comment));
            break;
#endif
         case SETTING_PATH_SYSTEM:
            strlcpy(text, "System Directory", sizeof(text));
            strlcpy(setting_text, g_settings.system_directory, sizeof(setting_text));
            strlcpy(comment, "INFO - Set the default [System directory] path.", sizeof(comment));
            break;
         case SETTING_CONTROLS_SCHEME:
            strlcpy(text, "Load Controls Preset", sizeof(text));
            snprintf(comment, sizeof(comment), "INFO - Controls preset [%s] is selected.", g_extern.input_config_path);
            strlcpy(setting_text, g_extern.input_config_path, sizeof(setting_text));
            break;
         case SETTING_CONTROLS_NUMBER:
            strlcpy(text, "Player", sizeof(text));
            snprintf(comment, sizeof(comment), "Player %d is currently selected.", rgui->current_pad+1);
            snprintf(setting_text, sizeof(setting_text), "%d", rgui->current_pad+1);
            break;
         case SETTING_DPAD_EMULATION:
            strlcpy(text, "D-Pad Emulation", sizeof(text));
            switch(g_settings.input.dpad_emulation[rgui->current_pad])
            {
               case ANALOG_DPAD_NONE:
                  snprintf(comment, sizeof(comment), "[%s] from Controller %d is mapped to D-pad.", "None", rgui->current_pad+1);
                  strlcpy(setting_text, "None", sizeof(setting_text));
                  break;
               case ANALOG_DPAD_LSTICK:
                  snprintf(comment, sizeof(comment), "[%s] from Controller %d is mapped to D-pad.", "Left Stick", rgui->current_pad+1);
                  strlcpy(setting_text, "Left Stick", sizeof(setting_text));
                  break;
               case ANALOG_DPAD_RSTICK:
                  snprintf(comment, sizeof(comment), "[%s] from Controller %d is mapped to D-pad.", "Right Stick", rgui->current_pad+1);
                  strlcpy(setting_text, "Right Stick", sizeof(setting_text));
                  break;
            }
            break;
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_B:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_Y:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_SELECT:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_START:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_UP:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_DOWN:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_LEFT:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_RIGHT:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_A:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_X:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_L:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_R:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_L2:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_R2:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_L3:
         case SETTING_CONTROLS_RETRO_DEVICE_ID_JOYPAD_R3:
            {
               unsigned id = i - FIRST_CONTROL_BIND;
               struct platform_bind key_label;
               strlcpy(key_label.desc, "Unknown", sizeof(key_label.desc));
               key_label.joykey = g_settings.input.binds[rgui->current_pad][id].joykey;

               if (driver.input->set_keybinds)
                  driver.input->set_keybinds(&key_label, 0, 0, 0, (1ULL << KEYBINDS_ACTION_GET_BIND_LABEL));
               strlcpy(text, g_settings.input.binds[rgui->current_pad][id].desc, sizeof(text));
               snprintf(comment, sizeof(comment), "INFO - [%s] is mapped to action:\n[%s].", text, key_label.desc);
               strlcpy(setting_text, key_label.desc, sizeof(setting_text));
            }
            break;
         case SETTING_CONTROLS_SAVE_CUSTOM_CONTROLS:
            strlcpy(text, "Save Controls Preset", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "INFO - Save the [Custom Controls] settings to file.",  sizeof(comment));
            break;
         case SETTING_CONTROLS_DEFAULT_ALL:
            strlcpy(text, "DEFAULTS", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "INFO - Set all Controls settings to defaults.", sizeof(comment));
            break;
         case INGAME_MENU_LOAD_STATE:
            strlcpy(text, "Load State", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), "%d", g_extern.state_slot);
            strlcpy(comment, "Load from current state slot.", sizeof(comment));
            break;
         case INGAME_MENU_SAVE_STATE:
            strlcpy(text, "Save State", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), "%d", g_extern.state_slot);
            strlcpy(comment, "Save to current state slot.", sizeof(comment));
            break;
         case SETTING_ASPECT_RATIO:
            strlcpy(text, "Aspect Ratio", sizeof(text));
            strlcpy(setting_text, aspectratio_lut[g_settings.video.aspect_ratio_idx].name, sizeof(setting_text));
            strlcpy(comment, "Change the aspect ratio of the screen.", sizeof(comment));
            break;
         case SETTING_ROTATION:
            strlcpy(text, "Rotation", sizeof(text));
            strlcpy(setting_text, rotation_lut[g_extern.console.screen.orientation], sizeof(setting_text));
            strlcpy(comment, "Change orientation of the screen.", sizeof(comment));
            break;
         case SETTING_CUSTOM_VIEWPORT:
            strlcpy(text, "Custom Ratio", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Allows you to resize the screen.", sizeof(comment));
            break;
         case INGAME_MENU_CORE_OPTIONS_MODE:
            strlcpy(text, "Core Options", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Set core-specific options.", sizeof(comment));
            break;
#ifdef HAVE_SHADER_MANAGER
         case INGAME_MENU_SHADER_OPTIONS_MODE:
            strlcpy(text, "Shader Options", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Set and manage shader options.", sizeof(comment));
            break;
#endif
         case INGAME_MENU_LOAD_GAME_HISTORY_MODE:
            strlcpy(text, "Load Game (History)", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Select a game from the history list.", sizeof(comment));
            break;
         case INGAME_MENU_VIDEO_OPTIONS_MODE:
            strlcpy(text, "Video Options", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Set and manage video options.", sizeof(comment));
            break;
         case INGAME_MENU_AUDIO_OPTIONS_MODE:
            strlcpy(text, "Audio Options", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Set and manage audio options.", sizeof(comment));
            break;
         case INGAME_MENU_INPUT_OPTIONS_MODE:
            strlcpy(text, "Input Options", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Set and manage input options.", sizeof(comment));
            break;
         case INGAME_MENU_PATH_OPTIONS_MODE:
            strlcpy(text, "Path Options", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Set and manage path options.", sizeof(comment));
            break;
         case INGAME_MENU_SETTINGS_MODE:
            strlcpy(text, "Settings", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Set and manage various settings.", sizeof(comment));
            break;
         case INGAME_MENU_FRAME_ADVANCE:
            strlcpy(text, "Frame Advance", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "Press a button to step one frame.", sizeof(comment));
            break;
         case INGAME_MENU_SCREENSHOT_MODE:
            strlcpy(text, "Take Screenshot", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "Take a screenshot.", sizeof(comment));
            break;
         case INGAME_MENU_RESET:
            strlcpy(text, "Restart Game", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "Reset the game.", sizeof(comment));
            break;
         case INGAME_MENU_RETURN_TO_GAME:
            strlcpy(text, "Resume Game", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "Resume the currently loaded game.", sizeof(comment));
            break;
         case INGAME_MENU_CHANGE_GAME:
            strlcpy(text, "Load Game", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Select a game to be loaded.", sizeof(comment));
            break;
         case INGAME_MENU_CHANGE_LIBRETRO_CORE:
            strlcpy(text, "Core", sizeof(text));
            strlcpy(setting_text, "...", sizeof(setting_text));
            strlcpy(comment, "Choose another libretro core.", sizeof(comment));
            break;
#ifdef HAVE_MULTIMAN
         case INGAME_MENU_RETURN_TO_MULTIMAN:
            strlcpy(text, "Return to multiMAN", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "Quit RetroArch and return to multiMAN.", sizeof(comment));
            break;
#endif
         case INGAME_MENU_QUIT_RETROARCH:
            strlcpy(text, "Quit RetroArch", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "Quit RetroArch.", sizeof(comment));
            break;
         default:
            break;
#ifdef HAVE_SHADER_MANAGER
         case SHADERMAN_LOAD_CGP:
            strlcpy(text, "Load Shader Preset", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "INFO - Select a CGP file.", sizeof(comment));
            break;
         case SHADERMAN_AUTOSTART_CGP_ON_STARTUP:
            strlcpy(text, "Autostart CGP at startup", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "INFO - Auto-load at startup the current shader settings.", sizeof(comment));
            break;
         case SHADERMAN_SAVE_CGP:
            strlcpy(text, "Save Shader Preset", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "INFO - Save current shader settings to a CGP file.", sizeof(comment));
            break;
         case SHADERMAN_SHADER_PASSES:
            strlcpy(text, "Shader Passes", sizeof(text));
            snprintf(setting_text, sizeof(setting_text), "%u", rgui->shader.passes);
            strlcpy(comment, "INFO - Set the amount of shader passes.", sizeof(comment));
            break;
         case SHADERMAN_APPLY_CHANGES:
            strlcpy(text, "Apply Shader Changes", sizeof(text));
            strlcpy(setting_text, "", sizeof(setting_text));
            strlcpy(comment, "INFO - Apply the changes made below.", sizeof(comment));
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
               char type_str[256];
               uint8_t index = (i - SHADERMAN_SHADER_0) / 3;
               if (*rgui->shader.pass[index].source.cg)
                  fill_pathname_base(type_str,
                        rgui->shader.pass[index].source.cg, sizeof(type_str));
               else
                  strlcpy(type_str, "N/A", sizeof(type_str));
               snprintf(text, sizeof(text), "Shader #%d", index);
               strlcpy(setting_text, type_str, sizeof(setting_text));
               strlcpy(comment, "INFO - Select the shader.", sizeof(comment));
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
               char type_str[256];
               uint8_t index = (i - SHADERMAN_SHADER_0) / 3;
               snprintf(text, sizeof(text), "Shader #%d filter", index);
               shader_manager_get_str_filter(type_str, sizeof(type_str), index);
               strlcpy(setting_text, type_str, sizeof(setting_text));
               strlcpy(comment, "INFO - Select the filtering.", sizeof(comment));
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
               char type_str[256];
               uint8_t index = (i - SHADERMAN_SHADER_0) / 3;
               unsigned scale = rgui->shader.pass[index].fbo.scale_x;

               snprintf(text, sizeof(text), "Shader #%d scale", index);

               if (!scale)
                  strlcpy(type_str, "Don't care", sizeof(type_str));
               else
                  snprintf(type_str, sizeof(type_str), "%ux", scale);

               strlcpy(setting_text, type_str, sizeof(setting_text));
               strlcpy(comment, "INFO - Select the scaling factor of this pass.", sizeof(comment));
            }
            break;
#endif
      }
