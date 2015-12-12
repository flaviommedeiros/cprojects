static const gl_font_renderer_t *gl_font_backends[] = {
#ifdef HAVE_LIBDBGFONT
   &libdbg_font,
#else
   &gl_raster_font,
#endif
};
