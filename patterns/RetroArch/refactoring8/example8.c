rarch_softfilter_t *rarch_softfilter_new(const char *filter_config,
      unsigned threads,
      enum retro_pixel_format in_pixel_format,
      unsigned max_width, unsigned max_height)
{
   softfilter_simd_mask_t cpu_features = retro_get_cpu_features();
   char basedir[PATH_MAX_LENGTH] = {0};
   struct string_list *plugs     = NULL;
   rarch_softfilter_t *filt      = NULL;

   (void)basedir;

   filt = (rarch_softfilter_t*)calloc(1, sizeof(*filt));
   if (!filt)
      return NULL;

   filt->conf = config_file_new(filter_config);
   if (!filt->conf)
   {
      RARCH_ERR("[SoftFilter]: Did not find config: %s\n", filter_config);
      goto error;
   }

#if defined(HAVE_DYLIB)
   fill_pathname_basedir(basedir, filter_config, sizeof(basedir));

   plugs = dir_list_new(basedir, EXT_EXECUTABLES, false, false);
   if (!plugs)
   {
      RARCH_ERR("[SoftFilter]: Could not build up string list...\n");
      goto error;
   }
#endif
   if (!append_softfilter_plugs(filt, plugs))
   {
      RARCH_ERR("[SoftFitler]: Failed to append softfilter plugins...\n");
      goto error;
   }

   if (plugs)
      string_list_free(plugs);
   plugs = NULL;

   if (!create_softfilter_graph(filt, in_pixel_format,
            max_width, max_height, cpu_features, threads))
   {
      RARCH_ERR("[SoftFitler]: Failed to create softfilter graph...\n");
      goto error;
   }

   return filt;

error:
   if (plugs)
      string_list_free(plugs);
   plugs = NULL;
   rarch_softfilter_free(filt);
   return NULL;
}
