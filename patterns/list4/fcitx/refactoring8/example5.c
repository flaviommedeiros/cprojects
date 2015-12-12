static guint16 cedilla_compose_seqs[] = {
#ifdef DEPRECATED_GDK_KEYSYMS
    GDK_dead_acute, GDK_C, 0, 0, 0, 0x00C7, /* LATIN_CAPITAL_LETTER_C_WITH_CEDILLA */
    GDK_dead_acute, GDK_c, 0, 0, 0, 0x00E7, /* LATIN_SMALL_LETTER_C_WITH_CEDILLA */
    GDK_Multi_key, GDK_apostrophe, GDK_C, 0, 0, 0x00C7, /* LATIN_CAPITAL_LETTER_C_WITH_CEDILLA */
    GDK_Multi_key, GDK_apostrophe, GDK_c, 0, 0, 0x00E7, /* LATIN_SMALL_LETTER_C_WITH_CEDILLA */
    GDK_Multi_key, GDK_C, GDK_apostrophe, 0, 0, 0x00C7, /* LATIN_CAPITAL_LETTER_C_WITH_CEDILLA */
    GDK_Multi_key, GDK_c, GDK_apostrophe, 0, 0, 0x00E7, /* LATIN_SMALL_LETTER_C_WITH_CEDILLA */
#else
    GDK_KEY_dead_acute, GDK_KEY_C, 0, 0, 0, 0x00C7, /* LATIN_CAPITAL_LETTER_C_WITH_CEDILLA */
    GDK_KEY_dead_acute, GDK_KEY_c, 0, 0, 0, 0x00E7, /* LATIN_SMALL_LETTER_C_WITH_CEDILLA */
    GDK_KEY_Multi_key, GDK_KEY_apostrophe, GDK_KEY_C, 0, 0, 0x00C7, /* LATIN_CAPITAL_LETTER_C_WITH_CEDILLA */
    GDK_KEY_Multi_key, GDK_KEY_apostrophe, GDK_KEY_c, 0, 0, 0x00E7, /* LATIN_SMALL_LETTER_C_WITH_CEDILLA */
    GDK_KEY_Multi_key, GDK_KEY_C, GDK_KEY_apostrophe, 0, 0, 0x00C7, /* LATIN_CAPITAL_LETTER_C_WITH_CEDILLA */
    GDK_KEY_Multi_key, GDK_KEY_c, GDK_KEY_apostrophe, 0, 0, 0x00E7, /* LATIN_SMALL_LETTER_C_WITH_CEDILLA */
#endif
};
