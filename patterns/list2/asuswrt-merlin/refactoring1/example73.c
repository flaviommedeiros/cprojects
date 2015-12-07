if (stat(path, &statbuf) < 0) {
        fprintf(stderr, "Cannot access file \"%s\".\n", path);
        QUITFUN(SNMPERR_GENERR, get_user_passphrases_quit);
#ifndef WIN32
    } else if (statbuf.st_mode & (S_IRWXG | S_IRWXO)) {
        fprintf(stderr,
                "File \"%s\" is accessible by group or world.\n", path);
        QUITFUN(SNMPERR_GENERR, get_user_passphrases_quit);
#endif                          /* !WIN32 */
    }
#endif
