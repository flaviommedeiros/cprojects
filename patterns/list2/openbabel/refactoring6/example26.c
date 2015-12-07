if ( at[i2].nRingSystem != at[i1].nRingSystem ||
                         !bIsCenterPointStrict( at, i2 ) ||
#if ( TAUT_RINGS_ATTACH_CHAIN == 1 )        
                         !at[i2].bCutVertex ||
#endif                         
                         at[i2].valence != 3 || at[i2].endpoint )
                        continue;
