if (rgui->need_refresh && (menu_type == RGUI_FILE_DIRECTORY ||
#ifdef HAVE_SHADER_MANAGER
            menu_type_is_shader_browser(menu_type) ||
#endif
            menu_type_is_directory_browser(menu_type) || 
#ifdef HAVE_OVERLAY
            menu_type == RGUI_SETTINGS_OVERLAY_PRESET ||
#endif
            menu_type == RGUI_SETTINGS_CORE ||
            menu_type == RGUI_SETTINGS_OPEN_HISTORY ||
            menu_type == RGUI_SETTINGS_DISK_APPEND))
   {
      rgui->need_refresh = false;
      rgui_list_clear(rgui->selection_buf);

      if (menu_type == RGUI_SETTINGS_OPEN_HISTORY)
         history_parse(rgui);
      else
         directory_parse(rgui, dir, menu_type, rgui->selection_buf);

      // Before a refresh, we could have deleted a file on disk, causing
      // selection_ptr to suddendly be out of range. Ensure it doesn't overflow.
      if (rgui->selection_ptr >= rgui->selection_buf->size && rgui->selection_buf->size)
         rgui->selection_ptr = rgui->selection_buf->size - 1;
      else if (!rgui->selection_buf->size)
         rgui->selection_ptr = 0;
   }
