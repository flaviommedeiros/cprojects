if (!egl_config_match_pixmap_info((int)(size_t)config - 1, &image) ||
                  !platform_match_pixmap_api_support(pixmap, egl_config_get_api_support((int)(size_t)config - 1))
#if EGL_BRCM_global_image
                  || ((server_handle[1] != (uint32_t)(-1)) && (
                  (!(image.format & IMAGE_FORMAT_LIN) != !linear) ||
                  (!(image.format & IMAGE_FORMAT_PRE) != !premult)))
#endif
                  ) {
                  thread->error = EGL_BAD_MATCH;
                  result = EGL_NO_SURFACE;
               } else {
                  /*
                   * Check that we didn't already use this pixmap in an
                   * earlier call to eglCreatePixmapSurface()
                   */
                  PIXMAP_CHECK_DATA_T pixmap_check_data;
                  pixmap_check_data.process = process;
                  pixmap_check_data.pixmap = pixmap;
                  pixmap_check_data.pixmap_server_handle[0] = 0;
                  pixmap_check_data.pixmap_server_handle[1] = (uint32_t)-1;
                  platform_get_pixmap_server_handle(pixmap, pixmap_check_data.pixmap_server_handle);
                  pixmap_check_data.is_dup = 0;

                  khrn_pointer_map_iterate(&process->surfaces, callback_check_duplicate_pixmap, &pixmap_check_data);

                  if (pixmap_check_data.is_dup) {
                     thread->error = EGL_BAD_ALLOC;
                     result = EGL_NO_SURFACE;
                  } else {
                     surface = egl_surface_create(
                                   (EGLSurface)(size_t)process->next_surface,
                                   PIXMAP,
                                   linear ? LINEAR : SRGB,
                                   premult ? PRE : NONPRE,
                                   1,
                                   image.width, image.height,
                                   config,
                                   0,
                                   PLATFORM_WIN_NONE,
                                   false,
                                   false,
                                   false,
                                   EGL_NO_TEXTURE,
                                   EGL_NO_TEXTURE,
                                   pixmap, ((server_handle[0] == 0) && (server_handle[1] == (uint32_t)(-1))) ? NULL : server_handle);

                     if (surface) {
                        if (khrn_pointer_map_insert(&process->surfaces, process->next_surface, surface)) {
                           thread->error = EGL_SUCCESS;
                           result = (EGLSurface)(size_t)process->next_surface++;
                        } else {
                           thread->error = EGL_BAD_ALLOC;
                           result = EGL_NO_SURFACE;
                           egl_surface_free(surface);
                        }
                     } else {
                        thread->error = EGL_BAD_ALLOC;
                        result = EGL_NO_SURFACE;
                     }
                  }
               }
