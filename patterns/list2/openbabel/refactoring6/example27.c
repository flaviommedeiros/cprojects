if ( t_group[i].nNumEndpoints != nTautomerGroupNumber[(int)nGroupNumber]
#if ( IGNORE_TGROUP_WITHOUT_H == 1 )
             || (bNoH = (t_group[i].num[0]==t_group[i].num[1]))  /* only for (H,-) t-groups; (+) t-groups are not removed */
#endif
           ) {
            if ( !nTautomerGroupNumber[(int)nGroupNumber] || bNoH ) {
                /*  the group belongs to another disconnected part of the structure or has only charges */
                /*  Remove the group */
                num_t --;
                if ( i < num_t )
                    memmove( t_group+i, t_group+i+1, (num_t-i)*sizeof(t_group[0]) );
                if ( bNoH ) {
                    /*  group contains no mobile hydrogen atoms, only charges. Prepare to remove it. */
                    nTautomerGroupNumber[(int)nGroupNumber] = 0;
                    num_groups_noH ++;
                }
                /*i --;*/
            } else {
                /*  different number of endpoints */
                goto err_exit_function; /*  program error */ /*   <BRKPT> */
            }
        } else {
            /*  renumber t_group and prepare to renumber at[i].endpoint */
            nTautomerGroupNumber[(int)nGroupNumber] =
            t_group[i].nGroupNumber                 = ++nNewGroupNumber; /*  = i+1 */
            /*  get first group atom orig. number position in the nEndpointAtomNumber[] */
            /*  and in the tautomer endpoint canon numbers part of the connection table */
            t_group[i].nFirstEndpointAtNoPos = nCurrEndpointAtNoPos[i]  =
                i? (t_group[i-1].nFirstEndpointAtNoPos+t_group[i-1].nNumEndpoints) : 0;
            t_group[i].num[0] = nNumH;
#if ( REMOVE_TGROUP_CHARGE == 1 )
            t_group[i].num[1]  = 0;  /* remove only (-) charges */
#endif
            /* -- wrong condition. Disabled.
            if ( t_group[i].nGroupNumber != i + 1 ) { // for debug only
                goto err_exit_function; // program error
            }
            */
            i ++;
        }
