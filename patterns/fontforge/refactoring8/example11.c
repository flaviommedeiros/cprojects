static GMenuItem2 vwlist[] = {
    { { (unichar_t *) N_("_Fit"), (GImage *) "viewfit.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'F' }, H_("Fit|No Shortcut"), NULL, NULL, CVMenuScale, MID_Fit },
    { { (unichar_t *) N_("Z_oom out"), (GImage *) "viewzoomout.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'o' }, H_("Zoom out|No Shortcut"), NULL, NULL, CVMenuScale, MID_ZoomOut },
    { { (unichar_t *) N_("Zoom _in"), (GImage *) "viewzoomin.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'i' }, H_("Zoom in|No Shortcut"), NULL, NULL, CVMenuScale, MID_ZoomIn },
#if HANYANG
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Display Compositions..."), NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'i' }, H_("Display Compositions...|No Shortcut"), NULL, NULL, CVDisplayCompositions, MID_DisplayCompositions },
#endif
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Next Glyph"), (GImage *) "viewnext.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'N' }, H_("Next Glyph|No Shortcut"), NULL, NULL, CVMenuChangeChar, MID_Next },
    { { (unichar_t *) N_("_Prev Glyph"), (GImage *) "viewprev.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'P' }, H_("Prev Glyph|No Shortcut"), NULL, NULL, CVMenuChangeChar, MID_Prev },
    { { (unichar_t *) N_("Next _Defined Glyph"), (GImage *) "viewnextdef.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'D' }, H_("Next Defined Glyph|No Shortcut"), NULL, NULL, CVMenuChangeChar, MID_NextDef },
    { { (unichar_t *) N_("Prev Defined Gl_yph"), (GImage *) "viewprevdef.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'a' }, H_("Prev Defined Glyph|No Shortcut"), NULL, NULL, CVMenuChangeChar, MID_PrevDef },
    { { (unichar_t *) N_("Form_er Glyph"), (GImage *) "viewformer.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'a' }, H_("Former Glyph|No Shortcut"), NULL, NULL, CVMenuChangeChar, MID_Former },
    { { (unichar_t *) N_("_Goto"), (GImage *) "viewgoto.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'G' }, H_("Goto|No Shortcut"), NULL, NULL, CVMenuGotoChar, MID_Goto },
    { { (unichar_t *) N_("Find In Font _View"), (GImage *) "viewfindinfont.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'V' }, H_("Find In Font View|No Shortcut"), NULL, NULL, CVMenuFindInFontView, MID_FindInFontView },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("N_umber Points"), NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'o' }, H_("Number Points|No Shortcut"), nplist, nplistcheck, NULL, 0 },
    { { (unichar_t *) N_("Grid Fi_t"), NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'l' }, H_("Grid Fit|No Shortcut"), gflist, gflistcheck, NULL, MID_ShowGridFit },
    { { (unichar_t *) N_("Sho_w"), NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'l' }, H_("Show|No Shortcut"), swlist, swlistcheck, NULL, 0 },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("Com_binations"), NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'b' }, H_("Combinations|No Shortcut"), cblist, cblistcheck, NULL, 0 },
    GMENUITEM2_LINE,
    { { (unichar_t *) N_("Next _Line in Word List"),     NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'L' }, H_("Next Line in Word List|No Shortcut"), NULL, NULL, CVMenuNextLineInWordList, MID_NextLineInWordList },
    { { (unichar_t *) N_("Previous Line in _Word List"), NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'W' }, H_("Previous Line in Word List|No Shortcut"), NULL, NULL, CVMenuPrevLineInWordList, MID_PrevLineInWordList },
    GMENUITEM2_EMPTY
};
