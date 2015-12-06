static GMenuItem2 ellist[] = {
    { { (unichar_t *) N_("_Font Info..."), (GImage *) "elementfontinfo.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'F' }, H_("Font Info...|No Shortcut"), NULL, NULL, CVMenuFontInfo, MID_FontInfo },
    { { (unichar_t *) N_("_Glyph Info..."), (GImage *) "elementglyphinfo.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Glyph Info...|No Shortcut"), NULL, NULL, CVMenuCharInfo, MID_CharInfo },
    { { (unichar_t *) N_("Get _Info..."), (GImage *) "elementgetinfo.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Get Info...|No Shortcut"), NULL, NULL, CVMenuGetInfo, MID_GetInfo },
    { { (unichar_t *) N_("S_how Dependent"), (GImage *) "elementshowdep.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'D' }, H_("Show Dependent|No Shortcut"), delist, delistcheck, NULL, MID_ShowDependentRefs },
    { { (unichar_t *) N_("Find Proble_ms..."), (GImage *) "elementfindprobs.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'o' }, H_("Find Problems...|No Shortcut"), NULL, NULL, CVMenuFindProblems, MID_FindProblems },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("Bitm_ap strikes Available..."), (GImage *) "elementbitmapsavail.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'A' }, H_("Bitmap strikes Available...|No Shortcut"), NULL, NULL, CVMenuBitmaps, MID_AvailBitmaps },
    { { (unichar_t *) N_("Regenerate _Bitmap Glyphs..."), (GImage *) "elementregenbitmaps.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'B' }, H_("Regenerate Bitmap Glyphs...|No Shortcut"), NULL, NULL, CVMenuBitmaps, MID_RegenBitmaps },
    { { (unichar_t *) N_("Remove Bitmap Glyphs..."), (GImage *) "elementremovebitmaps.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, '\0' }, H_("Remove Bitmap Glyphs...|No Shortcut"), NULL, NULL, CVMenuBitmaps, MID_RemoveBitmaps },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("St_yles"), (GImage *) "elementstyles.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, '\0' }, H_("Styles|No Shortcut"), eflist, NULL, NULL, MID_Styles },
    { { (unichar_t *) N_("_Transformations"), (GImage *) "elementtransform.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'T' }, H_("Transformations|No Shortcut"), trlist, NULL, NULL, 0 },
    { { (unichar_t *) N_("_Expand Stroke..."), (GImage *) "elementexpandstroke.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'E' }, H_("Expand Stroke...|No Shortcut"), NULL, NULL, CVMenuStroke, MID_Stroke },
#ifdef FONTFORGE_CONFIG_TILEPATH
    { { (unichar_t *) N_("Tile _Path..."), (GImage *) "elementtilepath.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'P' }, H_("Tile Path...|No Shortcut"), NULL, NULL, CVMenuTilePath, MID_TilePath },
    { { (unichar_t *) N_("Tile Pattern..."), (GImage *) "elementtilepattern.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, '\0' }, H_("Tile Pattern...|No Shortcut"), NULL, NULL, CVMenuPatternTile, 0 },
#endif
    { { (unichar_t *) N_("O_verlap"), (GImage *) "overlaprm.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'v' }, H_("Overlap|No Shortcut"), rmlist, NULL, NULL, MID_RmOverlap },
    { { (unichar_t *) N_("_Simplify"), (GImage *) "elementsimplify.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'S' }, H_("Simplify|No Shortcut"), smlist, smlistcheck, NULL, MID_Simplify },
    { { (unichar_t *) N_("Add E_xtrema"), (GImage *) "elementaddextrema.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'x' }, H_("Add Extrema|No Shortcut"), NULL, NULL, CVMenuAddExtrema, MID_AddExtrema },
    { { (unichar_t *) N_("Autot_race"), (GImage *) "elementautotrace.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'r' }, H_("Autotrace|No Shortcut"), NULL, NULL, CVMenuAutotrace, MID_Autotrace },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("A_lign"), (GImage *) "elementalign.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'l' }, H_("Align|No Shortcut"), allist, allistcheck, NULL, MID_Align },
    { { (unichar_t *) N_("Roun_d"), (GImage *) "elementround.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Round|No Shortcut"), rndlist, rndlistcheck, NULL, MID_Round },
    { { (unichar_t *) N_("_Order"), (GImage *) "elementorder.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, '\0' }, H_("Order|No Shortcut"), orlist, orlistcheck, NULL, 0 },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("Check Self-Intersection"), (GImage *) "menuempty.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 1, 0, 0, 0, 1, 1, 0, 'o' }, H_("Clockwise|No Shortcut"), NULL, NULL, CVMenuCheckSelf, MID_CheckSelf },
    { { (unichar_t *) N_("Glyph Self-Intersects"), (GImage *) "menuempty.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 1, 0, 0, 0, 1, 1, 0, 'o' }, H_("Clockwise|No Shortcut"), NULL, NULL, CVMenuGlyphSelfIntersects, MID_GlyphSelfIntersects },
    { { (unichar_t *) N_("Cloc_kwise"), (GImage *) "elementclockwise.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 1, 0, 0, 0, 1, 1, 0, 'o' }, H_("Clockwise|No Shortcut"), NULL, NULL, CVMenuDir, MID_Clockwise },
    { { (unichar_t *) N_("Cou_nter Clockwise"), (GImage *) "elementanticlock.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 1, 0, 0, 0, 1, 1, 0, 'n' }, H_("Counter Clockwise|No Shortcut"), NULL, NULL, CVMenuDir, MID_Counter },
    { { (unichar_t *) N_("_Correct Direction"), (GImage *) "elementcorrectdir.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'D' }, H_("Correct Direction|No Shortcut"), NULL, NULL, CVMenuCorrectDir, MID_Correct },
    { { (unichar_t *) N_("Reverse Direction"), (GImage *) "menuempty.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'D' }, H_("Reverse Direction|No Shortcut"), NULL, NULL, CVMenuReverseDir, MID_ReverseDir },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("Insert Text Outlines..."), (GImage *) "menuempty.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'D' }, H_("Insert Text Outlines|No Shortcut"), NULL, NULL, CVMenuInsertText, MID_InsertText },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("B_uild"), (GImage *) "elementbuildaccent.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'u' }, H_("Build|No Shortcut"), balist, balistcheck, NULL, MID_BuildAccent },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("Compare Layers..."), (GImage *) "elementcomparelayers.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'u' }, H_("Compare Layers...|No Shortcut"), NULL, NULL, CVMenuCompareL2L, 0 },
    GMENUITEM2_EMPTY
};
