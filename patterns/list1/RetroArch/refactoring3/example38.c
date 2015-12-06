switch (type)
      {
         case MENU_SETTING_ACTION_CORE_DISK_OPTIONS:
            BIND_ACTION_OK(cbs, action_ok_push_default);
            break;
         case MENU_FILE_PLAYLIST_ENTRY:
            BIND_ACTION_OK(cbs, action_ok_playlist_entry);
            break;
         case MENU_FILE_RPL_ENTRY:
            BIND_ACTION_OK(cbs, action_ok_rpl_entry);
            break;
         case MENU_FILE_PLAYLIST_COLLECTION:
            BIND_ACTION_OK(cbs, action_ok_playlist_collection);
            break;
         case MENU_FILE_CONTENTLIST_ENTRY:
            BIND_ACTION_OK(cbs, action_ok_push_generic_list);
            break;
         case MENU_FILE_CHEAT:
            BIND_ACTION_OK(cbs, action_ok_cheat_file_load);
            break;
         case MENU_FILE_RECORD_CONFIG:
            BIND_ACTION_OK(cbs, action_ok_record_configfile_load);
            break;
         case MENU_FILE_REMAP:
            BIND_ACTION_OK(cbs, action_ok_remap_file_load);
            break;
         case MENU_FILE_SHADER_PRESET:
            switch (menu_label_hash)
            {
               case MENU_LABEL_SCAN_FILE:
                  break;
               default:
                  BIND_ACTION_OK(cbs, action_ok_shader_preset_load);
                  break;
            }
            break;
         case MENU_FILE_SHADER:
            switch (menu_label_hash)
            {
               case MENU_LABEL_SCAN_FILE:
                  break;
               default:
                  BIND_ACTION_OK(cbs, action_ok_shader_pass_load);
                  break;
            }
            break;
         case MENU_FILE_IMAGE:
            switch (menu_label_hash)
            {
               case MENU_LABEL_SCAN_FILE:
                  break;
               default:
                  BIND_ACTION_OK(cbs, action_ok_menu_wallpaper_load);
                  break;
            }
            break;
         case MENU_FILE_USE_DIRECTORY:
            BIND_ACTION_OK(cbs, action_ok_path_use_directory);
            break;
         case MENU_FILE_SCAN_DIRECTORY:
            BIND_ACTION_OK(cbs, action_ok_path_scan_directory);
            break;
         case MENU_FILE_CONFIG:
            BIND_ACTION_OK(cbs, action_ok_config_load);
            break;
         case MENU_FILE_PARENT_DIRECTORY:
            BIND_ACTION_OK(cbs, action_ok_parent_directory_push);
            break;
         case MENU_FILE_DIRECTORY:
            BIND_ACTION_OK(cbs, action_ok_directory_push);
            break;
         case MENU_FILE_CARCHIVE:
            switch (menu_label_hash)
            {
               case MENU_LABEL_DETECT_CORE_LIST:
                  BIND_ACTION_OK(cbs, action_ok_compressed_archive_push_detect_core);
                  break;
               case MENU_LABEL_SCAN_FILE:
                  break;
               default:
                  BIND_ACTION_OK(cbs, action_ok_compressed_archive_push);
                  break;
            }
            break;
         case MENU_FILE_CORE:
            switch (menu_label_hash)
            {
               case MENU_LABEL_DEFERRED_CORE_LIST:
                  BIND_ACTION_OK(cbs, action_ok_core_load_deferred);
                  break;
               case MENU_LABEL_DEFERRED_CORE_LIST_SET:
                  BIND_ACTION_OK(cbs, action_ok_core_deferred_set);
                  break;
               case MENU_LABEL_CORE_LIST:
                  BIND_ACTION_OK(cbs, action_ok_core_load);
                  break;
               case MENU_LABEL_CORE_UPDATER_LIST:
                  BIND_ACTION_OK(cbs, action_ok_deferred_list_stub);
                  break;
            }
            break;
         case MENU_FILE_DOWNLOAD_CORE_CONTENT:
            BIND_ACTION_OK(cbs, action_ok_core_content_download);
            break;
         case MENU_FILE_DOWNLOAD_CORE:
            BIND_ACTION_OK(cbs, action_ok_core_updater_download);
            break;
         case MENU_FILE_DOWNLOAD_CORE_INFO:
            break;
         case MENU_FILE_RDB:
            switch (menu_label_hash)
            {
               case MENU_LABEL_DEFERRED_DATABASE_MANAGER_LIST:
                  BIND_ACTION_OK(cbs, action_ok_deferred_list_stub);
                  break;
               case MENU_LABEL_DATABASE_MANAGER_LIST:
               case MENU_VALUE_HORIZONTAL_MENU:
                  BIND_ACTION_OK(cbs, action_ok_database_manager_list);
                  break;
            }
            break;
         case MENU_FILE_RDB_ENTRY:
            BIND_ACTION_OK(cbs, action_ok_rdb_entry);
            break;
         case MENU_FILE_CURSOR:
            switch (menu_label_hash)
            {
               case MENU_LABEL_DEFERRED_DATABASE_MANAGER_LIST:
                  BIND_ACTION_OK(cbs, action_ok_deferred_list_stub);
                  break;
               case MENU_LABEL_CURSOR_MANAGER_LIST:
                  BIND_ACTION_OK(cbs, action_ok_cursor_manager_list);
                  break;
            }
            break;
         case MENU_FILE_FONT:
         case MENU_FILE_OVERLAY:
         case MENU_FILE_AUDIOFILTER:
         case MENU_FILE_VIDEOFILTER:
            BIND_ACTION_OK(cbs, action_ok_set_path);
            break;
#ifdef HAVE_COMPRESSION
         case MENU_FILE_IN_CARCHIVE:
#endif
         case MENU_FILE_PLAIN:
            switch (menu_label_hash)
            {
               case MENU_LABEL_SCAN_FILE:
                  BIND_ACTION_OK(cbs, action_ok_scan_file);
                  break;
               case MENU_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST:
               case MENU_LABEL_DETECT_CORE_LIST:
               case MENU_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE:
#ifdef HAVE_COMPRESSION
                  if (type == MENU_FILE_IN_CARCHIVE)
                  {
                     BIND_ACTION_OK(cbs, action_ok_file_load_with_detect_core_carchive);
                  }
                  else
#endif
                  {
                     BIND_ACTION_OK(cbs, action_ok_file_load_with_detect_core);
                  }
                  break;
               case MENU_LABEL_DISK_IMAGE_APPEND:
                  BIND_ACTION_OK(cbs, action_ok_disk_image_append);
                  break;
               default:
                  BIND_ACTION_OK(cbs, action_ok_file_load);
                  break;
            }
            break;
         case MENU_FILE_MOVIE:
         case MENU_FILE_MUSIC:
#ifdef HAVE_FFMPEG
            switch (menu_label_hash)
            {
               case MENU_LABEL_SCAN_FILE:
                  break;
               default:
                  BIND_ACTION_OK(cbs, action_ok_file_load_ffmpeg);
                  break;
            }
#endif
            break;
         case MENU_FILE_IMAGEVIEWER:
            switch (menu_label_hash)
            {
               case MENU_LABEL_SCAN_FILE:
                  break;
               default:
                  BIND_ACTION_OK(cbs, action_ok_file_load_imageviewer);
                  break;
            }
            break;
         case MENU_SETTINGS:
         case MENU_SETTING_GROUP:
         case MENU_SETTING_SUBGROUP:
            BIND_ACTION_OK(cbs, action_ok_push_default);
            break;
         case MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_CYCLE_TRAY_STATUS:
            BIND_ACTION_OK(cbs, action_ok_disk_cycle_tray_status);
            break;
         case MENU_SETTINGS_CORE_OPTION_CREATE:
            BIND_ACTION_OK(cbs, action_ok_option_create);
            break;
         default:
            return -1;
      }
