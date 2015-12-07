if ( (0 == at[n1].charge
#if ( S_VI_O_PLUS_METAL_FIX_BOND == 1 )
                          || 1 == at[n1].charge && 2 == at[n1].valence
#endif
                          )                        
                         && 0 == at[n1].radical &&
                         0 == num_of_H( at, n1 ) &&
                         NULL != memchr( en+ELEM_O_FST, at[n1].el_number, ELEM_O_LEN) &&
                         1 == nNoMetalNumBonds( at, n1 ) ) {

                        num_O ++;
                    }
