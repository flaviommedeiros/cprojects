if (*cp == '/'
#ifdef XP_WIN
            || *cp == '\\'
#endif
           ) {
            slash = cp;
        }
