switch (cmd)
   {
      case RETRO_ENVIRONMENT_GET_OVERSCAN:
         *(bool*)data = !g_settings.video.crop_overscan;
         RARCH_LOG("Environ GET_OVERSCAN: %u\n", (unsigned)!g_settings.video.crop_overscan);
         break;

      case RETRO_ENVIRONMENT_GET_CAN_DUPE:
         *(bool*)data = true;
         RARCH_LOG("Environ GET_CAN_DUPE: true\n");
         break;

      case RETRO_ENVIRONMENT_GET_VARIABLE:
      {
         struct retro_variable *var = (struct retro_variable*)data;
         RARCH_LOG("Environ GET_VARIABLE %s:\n", var->key);

         if (g_extern.system.core_options)
            core_option_get(g_extern.system.core_options, var);
         else
            var->value = NULL;

         RARCH_LOG("\t%s\n", var->value ? var->value : "N/A");
         break;
      }

      case RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE:
         *(bool*)data = g_extern.system.core_options ?
            core_option_updated(g_extern.system.core_options) : false;
         break;

      case RETRO_ENVIRONMENT_SET_VARIABLES:
      {
         RARCH_LOG("Environ SET_VARIABLES.\n");

         if (g_extern.system.core_options)
         {
            core_option_flush(g_extern.system.core_options);
            core_option_free(g_extern.system.core_options);
         }

         const struct retro_variable *vars = (const struct retro_variable*)data;

         const char *options_path = g_settings.core_options_path;
         char buf[PATH_MAX];
         if (!*options_path && *g_extern.config_path)
         {
            fill_pathname_resolve_relative(buf, g_extern.config_path, ".retroarch-core-options.cfg", sizeof(buf));
            options_path = buf;
         }
         g_extern.system.core_options = core_option_new(options_path, vars);

         break;
      }

      case RETRO_ENVIRONMENT_SET_MESSAGE:
      {
         const struct retro_message *msg = (const struct retro_message*)data;
         RARCH_LOG("Environ SET_MESSAGE: %s\n", msg->msg);
         if (g_extern.msg_queue)
         {
            msg_queue_clear(g_extern.msg_queue);
            msg_queue_push(g_extern.msg_queue, msg->msg, 1, msg->frames);
         }
         break;
      }

      case RETRO_ENVIRONMENT_SET_ROTATION:
      {
         unsigned rotation = *(const unsigned*)data;
         RARCH_LOG("Environ SET_ROTATION: %u\n", rotation);
         if (!g_settings.video.allow_rotate)
            break;

         g_extern.system.rotation = rotation;

         if (driver.video && driver.video->set_rotation)
         {
            if (driver.video_data)
               video_set_rotation_func(rotation);
         }
         else
            return false;
         break;
      }

      case RETRO_ENVIRONMENT_SHUTDOWN:
         RARCH_LOG("Environ SHUTDOWN.\n");
         g_extern.system.shutdown = true;
         break;

      case RETRO_ENVIRONMENT_SET_PERFORMANCE_LEVEL:
         g_extern.system.performance_level = *(const unsigned*)data;
         RARCH_LOG("Environ PERFORMANCE_LEVEL: %u.\n", g_extern.system.performance_level);
         break;

      case RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY:
         *(const char **)data = *g_settings.system_directory ? g_settings.system_directory : NULL;
         RARCH_LOG("Environ SYSTEM_DIRECTORY: \"%s\".\n", g_settings.system_directory);
         break;

      case RETRO_ENVIRONMENT_SET_PIXEL_FORMAT:
      {
         enum retro_pixel_format pix_fmt = *(const enum retro_pixel_format*)data;
         switch (pix_fmt)
         {
            case RETRO_PIXEL_FORMAT_0RGB1555:
               RARCH_LOG("Environ SET_PIXEL_FORMAT: 0RGB1555.\n");
               break;

            case RETRO_PIXEL_FORMAT_RGB565:
               RARCH_LOG("Environ SET_PIXEL_FORMAT: RGB565.\n");
               break;
            case RETRO_PIXEL_FORMAT_XRGB8888:
               RARCH_LOG("Environ SET_PIXEL_FORMAT: XRGB8888.\n");
               break;
            default:
               return false;
         }
         
         g_extern.system.pix_fmt = pix_fmt;
         break;
      }

      case RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS:
      {
         memset(g_extern.system.input_desc_btn, 0, sizeof(g_extern.system.input_desc_btn));

         const struct retro_input_descriptor *desc = (const struct retro_input_descriptor*)data;
         for (; desc->description; desc++)
         {
            if (desc->port >= MAX_PLAYERS)
               continue;

            if (desc->device != RETRO_DEVICE_JOYPAD) // Ignore all others for now.
               continue;

            if (desc->id >= RARCH_FIRST_CUSTOM_BIND)
               continue;

            g_extern.system.input_desc_btn[desc->port][desc->id] = desc->description;
         }

         static const char *libretro_btn_desc[] = {
            "B (bottom)", "Y (left)", "Select", "Start",
            "D-Pad Up", "D-Pad Down", "D-Pad Left", "D-Pad Right",
            "A (right)", "X (up)",
            "L", "R", "L2", "R2", "L3", "R3",
         };

         RARCH_LOG("Environ SET_INPUT_DESCRIPTORS:\n");
         for (unsigned p = 0; p < MAX_PLAYERS; p++)
         {
            for (unsigned id = 0; id < RARCH_FIRST_CUSTOM_BIND; id++)
            {
               const char *desc = g_extern.system.input_desc_btn[p][id];
               if (desc)
               {
                  RARCH_LOG("\tRetroPad, Player %u, Button \"%s\" => \"%s\"\n",
                        p + 1, libretro_btn_desc[id], desc);
               }
            }
         }

         break;
      }
      
      case RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK:
      {
         RARCH_LOG("Environ SET_KEYBOARD_CALLBACK.\n");
         const struct retro_keyboard_callback *info = (const struct retro_keyboard_callback*)data;
         g_extern.system.key_event = info->callback;
         break;
      }

      case RETRO_ENVIRONMENT_SET_DISK_CONTROL_INTERFACE:
         RARCH_LOG("Environ SET_DISK_CONTROL_INTERFACE.\n");
         g_extern.system.disk_control = *(const struct retro_disk_control_callback*)data;
         break;

      case RETRO_ENVIRONMENT_SET_HW_RENDER:
      case RETRO_ENVIRONMENT_SET_HW_RENDER | RETRO_ENVIRONMENT_EXPERIMENTAL: // ABI compat
      {
         RARCH_LOG("Environ SET_HW_RENDER.\n");
         struct retro_hw_render_callback *cb = (struct retro_hw_render_callback*)data;
         switch (cb->context_type)
         {
            case RETRO_HW_CONTEXT_NONE:
               RARCH_LOG("Requesting no HW context.\n");
               break;

#if defined(HAVE_OPENGLES2)
            case RETRO_HW_CONTEXT_OPENGLES2:
               RARCH_LOG("Requesting OpenGLES2 context.\n");
               driver.video = &video_gl;
               break;

            case RETRO_HW_CONTEXT_OPENGL:
            case RETRO_HW_CONTEXT_OPENGL_CORE:
               RARCH_ERR("Requesting OpenGL context, but RetroArch is compiled against OpenGLES2. Cannot use HW context.\n");
               return false;
#elif defined(HAVE_OPENGL)
            case RETRO_HW_CONTEXT_OPENGLES2:
               RARCH_ERR("Requesting OpenGLES2 context, but RetroArch is compiled against OpenGL. Cannot use HW context.\n");
               return false;

            case RETRO_HW_CONTEXT_OPENGL:
               RARCH_LOG("Requesting OpenGL context.\n");
               driver.video = &video_gl;
               break;

            case RETRO_HW_CONTEXT_OPENGL_CORE:
               RARCH_LOG("Requesting core OpenGL context (%u.%u).\n", cb->version_major, cb->version_minor);
               driver.video = &video_gl;
               break;
#endif

            default:
               RARCH_LOG("Requesting unknown context.\n");
               return false;
         }
         cb->get_current_framebuffer = driver_get_current_framebuffer;
         cb->get_proc_address = driver_get_proc_address;

         if (cmd & RETRO_ENVIRONMENT_EXPERIMENTAL) // Old ABI. Don't copy garbage.
            memcpy(&g_extern.system.hw_render_callback, cb, offsetof(struct retro_hw_render_callback, stencil));
         else
            memcpy(&g_extern.system.hw_render_callback, cb, sizeof(*cb));
         break;
      }

      case RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME:
      {
         bool state = *(const bool*)data;
         RARCH_LOG("Environ SET_SUPPORT_NO_GAME: %s.\n", state ? "yes" : "no");
         g_extern.system.no_game = state;
         break;
      }

      case RETRO_ENVIRONMENT_GET_LIBRETRO_PATH:
      {
         const char **path = (const char**)data;
#ifdef HAVE_DYNAMIC
         *path = g_settings.libretro;
#else
         *path = NULL; 
#endif
         break;
      }

#ifdef HAVE_THREADS
      case RETRO_ENVIRONMENT_SET_AUDIO_CALLBACK:
      {
         RARCH_LOG("Environ SET_AUDIO_CALLBACK.\n");
         const struct retro_audio_callback *info = (const struct retro_audio_callback*)data;

#ifdef HAVE_FFMPEG
         if (g_extern.recording) // A/V sync is a must.
            return false;
#endif

#ifdef HAVE_NETPLAY
         if (g_extern.netplay_enable)
            return false;
#endif

         g_extern.system.audio_callback = info->callback;
         break;
      }
#endif

      case RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK:
      {
         RARCH_LOG("Environ SET_FRAME_TIME_CALLBACK.\n");

#ifdef HAVE_NETPLAY
         if (g_extern.netplay_enable) // retro_run() will be called in very strange and mysterious ways, have to disable it.
            return false;
#endif

         const struct retro_frame_time_callback *info = (const struct retro_frame_time_callback*)data;
         g_extern.system.frame_time = *info;
         break;
      }

      default:
         RARCH_LOG("Environ UNSUPPORTED (#%u).\n", cmd);
         return false;
   }
