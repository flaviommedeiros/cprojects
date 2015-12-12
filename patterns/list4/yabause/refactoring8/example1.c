M68K_struct * M68KCoreList[] = {
    &M68KDummy,
    &M68KC68K,
#ifdef HAVE_Q68
    &M68KQ68,
#endif
    NULL
};
