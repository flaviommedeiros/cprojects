static const struct va_native_display *const native_displays[] = {
#if HAVE_VAAPI_X11
    &disp_x11,
#endif
    NULL
};
