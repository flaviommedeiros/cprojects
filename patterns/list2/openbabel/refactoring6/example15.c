if ( (nType & (type=GetAtomChargeType( at, c_point, NULL, &mask, 0 ))) && (mask & nMask)
#if ( OPPOSITE_CHARGE_IN_CGROUP == 0 )
             && ( at[c_point].charge == nCharge || !at[c_point].charge)
#endif
        );
        else
            continue;
