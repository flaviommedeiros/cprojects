switch (label_hash)
      {
#ifdef HAVE_MENU
         case CB_CORE_UPDATER_DOWNLOAD:
            http->cb = &cb_core_updater_download;
            break;
         case CB_CORE_CONTENT_DOWNLOAD:
            http->cb = &cb_core_content_download;
            break;
         case CB_CORE_UPDATER_LIST:
            http->cb = &cb_core_updater_list;
            break;
         case CB_CORE_CONTENT_LIST:
            http->cb = &cb_core_content_list;
            break;
         case CB_UPDATE_ASSETS:
            http->cb = &cb_update_assets;
            break;
         case CB_UPDATE_CORE_INFO_FILES:
            http->cb = &cb_update_core_info_files;
            break;
         case CB_UPDATE_AUTOCONFIG_PROFILES:
            http->cb = &cb_update_autoconfig_profiles;
            break;
         case CB_UPDATE_CHEATS:
            http->cb = &cb_update_cheats;
            break;
         case CB_UPDATE_DATABASES:
            http->cb = &cb_update_databases;
            break;
         case CB_UPDATE_SHADERS_CG:
            http->cb = &cb_update_shaders_cg;
            break;
         case CB_UPDATE_SHADERS_GLSL:
            http->cb = &cb_update_shaders_glsl;
            break;
         case CB_UPDATE_OVERLAYS:
            http->cb = &cb_update_overlays;
            break;
#endif
         default:
            break;
      }
