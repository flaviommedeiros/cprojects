return type == RGUI_BROWSER_DIR_PATH ||
#ifdef HAVE_SHADER_MANAGER
      type == RGUI_SHADER_DIR_PATH ||
#endif
      type == RGUI_SAVESTATE_DIR_PATH ||
      type == RGUI_SAVEFILE_DIR_PATH ||
#ifdef HAVE_OVERLAY
      type == RGUI_OVERLAY_DIR_PATH ||
#endif
      type == RGUI_SYSTEM_DIR_PATH;
