#ifdef HAVE_MENU
if (menu_label_hash == MENU_LABEL_LOAD_CONTENT)
   {
      info = (const core_info_t*)&global->core_info.current;

      if (info)
      {
         strlcpy(new_core_path, info->path, sizeof(new_core_path));
         supported = 1;
      }
   }
   else
#endif
      strlcpy(new_core_path, info->path, sizeof(new_core_path));
