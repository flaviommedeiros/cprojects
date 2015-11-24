if ((in_path[0] == ':') &&
#ifdef _WIN32
         ((in_path[1] == '/') || (in_path[1] == '\\'))
#else
         (in_path[1] == '/')
#endif
            )
   {
      size_t src_size;
      char application_dir[PATH_MAX_LENGTH] = {0};

      fill_pathname_application_path(application_dir, sizeof(application_dir));
      path_basedir(application_dir);

      src_size   = strlcpy(out_path, application_dir, size);
      retro_assert(src_size < size);

      out_path  += src_size;
      size      -= src_size;
      in_path   += 2;
   }
