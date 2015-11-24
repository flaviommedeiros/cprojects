static GMenuItem2 balist[] = {
    { { (unichar_t *) N_("_Build Accented Glyph"), (GImage *) "elementbuildaccent.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, H_("Build Accented Glyph|No Shortcut"), NULL, NULL, FVMenuBuildAccent, MID_BuildAccent },
    { { (unichar_t *) N_("Build _Composite Glyph"), (GImage *) "elementbuildcomposite.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, H_("Build Composite Glyph|No Shortcut"), NULL, NULL, FVMenuBuildComposite, MID_BuildComposite },
    { { (unichar_t *) N_("Buil_d Duplicate Glyph"), (GImage *) "menuempty.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, H_("Build Duplicate Glyph|No Shortcut"), NULL, NULL, FVMenuBuildDuplicate, MID_BuildDuplicates },
#ifdef KOREAN
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) _STR_ShowGrp, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, NULL, NULL, NULL, FVMenuShowGroup },
#endif
    GMENUITEM2_EMPTY
};
