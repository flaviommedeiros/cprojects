if ( p != q 
#if (FIX_DALKE_BUGS == 1)
                || !isdigit( UCINT *pStart )
#endif
                ) {
                ret = RI_ERR_SYNTAX; /* syntax error */
                goto exit_function;
            }
