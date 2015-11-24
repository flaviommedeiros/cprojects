static GTextInfo formats[] = {
    { (unichar_t *) N_("EPS"), NULL, 0, 0, (void *) 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("XFig"), NULL, 0, 0, (void *) 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("SVG"), NULL, 0, 0, (void *) 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("Glif"), NULL, 0, 0, (void *) 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("PDF"), NULL, 0, 0, (void *) 4, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("Raph's plate"), NULL, 0, 0, (void *) 5, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
#define BITMAP_FORMAT_START	6
    /* 0=*.xbm, 1=*.bmp, 2=*.png, 3=*.xpm, 4=*.c(fontforge-internal) */
    { (unichar_t *) N_("X Bitmap"), NULL, 0, 0, (void *) BITMAP_FORMAT_START, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("BMP"), NULL, 0, 0, (void *) (BITMAP_FORMAT_START+1), 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
#ifndef _NO_LIBPNG
    { (unichar_t *) N_("png"), NULL, 0, 0, (void *) (BITMAP_FORMAT_START+2), 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
#endif
    { (unichar_t *) N_("X Pixmap"), NULL, 0, 0, (void *) (BITMAP_FORMAT_START+3), 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("C FontForge"), NULL, 0, 0, (void *) (BITMAP_FORMAT_START+4), 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    GTEXTINFO_EMPTY
};
