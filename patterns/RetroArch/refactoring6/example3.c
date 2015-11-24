if(global_library_name_hash != 0
#ifdef HAVE_MENU
         && (global_library_name_hash != MENU_VALUE_NO_CORE)
#endif
         )
   {
      /* per-core saves: append the library_name to the save location */
      if (settings->sort_savefiles_enable && global->dir.savefile[0] != '\0')
      {
         fill_pathname_join(
               current_savefile_dir,
               global->dir.savefile,
               info->info.library_name,
               sizeof(global->dir.savefile));

         /* If path doesn't exist, try to create it,
          * if everything fails revert to the original path. */
         if(!path_is_directory(current_savefile_dir) && current_savefile_dir[0] != '\0')
         {
            path_mkdir(current_savefile_dir);
            if(!path_is_directory(current_savefile_dir))
            {
               RARCH_LOG("Reverting savefile directory to %s\n", global->dir.savefile);
               strlcpy(current_savefile_dir,
                     global->dir.savefile,
                     sizeof(current_savefile_dir));
            }
         }
      }

      /* per-core states: append the library_name to the save location */
      if (settings->sort_savestates_enable && global->dir.savestate[0] != '\0')
      {
         fill_pathname_join(
               current_savestate_dir,
               global->dir.savestate,
               info->info.library_name,
               sizeof(global->dir.savestate));

         /* If path doesn't exist, try to create it.
          * If everything fails, revert to the original path. */
         if(!path_is_directory(current_savestate_dir) && current_savestate_dir[0] != '\0')
         {
            path_mkdir(current_savestate_dir);
            if(!path_is_directory(current_savestate_dir))
            {
               RARCH_LOG("Reverting savestate directory to %s\n", global->dir.savestate);
               strlcpy(current_savestate_dir,
                     global->dir.savestate,
                     sizeof(current_savestate_dir));
            }
         }
      }
   }
