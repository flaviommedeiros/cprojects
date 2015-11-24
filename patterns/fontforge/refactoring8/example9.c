static GMenuItem2 fllist[] = {
    { { (unichar_t *) N_("Font|_New"), (GImage *) "filenew.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'N' }, H_("New|No Shortcut"), NULL, NULL, MenuNew, MID_New },
    { { (unichar_t *) N_("_Open"), (GImage *) "fileopen.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'O' }, H_("Open|No Shortcut"), NULL, NULL, CVMenuOpen, MID_Open },
    { { (unichar_t *) N_("Recen_t"), (GImage *) "filerecent.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 't' }, NULL, dummyitem, MenuRecentBuild, NULL, MID_Recent },
    { { (unichar_t *) N_("_Close"), (GImage *) "fileclose.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'C' }, H_("Close|No Shortcut"), NULL, NULL, CVMenuClose, MID_Close },
    { { (unichar_t *) N_("C_lose Tab"), (GImage *) "menuempty.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'C' }, H_("Close Tab|No Shortcut"), NULL, NULL, CVMenuCloseTab, MID_CloseTab },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Save"), (GImage *) "filesave.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'S' }, H_("Save|No Shortcut"), NULL, NULL, CVMenuSave, 0 },
    { { (unichar_t *) N_("S_ave as..."), (GImage *) "filesaveas.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'a' }, H_("Save as...|No Shortcut"), NULL, NULL, CVMenuSaveAs, 0 },
    { { (unichar_t *) N_("_Generate Fonts..."), (GImage *) "filegenerate.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'G' }, H_("Generate Fonts...|No Shortcut"), NULL, NULL, CVMenuGenerate, 0 },
    { { (unichar_t *) N_("Generate Mac _Family..."), (GImage *) "filegeneratefamily.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'F' }, H_("Generate Mac Family...|No Shortcut"), NULL, NULL, CVMenuGenerateFamily, 0 },
    { { (unichar_t *) N_("Generate TTC..."), (GImage *) "filegeneratefamily.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'F' }, H_("Generate TTC...|No Shortcut"), NULL, NULL, CVMenuGenerateTTC, MID_GenerateTTC },
    { { (unichar_t *) N_("E_xport..."), (GImage *) "fileexport.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 't' }, H_("Export...|No Shortcut"), NULL, NULL, CVMenuExport, 0 },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Import..."), (GImage *) "fileimport.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'I' }, H_("Import...|No Shortcut"), NULL, NULL, CVMenuImport, 0 },
    { { (unichar_t *) N_("_Revert File"), (GImage *) "filerevert.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'R' }, H_("Revert File|No Shortcut"), NULL, NULL, CVMenuRevert, MID_Revert },
    { { (unichar_t *) N_("Revert Gl_yph"), (GImage *) "filerevertglyph.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'R' }, H_("Revert Glyph|No Shortcut"), NULL, NULL, CVMenuRevertGlyph, MID_RevertGlyph },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("Load Word List..."), (GImage *) 0, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'M' }, H_("Load Word List...|No Shortcut"), NULL, NULL, CVAddWordList, 0 },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Print..."), (GImage *) "fileprint.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'P' }, H_("Print...|No Shortcut"), NULL, NULL, CVMenuPrint, 0 },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
#if !defined(_NO_PYTHON)
    { { (unichar_t *) N_("E_xecute Script..."), (GImage *) "python.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'x' }, H_("Execute Script...|No Shortcut"), NULL, NULL, CVMenuExecute, 0 },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
#endif
    { { (unichar_t *) N_("Pr_eferences..."), (GImage *) "fileprefs.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'e' }, H_("Preferences...|No Shortcut"), NULL, NULL, MenuPrefs, 0 },
    { { (unichar_t *) N_("_X Resource Editor..."), (GImage *) "menuempty.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'e' }, H_("X Resource Editor...|No Shortcut"), NULL, NULL, MenuXRes, 0 },
    { { NULL, NULL, COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 1, 0, 0, 0, '\0' }, NULL, NULL, NULL, NULL, 0 }, /* line */
    { { (unichar_t *) N_("_Quit"), (GImage *) "filequit.png", COLOR_DEFAULT, COLOR_DEFAULT, NULL, NULL, 0, 1, 0, 0, 0, 0, 1, 1, 0, 'Q' }, H_("Quit|No Shortcut"), NULL, NULL, MenuExit, MID_Quit },
    GMENUITEM2_EMPTY
};
