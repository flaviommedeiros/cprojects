if ( ((charge=2) == at[c].charge && memchr( en+FIRST_CENTER2, at[c].el_number, ne-FIRST_CENTER2) 
#ifndef FIX_P_IV_Plus_O_Minus                 
                 || (charge=1) == at[c].charge && el_number_P==at[c].el_number
#endif
                 ) &&
                 4 == at[c].valence &&
                 (0 == at[c].radical || RADICAL_SINGLET == at[c].radical ) &&
                 at[c].valence == at[c].chem_bonds_valence &&
                 !NUMH(at,c) ) 
            {
                ;  /* accept */
            } 
            else 
            {
                continue; /* ignore at[i1] */
            }
