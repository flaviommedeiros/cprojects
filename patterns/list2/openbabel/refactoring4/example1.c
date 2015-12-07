#if ( USE_ISO_SORT_KEY_HFIXED == 1 )
if ( num_iso_Hfixed || num_iso_NoTautH )
#else
            if ( num_iso_NoTautH )
#endif
            {
                /* check whether we need NoTautH cononicalization */
                memset( nTempRank, 0, num_max * sizeof(nTempRank[0]) );
                for ( i = 0; i < num_atoms; i ++ ) {
                    if ( nTempRank[nSymmRankFixH[i]-1] < i ) {
                        nTempRank[nSymmRankFixH[i]-1] = i; /* greatest class representative */
                    }
                }
                for ( i = 0; i < num_atoms; i ++ ) {
#if ( USE_ISO_SORT_KEY_HFIXED == 1 )       
                    if ( iso_sort_key_Hfixed[i] != iso_sort_key_Hfixed[nTempRank[nSymmRankFixH[i]-1]] )
                        break;
#endif
                    if ( iso_sort_key_NoTautH[i] != iso_sort_key_NoTautH[nTempRank[nSymmRankFixH[i]-1]])
                        break; /* atoms so far found to be equivalent have different isotopic shifts; the canonicalization is needed */
                }
            } else {
                i = num_atoms; /* should not happen */
            }
