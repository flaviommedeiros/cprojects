#ifndef WIN32
if (HRN_savedFlags == LINK_UP)
#else
    if (HRN_savedFlags & IFF_UP)
#endif
        return 2;               /* running */
    else
        return 5;
