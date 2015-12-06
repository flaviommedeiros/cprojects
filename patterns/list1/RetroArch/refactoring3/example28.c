switch (pkt.type)
   {
      case CMD_INIT:
         thr->driver_data = thr->driver->init(&thr->info,
               thr->input, thr->input_data);
         pkt.data.b = thr->driver_data;
         thr->driver->viewport_info(thr->driver_data, &thr->vp);
         thread_reply(thr, &pkt);
         break;

      case CMD_FREE:
         if (thr->driver_data)
         {
            if (thr->driver && thr->driver->free)
               thr->driver->free(thr->driver_data);
         }
         thr->driver_data = NULL;
         thread_reply(thr, &pkt);
         return true;

      case CMD_SET_ROTATION:
         if (thr->driver && thr->driver->set_rotation)
            thr->driver->set_rotation(thr->driver_data, pkt.data.i);
         thread_reply(thr, &pkt);
         break;

      case CMD_READ_VIEWPORT:
      {
         struct video_viewport vp = {0};

         thr->driver->viewport_info(thr->driver_data, &vp);

         if (memcmp(&vp, &thr->read_vp, sizeof(vp)) == 0)
         {
            /* We can read safely
             *
             * read_viewport() in GL driver calls
             * 'cached frame render' to be able to read from
             * back buffer.
             *
             * This means frame() callback in threaded wrapper will
             * be called from this thread, causing a timeout, and
             * no frame to be rendered.
             *
             * To avoid this, set a flag so wrapper can see if
             * it's called in this "special" way. */
            thr->frame.within_thread = true;

            if (thr->driver && thr->driver->read_viewport)
               ret = thr->driver->read_viewport(thr->driver_data,
                     (uint8_t*)pkt.data.v);

            pkt.data.b = ret;
            thr->frame.within_thread = false;
         }
         else
         {
            /* Viewport dimensions changed right after main
             * thread read the async value. Cannot read safely. */
            pkt.data.b = false;
         }
         thread_reply(thr, &pkt);
         break;
      }

      case CMD_SET_SHADER:
         if (thr->driver && thr->driver->set_shader)
            ret = thr->driver->set_shader(thr->driver_data,
                     pkt.data.set_shader.type,
                     pkt.data.set_shader.path);

         pkt.data.b = ret;
         thread_reply(thr, &pkt);
         break;

      case CMD_ALIVE:
         if (thr->driver && thr->driver->alive)
            ret = thr->driver->alive(thr->driver_data);

         pkt.data.b = ret;
         thread_reply(thr, &pkt);
         break;

#ifdef HAVE_OVERLAY
      case CMD_OVERLAY_ENABLE:
         if (thr->overlay && thr->overlay->enable)
            thr->overlay->enable(thr->driver_data, pkt.data.b);
         thread_reply(thr, &pkt);
         break;

      case CMD_OVERLAY_LOAD:

         if (thr->overlay && thr->overlay->load)
            ret = thr->overlay->load(thr->driver_data,
                  pkt.data.image.data,
                  pkt.data.image.num);

         pkt.data.b = ret;
         thr->alpha_mods = pkt.data.image.num;
         thr->alpha_mod = (float*)realloc(thr->alpha_mod,
               thr->alpha_mods * sizeof(float));

         for (i = 0; i < thr->alpha_mods; i++)
         {
            /* Avoid temporary garbage data. */
            thr->alpha_mod[i] = 1.0f;
         }

         thread_reply(thr, &pkt);
         break;

      case CMD_OVERLAY_TEX_GEOM:
         if (thr->overlay && thr->overlay->tex_geom)
            thr->overlay->tex_geom(thr->driver_data,
                  pkt.data.rect.index,
                  pkt.data.rect.x,
                  pkt.data.rect.y,
                  pkt.data.rect.w,
                  pkt.data.rect.h);
         thread_reply(thr, &pkt);
         break;

      case CMD_OVERLAY_VERTEX_GEOM:
         if (thr->overlay && thr->overlay->vertex_geom)
            thr->overlay->vertex_geom(thr->driver_data,
                  pkt.data.rect.index,
                  pkt.data.rect.x,
                  pkt.data.rect.y,
                  pkt.data.rect.w,
                  pkt.data.rect.h);
         thread_reply(thr, &pkt);
         break;

      case CMD_OVERLAY_FULL_SCREEN:
         if (thr->overlay && thr->overlay->full_screen)
            thr->overlay->full_screen(thr->driver_data,
                  pkt.data.b);
         thread_reply(thr, &pkt);
         break;
#endif

      case CMD_POKE_SET_VIDEO_MODE:
         if (thr->poke && thr->poke->set_video_mode)
            thr->poke->set_video_mode(thr->driver_data,
                  pkt.data.new_mode.width,
                  pkt.data.new_mode.height,
                  pkt.data.new_mode.fullscreen);
         thread_reply(thr, &pkt);
         break;
      case CMD_POKE_SET_FILTERING:
         if (thr->poke && thr->poke->set_filtering)
            thr->poke->set_filtering(thr->driver_data,
                  pkt.data.filtering.index,
                  pkt.data.filtering.smooth);
         thread_reply(thr, &pkt);
         break;

      case CMD_POKE_GET_VIDEO_OUTPUT_SIZE:
         if (thr->poke && thr->poke->get_video_output_size)
            thr->poke->get_video_output_size(thr->driver_data,
                  &pkt.data.output.width,
                  &pkt.data.output.height);
         thread_reply(thr, &pkt);
         break;

      case CMD_POKE_GET_VIDEO_OUTPUT_PREV:
         if (thr->poke && thr->poke->get_video_output_prev)
            thr->poke->get_video_output_prev(thr->driver_data);
         thread_reply(thr, &pkt);
         break;

      case CMD_POKE_GET_VIDEO_OUTPUT_NEXT:
         if (thr->poke && thr->poke->get_video_output_next)
            thr->poke->get_video_output_next(thr->driver_data);
         thread_reply(thr, &pkt);
         break;

      case CMD_POKE_SET_ASPECT_RATIO:
         thr->poke->set_aspect_ratio(thr->driver_data,
               pkt.data.i);
         thread_reply(thr, &pkt);
         break;

      case CMD_POKE_SET_OSD_MSG:
         if (thr->poke && thr->poke->set_osd_msg)
            thr->poke->set_osd_msg(thr->driver_data,
                  pkt.data.osd_message.msg,
                  &pkt.data.osd_message.params, NULL);
         thread_reply(thr, &pkt);
         break;

      case CMD_FONT_INIT:
         if (pkt.data.font_init.method)
            pkt.data.font_init.return_value =
                  pkt.data.font_init.method
                  (pkt.data.font_init.font_driver,
                     pkt.data.font_init.font_handle,
                     pkt.data.font_init.video_data,
                     pkt.data.font_init.font_path,
                     pkt.data.font_init.font_size,
                     pkt.data.font_init.api);
         thread_reply(thr, &pkt);
         break;

      case CMD_CUSTOM_COMMAND:
         if (pkt.data.custom_command.method)
            pkt.data.custom_command.return_value =
                  pkt.data.custom_command.method
                  (pkt.data.custom_command.data);
         thread_reply(thr, &pkt);
         break;

      case CMD_NONE:
         /* Never reply on no command. Possible deadlock if
          * thread sends command right after frame update. */
         break;
      default:
         thread_reply(thr, &pkt);
         break;
   }
