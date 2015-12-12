static const GtkItemFactoryEntry menu_items[] = {
    {"/_File", NULL, NULL, 0, "<Branch>"},
#if 0
    {"/File/_New", C(N), func(print_hello), 0, NULL},
    {"/File/_Open", C(O), func(print_hello), 0, NULL},
    {"/File/_Save", C(S), func(print_hello), 0, NULL},
    {"/File/Save _As", NULL, NULL, 0, NULL},
    {"/File/sep1", NULL, NULL, 0, "<Separator>"},
    {"/File/Quit", C(Q), func(gtk_main_quit), 0, NULL},
#endif
    {"/File/_Quit", C(Q), func(delete_event), 0, NULL},

    {"/_Plotting", NULL, NULL, 0, "<Branch>"},
    {"/Plotting/_While advancing", NULL, func(spec_option), 5, NULL},
    {"/Plotting/_After advancing", NULL, func(spec_option), 6, NULL},
    {"/Plotting/Toggle SFB lines", NULL, func(spec_option), 7, NULL},
    {"/Plotting/Toggle orig-diff", NULL, func(spec_option), 8, NULL},

    {"/_Channel", NULL, NULL, 0, "<Branch>"},
    {"/Channel/show _Left", NULL, func(channel_option), 1, NULL},
    {"/Channel/show _Right", NULL, func(channel_option), 2, NULL},
    {"/Channel/show _Mid", NULL, func(channel_option), 3, NULL},
    {"/Channel/show _Side", NULL, func(channel_option), 4, NULL},

    {"/_Spectrum", NULL, NULL, 0, "<Branch>"},
    {"/Spectrum/_Scalefactor bands", NULL, func(spec_option), 1, NULL},
    {"/Spectrum/_Wave number", NULL, func(spec_option), 2, NULL},

    {"/_MDCT", NULL, NULL, 0, "<Branch>"},
    {"/MDCT/_Original", NULL, func(spec_option), 3, NULL},
    {"/MDCT/_Compressed", NULL, func(spec_option), 4, NULL},
    {"/MDCT/_Toggle SFB lines", NULL, func(spec_option), 7, NULL},

    {"/_Stats", NULL, NULL, 0, "<Branch>"},
    {"/Stats/_Show", NULL, func(text_window), 2, NULL},

    {"/_Help", NULL, NULL, 0, "<LastBranch>"},
    {"/_Help/_Documentation", NULL, func(text_window), 0, NULL},
    {"/_Help/_About", NULL, func(text_window), 1, NULL},
};
