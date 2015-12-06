GTextInfo mastercounts[] = {
    { (unichar_t *) "1", NULL, 0, 0, (void *) 1, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "2", NULL, 0, 0, (void *) 2, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "3", NULL, 0, 0, (void *) 3, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "4", NULL, 0, 0, (void *) 4, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "5", NULL, 0, 0, (void *) 5, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "6", NULL, 0, 0, (void *) 6, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "7", NULL, 0, 0, (void *) 7, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "8", NULL, 0, 0, (void *) 8, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "9", NULL, 0, 0, (void *) 9, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "10", NULL, 0, 0, (void *) 10, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "11", NULL, 0, 0, (void *) 11, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "12", NULL, 0, 0, (void *) 12, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "13", NULL, 0, 0, (void *) 13, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "14", NULL, 0, 0, (void *) 14, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "15", NULL, 0, 0, (void *) 15, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "16", NULL, 0, 0, (void *) 16, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "17", NULL, 0, 0, (void *) 17, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "18", NULL, 0, 0, (void *) 18, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "19", NULL, 0, 0, (void *) 19, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "20", NULL, 0, 0, (void *) 20, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "21", NULL, 0, 0, (void *) 21, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "22", NULL, 0, 0, (void *) 22, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "23", NULL, 0, 0, (void *) 23, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "24", NULL, 0, 0, (void *) 24, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "25", NULL, 0, 0, (void *) 25, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "26", NULL, 0, 0, (void *) 26, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
    { (unichar_t *) "27", NULL, 0, 0, (void *) 27, NULL, 0, 0, 0, 0, 0, 0, 1, 0, 0, '\0'},
#if AppleMmMax!=26
 #error "The mastercounts array needs to be expanded to match AppleMmMax"
    /* Actually it should be one bigger than AppleMmMax */
#endif
    GTEXTINFO_EMPTY
};
