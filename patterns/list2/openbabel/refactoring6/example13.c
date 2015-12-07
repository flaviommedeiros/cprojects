if ( (nType & GetAtomChargeType( at, endpoint, NULL, &mask, 0 )) && (mask & nMask)
#if ( OPPOSITE_CHARGE_IN_CGROUP == 0 )
         && ( at[endpoint].charge == nCharge || !at[endpoint].charge )
#endif
    ) {
        return 1;
    }
