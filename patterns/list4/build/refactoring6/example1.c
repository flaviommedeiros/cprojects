if ( ( val = strchr( *e, '=' ) )
#if defined( OS_MAC )
            /* On the mac (MPW), the var=val is actually var\0val */
            /* Think different. */
            || ( val = *e + strlen( *e ) )
#endif
        )
        {
            LIST * l = L0;
            size_t const len = strlen( val + 1 );
            int const quoted = ( val[ 1 ] == '"' ) && ( val[ len ] == '"' ) &&
                ( len > 1 );

            if ( quoted && preprocess )
            {
                string_append_range( buf, val + 2, val + len );
                l = list_push_back( l, object_new( buf->value ) );
                string_truncate( buf, 0 );
            }
            else
            {
                char * p;
                char * pp;
                char split =
#if defined( OPT_NO_EXTERNAL_VARIABLE_SPLIT )
                    '\0'
#elif defined( OS_MAC )
                    ','
#else
                    ' '
#endif
                    ;

                /* Split *PATH at :'s, not spaces. */
                if ( val - 4 >= *e )
                {
                    if ( !strncmp( val - 4, "PATH", 4 ) ||
                        !strncmp( val - 4, "Path", 4 ) ||
                        !strncmp( val - 4, "path", 4 ) )
                        split = SPLITPATH;
                }

                /* Do the split. */
                for
                (
                    pp = val + 1;
                    preprocess && ( ( p = strchr( pp, split ) ) != 0 );
                    pp = p + 1
                )
                {
                    string_append_range( buf, pp, p );
                    l = list_push_back( l, object_new( buf->value ) );
                    string_truncate( buf, 0 );
                }

                l = list_push_back( l, object_new( pp ) );
            }

            /* Get name. */
            string_append_range( buf, *e, val );
            {
                OBJECT * const varname = object_new( buf->value );
                var_set( module, varname, l, VAR_SET );
                object_free( varname );
            }
            string_truncate( buf, 0 );
        }
