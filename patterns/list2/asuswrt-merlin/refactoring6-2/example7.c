while (l > 0 && (path[l - 1] == '/'
#ifdef BACKSLASH_PATH_DELIM
                     || path[l - 1] == '\\'
#endif
               )) {
        path[--l] = '\0';
    }
