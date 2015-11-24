static GMenuItem2 ellist[] = {
    { { (unichar_t *) N_("_Font Info..."), (GImage *) "elementfontinfo.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'F' }, H_("Font Info...|No Shortcut"), NULL, NULL, FVMenuFontInfo, MID_FontInfo },
    { { (unichar_t *) N_("_Glyph Info..."), (GImage *) "elementglyphinfo.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Glyph Info...|No Shortcut"), NULL, NULL, FVMenuCharInfo, MID_CharInfo },
    { { (unichar_t *) N_("Other Info"), (GImage *) "elementotherinfo.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Other Info|No Shortcut"), infolist, infolistcheck, NULL, 0 },
    { { (unichar_t *) N_("_Validation"), (GImage *) "elementvalidate.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Validation|No Shortcut"), validlist, validlistcheck, NULL, 0 },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("Bitm_ap Strikes Available..."), (GImage *) "elementbitmapsavail.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'A' }, H_("Bitmap Strikes Available...|No Shortcut"), NULL, NULL, FVMenuBitmaps, MID_AvailBitmaps },
    { { (unichar_t *) N_("Regenerate _Bitmap Glyphs..."), (GImage *) "elementregenbitmaps.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, H_("Regenerate Bitmap Glyphs...|No Shortcut"), NULL, NULL, FVMenuBitmaps, MID_RegenBitmaps },
    { { (unichar_t *) N_("Remove Bitmap Glyphs..."), (GImage *) "elementremovebitmaps.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, '\0' }, H_("Remove Bitmap Glyphs...|No Shortcut"), NULL, NULL, FVMenuBitmaps, MID_RemoveBitmaps },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("St_yle"), (GImage *) "elementstyles.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'S' }, H_("Style|No Shortcut"), eflist, NULL, NULL, MID_Styles },
    { { (unichar_t *) N_("_Transformations"), (GImage *) "elementtransform.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'T' }, H_("Transformations|No Shortcut"), trlist, trlistcheck, NULL, MID_Transform },
    { { (unichar_t *) N_("_Expand Stroke..."), (GImage *) "elementexpandstroke.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'E' }, H_("Expand Stroke...|No Shortcut"), NULL, NULL, FVMenuStroke, MID_Stroke },
#ifdef FONTFORGE_CONFIG_TILEPATH
    { { (unichar_t *) N_("Tile _Path..."), (GImage *) "elementtilepath.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'P' }, H_("Tile Path...|No Shortcut"), NULL, NULL, FVMenuTilePath, MID_TilePath },
    { { (unichar_t *) N_("Tile Pattern..."), (GImage *) "elementtilepattern.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, '\0' }, H_("Tile Pattern...|No Shortcut"), NULL, NULL, FVMenuPatternTile, 0 },
#endif
    { { (unichar_t *) N_("O_verlap"), (GImage *) "overlaprm.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'O' }, H_("Overlap|No Shortcut"), rmlist, NULL, NULL, MID_RmOverlap },
    { { (unichar_t *) N_("_Simplify"), (GImage *) "elementsimplify.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'S' }, H_("Simplify|No Shortcut"), smlist, NULL, NULL, MID_Simplify },
    { { (unichar_t *) N_("Add E_xtrema"), (GImage *) "elementaddextrema.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'x' }, H_("Add Extrema|No Shortcut"), NULL, NULL, FVMenuAddExtrema, MID_AddExtrema },
    { { (unichar_t *) N_("Roun_d"), (GImage *) "elementround.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Round|No Shortcut"), rndlist, NULL, NULL, MID_Round },
    { { (unichar_t *) N_("Autot_race"), (GImage *) "elementautotrace.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'r' }, H_("Autotrace|No Shortcut"), NULL, NULL, FVMenuAutotrace, MID_Autotrace },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Correct Direction"), (GImage *) "elementcorrectdir.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'D' }, H_("Correct Direction|No Shortcut"), NULL, NULL, FVMenuCorrectDir, MID_Correct },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("B_uild"), (GImage *) "elementbuildaccent.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, H_("Build|No Shortcut"), balist, balistcheck, NULL, MID_BuildAccent },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Merge Fonts..."), (GImage *) "elementmergefonts.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'M' }, H_("Merge Fonts...|No Shortcut"), NULL, NULL, FVMenuMergeFonts, MID_MergeFonts },
    { { (unichar_t *) N_("Interpo_late Fonts..."), (GImage *) "elementinterpolatefonts.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'p' }, H_("Interpolate Fonts...|No Shortcut"), NULL, NULL, FVMenuInterpFonts, MID_InterpolateFonts },
    { { (unichar_t *) N_("Compare Fonts..."), (GImage *) "elementcomparefonts.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'p' }, H_("Compare Fonts...|No Shortcut"), NULL, NULL, FVMenuCompareFonts, MID_FontCompare },
    { { (unichar_t *) N_("Compare Layers..."), (GImage *) "elementcomparelayers.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'p' }, H_("Compare Layers...|No Shortcut"), NULL, NULL, FVMenuCompareL2L, 0 },
    GMENUITEM2_EMPTY
};
