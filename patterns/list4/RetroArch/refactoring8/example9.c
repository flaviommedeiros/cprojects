static const font_renderer_driver_t *font_backends[] = {
#ifdef HAVE_FREETYPE
   &ft_font_renderer,
#endif
   &bitmap_font_renderer,
};
