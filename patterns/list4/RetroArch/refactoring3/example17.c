switch(menu_type)
   {
#ifdef HAVE_SHADER_MANAGER
      case SHADER_CHOICE:
      case CGP_CHOICE:
#endif
      case BORDER_CHOICE:
      case LIBRETRO_CHOICE:
      case INPUT_PRESET_CHOICE:
      case PATH_SAVESTATES_DIR_CHOICE:
      case PATH_DEFAULT_ROM_DIR_CHOICE:
#ifdef HAVE_XML
      case PATH_CHEATS_DIR_CHOICE:
#endif
      case PATH_SRAM_DIR_CHOICE:
      case PATH_SYSTEM_DIR_CHOICE:
      case FILE_BROWSER_MENU:
         snprintf(msg, sizeof(msg), "PATH: %s", rgui->browser->current_dir.directory_path);

         if (driver.video_poke->set_osd_msg)
            driver.video_poke->set_osd_msg(driver.video_data, msg, &font_parms);
         break;
   }
