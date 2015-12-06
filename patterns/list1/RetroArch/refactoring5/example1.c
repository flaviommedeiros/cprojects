#ifdef HAVE_MENU
if (*settings->menu_config_directory)
   {
      path_resolve_realpath(settings->menu_config_directory,
            sizeof(settings->menu_config_directory));
      strlcpy(global->path.core_specific_config,
            settings->menu_config_directory,
            sizeof(global->path.core_specific_config));
   }
   else
#endif
   {
      /* Use original config file's directory as a fallback. */
      fill_pathname_basedir(global->path.core_specific_config,
            global->path.config, sizeof(global->path.core_specific_config));
   }
