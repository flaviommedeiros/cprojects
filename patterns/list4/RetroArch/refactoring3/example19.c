switch(rgui->menu_type)
         {
#ifdef HAVE_SHADER_MANAGER
            case SHADER_CHOICE:
               strlcpy(rgui->shader.pass[shader_choice_set_shader_slot].source.cg, path,
                     sizeof(rgui->shader.pass[shader_choice_set_shader_slot].source.cg));
               break;
            case CGP_CHOICE:
               {
                  config_file_t *conf = NULL;

                  strlcpy(g_settings.video.shader_path, path, sizeof(g_settings.video.shader_path));

                  conf = config_file_new(path);
                  if (conf)
                     gfx_shader_read_conf_cgp(conf, &rgui->shader);
                  config_file_free(conf);

                  if (video_set_shader_func(RARCH_SHADER_CG, path))
                     g_settings.video.shader_enable = true;
                  else
                  {
                     RARCH_ERR("Setting CGP failed.\n");
                     g_settings.video.shader_enable = false;
                  }
               }
               break;
#endif
            case INPUT_PRESET_CHOICE:
               strlcpy(g_extern.input_config_path, path, sizeof(g_extern.input_config_path));
               config_read_keybinds(path);
               break;
            case BORDER_CHOICE:
               if (menu_texture)
               {
#ifdef _XBOX
                  if (menu_texture->vertex_buf)
                  {
                     menu_texture->vertex_buf->Release();
                     menu_texture->vertex_buf = NULL;
                  }
                  if (menu_texture->pixels)
                  {
                     menu_texture->pixels->Release();
                     menu_texture->pixels = NULL;
                  }
#else
                  free(menu_texture->pixels);
                  menu_texture->pixels = NULL;
#endif
                  menu_texture = (struct texture_image*)calloc(1, sizeof(*menu_texture));
               }
               texture_image_load(path, menu_texture);
               strlcpy(g_extern.menu_texture_path, path, sizeof(g_extern.menu_texture_path));

               if (driver.video_poke && driver.video_poke->set_texture_frame)
                  driver.video_poke->set_texture_frame(driver.video_data, menu_texture->pixels,
                        true, menu_texture->width, menu_texture->height, 1.0f);
               break;
            case LIBRETRO_CHOICE:
               strlcpy(g_settings.libretro, path, sizeof(g_settings.libretro));
               g_extern.lifecycle_mode_state |= (1ULL << MODE_EXITSPAWN);
               return -1;
         }
