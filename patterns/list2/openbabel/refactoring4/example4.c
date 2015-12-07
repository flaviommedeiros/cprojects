#if ( REPLACE_ALT_WITH_TAUT == 1 )
if ( bond_type != BOND_TAUTOM )
#else
        if ( bond_type != BOND_ALTERN && bond_type != BOND_TAUTOM )
#endif
        {
            int ii;
            /*  change bond type to BOND_TAUTOM presering higher bits marks */
            bond_type = (bond_mark & BOND_MARK_ALL) | BOND_TAUTOM;
            /*  change center-neighbor bond */
            at[center].bond_type[neighbor_index] = bond_type;
            neighbor = at[center].neighbor[neighbor_index];
            for ( ii = 0; ii < at[neighbor].valence; ii ++ ) {
                if ( at[neighbor].neighbor[ii] == center ) {
                    /*  neighbor-center bond found */
                    at[neighbor].bond_type[ii] = bond_type;
                    break;
                }
            }
            n ++;
        }
