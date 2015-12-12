if ( !strncmp( AIAMAG, fl_magic, SAIAMAG ) )
    {
        /* read small variant */
        file_archscan_small( fd, archive, func, closure );
    }
#ifdef AR_HSZ_BIG
    else if ( !strncmp( AIAMAGBIG, fl_magic, SAIAMAG ) )
    {
        /* read big variant */
        file_archscan_big( fd, archive, func, closure );
    }
#endif
