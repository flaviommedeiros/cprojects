#ifndef _DEBUG
if(darktable.unmuted & DT_DEBUG_NAN)
#endif
    {
      dt_pthread_mutex_lock(&pipe->busy_mutex);
      if(pipe->shutdown)
      {
        dt_pthread_mutex_unlock(&pipe->busy_mutex);
        return 1;
      }

      if(strcmp(module->op, "gamma") && bpp == sizeof(float) * 4)
      {
#ifdef HAVE_OPENCL
        if(*cl_mem_output != NULL)
          dt_opencl_copy_device_to_host(pipe->devid, *output, *cl_mem_output, roi_out->width, roi_out->height,
                                        bpp);
#endif
        int hasinf = 0, hasnan = 0;
        float min[3] = { FLT_MAX };
        float max[3] = { FLT_MIN };

        for(int k = 0; k < 4 * roi_out->width * roi_out->height; k++)
        {
          if((k & 3) < 3)
          {
            float f = ((float *)(*output))[k];
            if(isnan(f))
              hasnan = 1;
            else if(isinf(f))
              hasinf = 1;
            else
            {
              min[k & 3] = fmin(f, min[k & 3]);
              max[k & 3] = fmax(f, max[k & 3]);
            }
          }
        }
        gchar *module_label = dt_history_item_get_name(module);
        if(hasnan)
          fprintf(stderr, "[dev_pixelpipe] module `%s' outputs NaNs! [%s]\n", module_label,
                  _pipe_type_to_str(pipe->type));
        if(hasinf)
          fprintf(stderr, "[dev_pixelpipe] module `%s' outputs non-finite floats! [%s]\n", module_label,
                  _pipe_type_to_str(pipe->type));
        fprintf(stderr, "[dev_pixelpipe] module `%s' min: (%f; %f; %f) max: (%f; %f; %f) [%s]\n",
                module_label, min[0], min[1], min[2], max[0], max[1], max[2], _pipe_type_to_str(pipe->type));
        g_free(module_label);
      }
      dt_pthread_mutex_unlock(&pipe->busy_mutex);
    }
