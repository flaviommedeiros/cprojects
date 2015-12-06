static GTextInfo bitmaptypes[] = {
    { (unichar_t *) N_("BDF"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("In TTF/OTF"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("Apple bitmap only sfnt (dfont)"), NULL, 0, 0, NULL, NULL, 1, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("(faked) MS bitmap only sfnt (ttf)"), NULL, 0, 0, NULL, NULL, 1, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("X11 bitmap only sfnt (otb)"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
#if __Mac
    { (unichar_t *) N_("NFNT (Resource)"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
#else
    { (unichar_t *) N_("NFNT (MacBin)"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
#endif
/* OS/X doesn't seem to support NFNTs, so there's no point in putting them in a dfont */
/*  { (unichar_t *) "NFNT (dfont)", NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },*/
    { (unichar_t *) N_("Win FON"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("Win FNT"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("Palm OS Bitmap"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("PS Type3 Bitmap"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    { (unichar_t *) N_("No Bitmap Fonts"), NULL, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0' },
    GTEXTINFO_EMPTY
};
