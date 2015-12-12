switch (thr->send_cmd)
      {
         case CMD_INIT:
            thr->driver_data = thr->driver->init(&thr->info, thr->input, thr->input_data);
            thr->cmd_data.b = thr->driver_data;
            thr->driver->viewport_info(thr->driver_data, &thr->vp);
            thread_reply(thr, CMD_INIT);
            break;

         case CMD_FREE:
            if (thr->driver_data)
               thr->driver->free(thr->driver_data);
            thr->driver_data = NULL;
            thread_reply(thr, CMD_FREE);
            return;

         case CMD_SET_ROTATION:
            thr->driver->set_rotation(thr->driver_data, thr->cmd_data.i);
            thread_reply(thr, CMD_SET_ROTATION);
            break;

         case CMD_READ_VIEWPORT:
         {
            struct rarch_viewport vp = {0};
            thr->driver->viewport_info(thr->driver_data, &vp);
            if (memcmp(&vp, &thr->read_vp, sizeof(vp)) == 0) // We can read safely
            {
               thr->cmd_data.b = thr->driver->read_viewport(thr->driver_data, (uint8_t*)thr->cmd_data.v);
               thread_reply(thr, CMD_READ_VIEWPORT);
            }
            else // Viewport dimensions changed right after main thread read the async value. Cannot read safely.
            {
               thr->cmd_data.b = false;
               thread_reply(thr, CMD_READ_VIEWPORT);
            }
            break;
         }
            
         case CMD_SET_SHADER:
         {
            bool ret = thr->driver->set_shader(thr->driver_data,
                  thr->cmd_data.set_shader.type,
                  thr->cmd_data.set_shader.path);
            thr->cmd_data.b = ret;
            thread_reply(thr, CMD_SET_SHADER);
            break;
         }

         case CMD_ALIVE:
            thr->cmd_data.b = thr->driver->alive(thr->driver_data);
            thread_reply(thr, CMD_ALIVE);
            break;

#ifdef HAVE_OVERLAY
         case CMD_OVERLAY_ENABLE:
            thr->overlay->enable(thr->driver_data, thr->cmd_data.b);
            thread_reply(thr, CMD_OVERLAY_ENABLE);
            break;

         case CMD_OVERLAY_LOAD:
            thr->cmd_data.b = thr->overlay->load(thr->driver_data,
                  thr->cmd_data.image.data,
                  thr->cmd_data.image.width,
                  thr->cmd_data.image.height);
            thread_reply(thr, CMD_OVERLAY_LOAD);
            break;

         case CMD_OVERLAY_TEX_GEOM:
            thr->overlay->tex_geom(thr->driver_data,
                  thr->cmd_data.rect.x,
                  thr->cmd_data.rect.y,
                  thr->cmd_data.rect.w,
                  thr->cmd_data.rect.h);
            thread_reply(thr, CMD_OVERLAY_TEX_GEOM);
            break;

         case CMD_OVERLAY_VERTEX_GEOM:
            thr->overlay->vertex_geom(thr->driver_data,
                  thr->cmd_data.rect.x,
                  thr->cmd_data.rect.y,
                  thr->cmd_data.rect.w,
                  thr->cmd_data.rect.h);
            thread_reply(thr, CMD_OVERLAY_VERTEX_GEOM);
            break;

         case CMD_OVERLAY_FULL_SCREEN:
            thr->overlay->full_screen(thr->driver_data, thr->cmd_data.b);
            thread_reply(thr, CMD_OVERLAY_FULL_SCREEN);
            break;

         case CMD_OVERLAY_SET_ALPHA:
            thr->overlay->set_alpha(thr->driver_data, thr->cmd_data.f);
            thread_reply(thr, CMD_OVERLAY_SET_ALPHA);
            break;
#endif

         case CMD_POKE_SET_FILTERING:
            thr->poke->set_filtering(thr->driver_data,
                  thr->cmd_data.filtering.index,
                  thr->cmd_data.filtering.smooth);
            thread_reply(thr, CMD_POKE_SET_FILTERING);
            break;

         case CMD_POKE_SET_ASPECT_RATIO:
            thr->poke->set_aspect_ratio(thr->driver_data,
                  thr->cmd_data.i);
            thread_reply(thr, CMD_POKE_SET_ASPECT_RATIO);
            break;

         default:
            thread_reply(thr, thr->send_cmd);
            break;
      }
