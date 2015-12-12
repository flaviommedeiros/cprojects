switch(rgui->menu_type)
         {
            case PATH_SAVESTATES_DIR_CHOICE:
               strlcpy(g_extern.savestate_dir, path, sizeof(g_extern.savestate_dir));
               break;
            case PATH_SRAM_DIR_CHOICE:
               strlcpy(g_extern.savefile_dir, path, sizeof(g_extern.savefile_dir));
               break;
            case PATH_DEFAULT_ROM_DIR_CHOICE:
               strlcpy(g_settings.rgui_browser_directory, path, sizeof(g_settings.rgui_browser_directory));
               break;
#ifdef HAVE_XML
            case PATH_CHEATS_DIR_CHOICE:
               strlcpy(g_settings.cheat_database, path, sizeof(g_settings.cheat_database));
               break;
#endif
            case PATH_SYSTEM_DIR_CHOICE:
               strlcpy(g_settings.system_directory, path, sizeof(g_settings.system_directory));
               break;
         }
