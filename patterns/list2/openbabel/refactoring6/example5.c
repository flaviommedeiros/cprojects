if ( !nSymmRankFixHIso || !nCanonRankFixHIso || !nAtomNumberCanonFixHIso ||
#if ( USE_ISO_SORT_KEY_HFIXED == 1 )       
                 !iso_sort_key_Hfixed ||
#endif
                 !iso_sort_key_NoTautH ) {
                goto exit_error_alloc;
            }
