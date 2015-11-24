static const char *const cdtext_name[] = {
#ifdef OLD_API
    [CDTEXT_ARRANGER] = "Arranger",
    [CDTEXT_COMPOSER] = "Composer",
    [CDTEXT_MESSAGE]  =  "Message",
    [CDTEXT_ISRC] =  "ISRC",
    [CDTEXT_PERFORMER] = "Performer",
    [CDTEXT_SONGWRITER] =  "Songwriter",
    [CDTEXT_TITLE] =  "Title",
    [CDTEXT_UPC_EAN] = "UPC_EAN",
#else
    [CDTEXT_FIELD_ARRANGER] = "Arranger",
    [CDTEXT_FIELD_COMPOSER] = "Composer",
    [CDTEXT_FIELD_MESSAGE]  =  "Message",
    [CDTEXT_FIELD_ISRC] =  "ISRC",
    [CDTEXT_FIELD_PERFORMER] = "Performer",
    [CDTEXT_FIELD_SONGWRITER] =  "Songwriter",
    [CDTEXT_FIELD_TITLE] =  "Title",
    [CDTEXT_FIELD_UPC_EAN] = "UPC_EAN",
#endif
};
