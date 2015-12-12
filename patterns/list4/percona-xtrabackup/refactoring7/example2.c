return MY_TEST(strchr(name, FN_LIBCHAR)) 
#if FN_LIBCHAR != '/'
    || MY_TEST(strchr(name,'/'))
#endif
#ifdef FN_DEVCHAR
    || MY_TEST(strchr(name, FN_DEVCHAR))
#endif
    ;
