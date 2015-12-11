static const struct wl_interface *qt_surface_extension_types[] = {
    NULL,
    NULL,
    &qt_extended_surface_interface,
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    /* FIXME: Set this dynamically to (*WAYLAND_wl_surface_interface) ? 
     * The value comes from auto generated code and does 
     * not appear to actually be used anywhere
     */
    NULL, 
#else
    &wl_surface_interface,
#endif    
};
