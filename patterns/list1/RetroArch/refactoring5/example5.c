#ifndef __CELLOS_LV2__
if (*path == '~')
   {
      const char *home = getenv("HOME");
      strlcpy(real_path, home ? home : "", sizeof(real_path));
      strlcat(real_path, path + 1, sizeof(real_path));
   }
   else
#endif
      fill_pathname_resolve_relative(real_path, conf->path,
            path, sizeof(real_path));
