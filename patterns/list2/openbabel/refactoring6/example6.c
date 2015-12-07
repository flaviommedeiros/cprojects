if ( 
#if ( ONE_BAD_SB_NEIGHBOR == 1 )
                 num_wrong_bonds_2 > 1 || num_wrong_bonds_2 && 2 >= at[at_2].valence ||
#else
                 j < at[at_2].valence /* "next" has a wrong bond type*/ ||
#endif
                 (num_alt_2>0) + (num_2s_2>0) != 1 || /* all double XOR all alt bonds only */
                  /* num_2s_2 > 1  ||*/ /* only one double bond permitted */
                  i_next_at_2 < 0 /* atom next to the opposite atom not found */ ) {
                bFound = 0;
            } else
            if ( at[at_2].c_point ) {
                bFound = 0; /* rejects atoms that can lose or gain a (positive) charge. 01-24-2003 */
            } else
            if ( num_2s_2 > 2 ) {
                bFound = 0;
            } else
#if ( N_V_STEREOBONDS == 1 )
            if ( 3 == (type_N | type_N_next) &&
                 ( 2 == type_N && !bIsOxide( at, at_1 ) ||
                   2 == type_N_next && !bIsOxide( at, at_2 ) ) ) {
                bFound = 0;
            } else
#endif
            if ( 2 == num_2s_2 ) {
#if ( N_V_STEREOBONDS == 1 )
                if ( !chain_length &&
                     1 == (num_2s_hetero_next[0] | num_2s_hetero_next[1]) &&
                     3 == at[at_2].valence + at[at_2].num_H &&
                     5 == at[at_2].chem_bonds_valence + at[at_2].num_H &&
                     3 == get_endpoint_valence( at[at_2].el_number ) &&
                     (!type_N || bIsOxide( at, at_2 )) ) {
                      /*
                       *   found:
                       *
                       *    \      /    \      /    \      /     
                       *     \    /      \    /      \    /      
                       *      N==C   or   N==C   or   N==N       
                       *    //    \     //    \     //    \      
                       *   O  ^    \   N  ^    \   O  ^    \     
                       *      |           |           |          
                       *      |           |           |          
                       *      at[at_2]    at[at_2]    at[at_2]
                       */
                    ;
                } else {
                    bFound = 0;
                }
#else
                bFound = 0;
#endif
            }
