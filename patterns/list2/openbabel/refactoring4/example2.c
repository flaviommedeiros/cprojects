#if ( ADD_6MEMB_AROM_BOND_PARITY == 1 )
if ( (bond_type &= ~BOND_MARK_ALL) == BOND_ALTERN )
#else
    /*  accept only aromatic bonds in non-6-member rings */
    if ( (bond_type &= ~BOND_MARK_ALL) == BOND_ALTERN )
