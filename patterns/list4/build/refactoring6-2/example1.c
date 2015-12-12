while ( ( read( fd, &ar_hdr, SARHDR ) == SARHDR ) &&
        !( memcmp( ar_hdr.ar_fmag, ARFMAG, SARFMAG )
#ifdef ARFZMAG
            /* OSF also has a compressed format */
            && memcmp( ar_hdr.ar_fmag, ARFZMAG, SARFMAG )
#endif
        ) )
    {
        char   lar_name_[ 257 ];
        char * lar_name = lar_name_ + 1;
        long   lar_date;
        long   lar_size;
        long   lar_offset;
        char * c;
        char * src;
        char * dest;

        strncpy( lar_name, ar_hdr.ar_name, sizeof( ar_hdr.ar_name ) );

        sscanf( ar_hdr.ar_date, "%ld", &lar_date );
        sscanf( ar_hdr.ar_size, "%ld", &lar_size );

        if ( ar_hdr.ar_name[ 0 ] == '/' )
        {
            if ( ar_hdr.ar_name[ 1 ] == '/' )
            {
                /* This is the "string table" entry of the symbol table, holding
                 * filename strings longer than 15 characters, i.e. those that
                 * do not fit into ar_name.
                 */
                string_table = (char *)BJAM_MALLOC_ATOMIC( lar_size );
                lseek( fd, offset + SARHDR, 0 );
                if ( read( fd, string_table, lar_size ) != lar_size )
                    out_printf("error reading string table\n");
            }
            else if ( string_table && ar_hdr.ar_name[ 1 ] != ' ' )
            {
                /* Long filenames are recognized by "/nnnn" where nnnn is the
                 * offset of the string in the string table represented in ASCII
                 * decimals.
                 */
                dest = lar_name;
                lar_offset = atoi( lar_name + 1 );
                src = &string_table[ lar_offset ];
                while ( *src != '/' )
                    *dest++ = *src++;
                *dest = '/';
            }
        }

        c = lar_name - 1;
        while ( ( *++c != ' ' ) && ( *c != '/' ) );
        *c = '\0';

        if ( DEBUG_BINDSCAN )
            out_printf( "archive name %s found\n", lar_name );

        sprintf( buf, "%s(%s)", archive, lar_name );

        {
            OBJECT * const member = object_new( buf );
            timestamp time;
            timestamp_init( &time, (time_t)lar_date, 0 );
            (*func)( closure, member, 1 /* time valid */, &time );
            object_free( member );
        }

        offset += SARHDR + ( ( lar_size + 1 ) & ~1 );
        lseek( fd, offset, 0 );
    }
