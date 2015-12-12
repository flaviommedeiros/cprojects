switch (type)
         {
            case RGUI_SETTINGS_VIDEO_ROTATION:
               strlcpy(type_str, rotation_lut[g_extern.console.screen.orientation],
                     sizeof(type_str));
               break;
            case RGUI_SETTINGS_VIDEO_SOFT_FILTER:
               snprintf(type_str, sizeof(type_str),
                     (g_extern.lifecycle_mode_state & (1ULL << MODE_VIDEO_SOFT_FILTER_ENABLE)) ? "ON" : "OFF");
               break;
            case RGUI_SETTINGS_VIDEO_FILTER:
               if (g_settings.video.smooth)
                  strlcpy(type_str, "Bilinear filtering", sizeof(type_str));
               else
                  strlcpy(type_str, "Point filtering", sizeof(type_str));
               break;
            case RGUI_SETTINGS_VIDEO_GAMMA:
               snprintf(type_str, sizeof(type_str), "%d", g_extern.console.screen.gamma_correction);
               break;
            case RGUI_SETTINGS_VIDEO_VSYNC:
               strlcpy(type_str, g_settings.video.vsync ? "ON" : "OFF", sizeof(type_str));
               break;
            case RGUI_SETTINGS_VIDEO_HARD_SYNC:
               strlcpy(type_str, g_settings.video.hard_sync ? "ON" : "OFF", sizeof(type_str));
               break;
            case RGUI_SETTINGS_VIDEO_HARD_SYNC_FRAMES:
               snprintf(type_str, sizeof(type_str), "%u", g_settings.video.hard_sync_frames);
               break;
            case RGUI_SETTINGS_VIDEO_REFRESH_RATE_AUTO:
            {
               double refresh_rate = 0.0;
               double deviation = 0.0;
               unsigned sample_points = 0;
               if (driver_monitor_fps_statistics(&refresh_rate, &deviation, &sample_points))
                  snprintf(type_str, sizeof(type_str), "%.3f Hz (%.1f%% dev, %u samples)", refresh_rate, 100.0 * deviation, sample_points);
               else
                  strlcpy(type_str, "N/A", sizeof(type_str));
               break;
            }
            case RGUI_SETTINGS_VIDEO_INTEGER_SCALE:
               strlcpy(type_str, g_settings.video.scale_integer ? "ON" : "OFF", sizeof(type_str));
               break;
            case RGUI_SETTINGS_VIDEO_ASPECT_RATIO:
               strlcpy(type_str, aspectratio_lut[g_settings.video.aspect_ratio_idx].name, sizeof(type_str));
               break;
#ifdef GEKKO
            case RGUI_SETTINGS_VIDEO_RESOLUTION:
               strlcpy(type_str, gx_get_video_mode(), sizeof(type_str));
               break;
#endif

            case RGUI_FILE_PLAIN:
               strlcpy(type_str, "(FILE)", sizeof(type_str));
               w = 6;
               break;
            case RGUI_FILE_DIRECTORY:
               strlcpy(type_str, "(DIR)", sizeof(type_str));
               w = 5;
               break;
            case RGUI_SETTINGS_REWIND_ENABLE:
               if (g_settings.rewind_enable)
                  strlcpy(type_str, "ON", sizeof(type_str));
               else
                  strlcpy(type_str, "OFF", sizeof(type_str));
               break;
            case RGUI_SETTINGS_REWIND_GRANULARITY:
               snprintf(type_str, sizeof(type_str), "%u", g_settings.rewind_granularity);
               break;
            case RGUI_SETTINGS_CONFIG_SAVE_ON_EXIT:
               strlcpy(type_str, g_extern.config_save_on_exit ? "ON" : "OFF", sizeof(type_str));
               break;
            case RGUI_SETTINGS_SRAM_AUTOSAVE:
               strlcpy(type_str, g_settings.autosave_interval ? "ON" : "OFF", sizeof(type_str));
               break;
            case RGUI_SETTINGS_SAVESTATE_SAVE:
            case RGUI_SETTINGS_SAVESTATE_LOAD:
               snprintf(type_str, sizeof(type_str), "%d", g_extern.state_slot);
               break;
            case RGUI_SETTINGS_AUDIO_MUTE:
               if (g_extern.audio_data.mute)
                  strlcpy(type_str, "ON", sizeof(type_str));
               else
                  strlcpy(type_str, "OFF", sizeof(type_str));
               break;
            case RGUI_SETTINGS_AUDIO_CONTROL_RATE_DELTA:
               snprintf(type_str, sizeof(type_str), "%.3f", g_settings.audio.rate_control_delta);
               break;
            case RGUI_SETTINGS_DEBUG_TEXT:
               snprintf(type_str, sizeof(type_str), (g_extern.lifecycle_mode_state & (1ULL << MODE_FPS_DRAW)) ? "ON" : "OFF");
               break;
            case RGUI_BROWSER_DIR_PATH:
               if (*g_settings.rgui_browser_directory)
                  strlcpy(type_str, g_settings.rgui_browser_directory, sizeof(type_str));
               else
                  strlcpy(type_str, "<default>", sizeof(type_str));
               break;
            case RGUI_SAVEFILE_DIR_PATH:
               if (*g_extern.savefile_dir)
                  strlcpy(type_str, g_extern.savefile_dir, sizeof(type_str));
               else
                  strlcpy(type_str, "<ROM dir>", sizeof(type_str));
               break;
#ifdef HAVE_OVERLAY
            case RGUI_OVERLAY_DIR_PATH:
               if (*g_extern.overlay_dir)
                  strlcpy(type_str, g_extern.overlay_dir, sizeof(type_str));
               else
                  strlcpy(type_str, "<default>", sizeof(type_str));
               break;
#endif
            case RGUI_SAVESTATE_DIR_PATH:
               if (*g_extern.savestate_dir)
                  strlcpy(type_str, g_extern.savestate_dir, sizeof(type_str));
               else
                  strlcpy(type_str, "<ROM dir>", sizeof(type_str));
               break;
            case RGUI_SHADER_DIR_PATH:
               if (*g_settings.video.shader_dir)
                  strlcpy(type_str, g_settings.video.shader_dir, sizeof(type_str));
               else
                  strlcpy(type_str, "<default>", sizeof(type_str));
               break;
            case RGUI_SYSTEM_DIR_PATH:
               if (*g_settings.system_directory)
                  strlcpy(type_str, g_settings.system_directory, sizeof(type_str));
               else
                  strlcpy(type_str, "<ROM dir>", sizeof(type_str));
               break;
            case RGUI_SETTINGS_DISK_INDEX:
            {
               const struct retro_disk_control_callback *control = &g_extern.system.disk_control;
               unsigned images = control->get_num_images();
               unsigned current = control->get_image_index();
               if (current >= images)
                  strlcpy(type_str, "No Disk", sizeof(type_str));
               else
                  snprintf(type_str, sizeof(type_str), "%u", current + 1);
               break;
            }
            case RGUI_SETTINGS_OPEN_FILEBROWSER:
            case RGUI_SETTINGS_OPEN_HISTORY:
            case RGUI_SETTINGS_CORE_OPTIONS:
            case RGUI_SETTINGS_CUSTOM_VIEWPORT:
            case RGUI_SETTINGS_TOGGLE_FULLSCREEN:
            case RGUI_SETTINGS_VIDEO_OPTIONS:
            case RGUI_SETTINGS_AUDIO_OPTIONS:
            case RGUI_SETTINGS_DISK_OPTIONS:
#ifdef HAVE_SHADER_MANAGER
            case RGUI_SETTINGS_SHADER_OPTIONS:
            case RGUI_SETTINGS_SHADER_PRESET:
#endif
            case RGUI_SETTINGS_CORE:
            case RGUI_SETTINGS_DISK_APPEND:
            case RGUI_SETTINGS_INPUT_OPTIONS:
            case RGUI_SETTINGS_PATH_OPTIONS:
            case RGUI_SETTINGS_OPTIONS:
               strlcpy(type_str, "...", sizeof(type_str));
               break;
#ifdef HAVE_OVERLAY
            case RGUI_SETTINGS_OVERLAY_PRESET:
               strlcpy(type_str, path_basename(g_settings.input.overlay), sizeof(type_str));
               break;

            case RGUI_SETTINGS_OVERLAY_OPACITY:
            {
               snprintf(type_str, sizeof(type_str), "%.2f", g_settings.input.overlay_opacity);
               break;
            }

            case RGUI_SETTINGS_OVERLAY_SCALE:
            {
               snprintf(type_str, sizeof(type_str), "%.2f", g_settings.input.overlay_scale);
               break;
            }
#endif
            case RGUI_SETTINGS_BIND_PLAYER:
            {
               snprintf(type_str, sizeof(type_str), "#%d", port + 1);
               break;
            }
            case RGUI_SETTINGS_BIND_DEVICE:
            {
               int map = g_settings.input.joypad_map[port];
               if (map >= 0 && map < MAX_PLAYERS)
               {
                  const char *device_name = g_settings.input.device_names[map];
                  if (*device_name)
                     strlcpy(type_str, device_name, sizeof(type_str));
                  else
                     snprintf(type_str, sizeof(type_str), "N/A (port #%u)", map);
               }
               else
                  strlcpy(type_str, "Disabled", sizeof(type_str));
               break;
            }
            case RGUI_SETTINGS_BIND_DEVICE_TYPE:
            {
               const char *name;
               switch (g_extern.libretro_device[port])
               {
                  case RETRO_DEVICE_NONE: name = "None"; break;
                  case RETRO_DEVICE_JOYPAD: name = "Joypad"; break;
                  case RETRO_DEVICE_ANALOG: name = "Joypad w/ Analog"; break;
                  case RETRO_DEVICE_JOYPAD_MULTITAP: name = "Multitap"; break;
                  case RETRO_DEVICE_MOUSE: name = "Mouse"; break;
                  case RETRO_DEVICE_LIGHTGUN_JUSTIFIER: name = "Justifier"; break;
                  case RETRO_DEVICE_LIGHTGUN_JUSTIFIERS: name = "Justifiers"; break;
                  case RETRO_DEVICE_LIGHTGUN_SUPER_SCOPE: name = "SuperScope"; break;
                  default: name = "Unknown"; break;
               }

               strlcpy(type_str, name, sizeof(type_str));
               break;
            }
            case RGUI_SETTINGS_BIND_DPAD_EMULATION:
               switch (g_settings.input.dpad_emulation[port])
               {
                  case ANALOG_DPAD_NONE:
                     strlcpy(type_str, "None", sizeof(type_str));
                     break;
                  case ANALOG_DPAD_LSTICK:
                     strlcpy(type_str, "Left Stick", sizeof(type_str));
                     break;
                  case ANALOG_DPAD_DUALANALOG:
                     strlcpy(type_str, "Dual Analog", sizeof(type_str));
                     break;
                  case ANALOG_DPAD_RSTICK:
                     strlcpy(type_str, "Right Stick", sizeof(type_str));
                     break;
               }
               break;
            case RGUI_SETTINGS_BIND_UP:
            case RGUI_SETTINGS_BIND_DOWN:
            case RGUI_SETTINGS_BIND_LEFT:
            case RGUI_SETTINGS_BIND_RIGHT:
            case RGUI_SETTINGS_BIND_A:
            case RGUI_SETTINGS_BIND_B:
            case RGUI_SETTINGS_BIND_X:
            case RGUI_SETTINGS_BIND_Y:
            case RGUI_SETTINGS_BIND_START:
            case RGUI_SETTINGS_BIND_SELECT:
            case RGUI_SETTINGS_BIND_L:
            case RGUI_SETTINGS_BIND_R:
            case RGUI_SETTINGS_BIND_L2:
            case RGUI_SETTINGS_BIND_R2:
            case RGUI_SETTINGS_BIND_L3:
            case RGUI_SETTINGS_BIND_R3:
               {
                  unsigned id = rgui_controller_lut[type - RGUI_SETTINGS_BIND_UP];
                  struct platform_bind key_label;
                  strlcpy(key_label.desc, "Unknown", sizeof(key_label.desc));
                  key_label.joykey = g_settings.input.binds[port][id].joykey;

                  if (driver.input->set_keybinds)
                     driver.input->set_keybinds(&key_label, 0, 0, 0, (1ULL << KEYBINDS_ACTION_GET_BIND_LABEL));

                  strlcpy(type_str, key_label.desc, sizeof(type_str));
               }
               break;
            default:
               type_str[0] = 0;
               w = 0;
               break;
         }
