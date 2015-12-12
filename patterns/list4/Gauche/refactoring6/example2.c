if ((unsigned int)*p < 128
        && ((special[(unsigned int)*p]&1)
#if GAUCHE_KEEP_DISJOINT_KEYWORD_OPTION
            || (keyword_disjoint_p && (*p == ':'))
#endif /*GAUCHE_KEEP_DISJOINT_KEYWORD_OPTION*/
            )
        && (!(flags & SCM_SYMBOL_WRITER_NOESCAPE_INITIAL))) {
        escape = TRUE;
    } else {
        const char *q = p;
        for (int i=0; i<siz; i++, q++) {
            if ((unsigned int)*q < 128
                && (special[(unsigned int)*q]&spmask)) {
                escape = TRUE;
                break;
            }
        }
    }
