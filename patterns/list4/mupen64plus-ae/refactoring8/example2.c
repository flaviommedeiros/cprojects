static const struct blit_table normal_blit_4[] = {
#if SDL_ALTIVEC_BLITTERS
    /* has-altivec | dont-use-prefetch */
    {0x00000000, 0x00000000, 0x00000000, 4, 0x00000000, 0x00000000, 0x00000000,
     6, ConvertAltivec32to32_noprefetch, NO_ALPHA | COPY_ALPHA | SET_ALPHA},
    /* has-altivec */
    {0x00000000, 0x00000000, 0x00000000, 4, 0x00000000, 0x00000000, 0x00000000,
     2, ConvertAltivec32to32_prefetch, NO_ALPHA | COPY_ALPHA | SET_ALPHA},
    /* has-altivec */
    {0x00000000, 0x00000000, 0x00000000, 2, 0x0000F800, 0x000007E0, 0x0000001F,
     2, Blit_RGB888_RGB565Altivec, NO_ALPHA},
#endif
    {0x00FF0000, 0x0000FF00, 0x000000FF, 2, 0x0000F800, 0x000007E0, 0x0000001F,
     0, Blit_RGB888_RGB565, NO_ALPHA},
    {0x00FF0000, 0x0000FF00, 0x000000FF, 2, 0x00007C00, 0x000003E0, 0x0000001F,
     0, Blit_RGB888_RGB555, NO_ALPHA},
    /* Default for 32-bit RGB source, used if no other blitter matches */
    {0, 0, 0, 0, 0, 0, 0, 0, BlitNtoN, 0}
};
