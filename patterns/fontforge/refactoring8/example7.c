static GMenuItem2 ellist[] = {
    { { (unichar_t *) N_("_Font Info..."), (GImage *) "elementfontinfo.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'F' }, H_("Font Info...|No Shortcut"), NULL, NULL, MVMenuFontInfo, 0 },
    { { (unichar_t *) N_("Glyph _Info..."), (GImage *) "elementglyphinfo.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Glyph Info...|No Shortcut"), NULL, NULL, MVMenuCharInfo, MID_CharInfo },
    { { (unichar_t *) N_("S_how Dependent"), (GImage *) "elementshowdep.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'D' }, H_("Show Dependent|No Shortcut"), NULL, NULL, MVMenuShowDependents, MID_ShowDependents },
    { { (unichar_t *) N_("Find Pr_oblems..."), (GImage *) "elementfindprobs.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'o' }, H_("Find Problems...|No Shortcut"), NULL, NULL, MVMenuFindProblems, MID_FindProblems },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("Bitm_ap Strikes Available..."), (GImage *) "elementbitmapsavail.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'A' }, H_("Bitmap Strikes Available...|No Shortcut"), NULL, NULL, MVMenuBitmaps, MID_AvailBitmaps },
    { { (unichar_t *) N_("Regenerate _Bitmap Glyphs..."), (GImage *) "elementregenbitmaps.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, H_("Regenerate Bitmap Glyphs...|No Shortcut"), NULL, NULL, MVMenuBitmaps, MID_RegenBitmaps },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Transform..."), (GImage *) "elementtransform.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'T' }, H_("Transform...|No Shortcut"), NULL, NULL, MVMenuTransform, MID_Transform },
#ifdef FONTFORGE_CONFIG_TILEPATH
    { { (unichar_t *) N_("Tile _Path..."), (GImage *) "elementtilepath.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'P' }, H_("Tile Path...|No Shortcut"), NULL, NULL, MVMenuTilePath, MID_TilePath },
#endif
    { { (unichar_t *) N_("_Remove Overlap"), (GImage *) "rmoverlap.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'O' }, H_("Remove Overlap|No Shortcut"), rmlist, NULL, NULL, MID_RmOverlap },
    { { (unichar_t *) N_("_Simplify"), (GImage *) "elementsimplify.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'S' }, H_("Simplify|No Shortcut"), smlist, NULL, NULL, MID_Simplify },
    { { (unichar_t *) N_("Add E_xtrema"), (GImage *) "elementaddextrema.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'x' }, H_("Add Extrema|No Shortcut"), NULL, NULL, MVMenuAddExtrema, MID_AddExtrema },
    { { (unichar_t *) N_("To _Int"), (GImage *) "elementround.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("To Int|No Shortcut"), NULL, NULL, MVMenuRound2Int, MID_Round },
    { { (unichar_t *) N_("Effects"), (GImage *) "elementstyles.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, '\0' }, H_("Effects|No Shortcut"), eflist, NULL, NULL, MID_Effects },
    { { (unichar_t *) N_("Autot_race"), (GImage *) "elementautotrace.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'r' }, H_("Autotrace|No Shortcut"), NULL, NULL, MVMenuAutotrace, MID_Autotrace },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Correct Direction"), (GImage *) "elementcorrectdir.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'D' }, H_("Correct Direction|No Shortcut"), NULL, NULL, MVMenuCorrectDir, MID_Correct },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("B_uild"), (GImage *) "elementbuildaccent.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, H_("Build|No Shortcut"), balist, balistcheck, NULL, MID_BuildAccent },
    GMENUITEM2_EMPTY
};
