static bool create_softfilter_graph(rarch_softfilter_t *filt,
      enum retro_pixel_format in_pixel_format,
      unsigned max_width, unsigned max_height,
      softfilter_simd_mask_t cpu_features,
      unsigned threads)
{
   unsigned input_fmts, input_fmt, output_fmts, i = 0;
   struct config_file_userdata userdata;
   char key[64]  = {0};
   char name[64] = {0};

   (void)i;

   snprintf(key, sizeof(key), "filter");

   if (!config_get_array(filt->conf, key, name, sizeof(name)))
   {
      RARCH_ERR("Could not find 'filter' array in config.\n");
      return false;
   }

   if (filt->num_plugs == 0)
   {
      RARCH_ERR("No filter plugs found. Exiting...\n");
      return false;
   }

   filt->impl = softfilter_find_implementation(filt, name);
   if (!filt->impl)
   {
      RARCH_ERR("Could not find implementation.\n");
      return false;
   }

   userdata.conf = filt->conf;
   /* Index-specific configs take priority over ident-specific. */
   userdata.prefix[0] = key; 
   userdata.prefix[1] = filt->impl->short_ident;

   /* Simple assumptions. */
   filt->pix_fmt = in_pixel_format;
   input_fmts = filt->impl->query_input_formats();

   switch (in_pixel_format)
   {
      case RETRO_PIXEL_FORMAT_XRGB8888:
         input_fmt = SOFTFILTER_FMT_XRGB8888;
         break;
      case RETRO_PIXEL_FORMAT_RGB565:
         input_fmt = SOFTFILTER_FMT_RGB565;
         break;
      default:
         return false;
   }

   if (!(input_fmt & input_fmts))
   {
      RARCH_ERR("Softfilter does not support input format.\n");
      return false;
   }

   output_fmts = filt->impl->query_output_formats(input_fmt);
   /* If we have a match of input/output formats, use that. */
   if (output_fmts & input_fmt)
      filt->out_pix_fmt = in_pixel_format;
   else if (output_fmts & SOFTFILTER_FMT_XRGB8888)
      filt->out_pix_fmt = RETRO_PIXEL_FORMAT_XRGB8888;
   else if (output_fmts & SOFTFILTER_FMT_RGB565)
      filt->out_pix_fmt = RETRO_PIXEL_FORMAT_RGB565;
   else
   {
      RARCH_ERR("Did not find suitable output format for softfilter.\n");
      return false;
   }

   filt->max_width = max_width;
   filt->max_height = max_height;

   filt->impl_data = filt->impl->create(
         &softfilter_config, input_fmt, input_fmt, max_width, max_height,
         threads != RARCH_SOFTFILTER_THREADS_AUTO ? threads : 
         retro_get_cpu_cores(), cpu_features,
         &userdata);
   if (!filt->impl_data)
   {
      RARCH_ERR("Failed to create softfilter state.\n");
      return false;
   }

   threads = filt->impl->query_num_threads(filt->impl_data);
   if (!threads)
   {
      RARCH_ERR("Invalid number of threads.\n");
      return false;
   }

   filt->threads = threads;
   RARCH_LOG("Using %u threads for softfilter.\n", threads);

   filt->packets = (struct softfilter_work_packet*)
      calloc(threads, sizeof(*filt->packets));
   if (!filt->packets)
   {
      RARCH_ERR("Failed to allocate softfilter packets.\n");
      return false;
   }

#ifdef HAVE_THREADS
   filt->thread_data = (struct filter_thread_data*)
      calloc(threads, sizeof(*filt->thread_data));
   if (!filt->thread_data)
      return false;

   for (i = 0; i < threads; i++)
   {
      filt->thread_data[i].userdata = filt->impl_data;
      filt->thread_data[i].done = true;

      filt->thread_data[i].lock = slock_new();
      if (!filt->thread_data[i].lock)
         return false;
      filt->thread_data[i].cond = scond_new();
      if (!filt->thread_data[i].cond)
         return false;
      filt->thread_data[i].thread = sthread_create(
            filter_thread_loop, &filt->thread_data[i]);
      if (!filt->thread_data[i].thread)
         return false;
   }
#endif

   return true;
}
