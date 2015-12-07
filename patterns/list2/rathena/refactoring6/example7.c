if (sc->data[SC_DANCING] ||
#ifdef RENEWAL
		sc->data[SC_MAXIMIZEPOWER] ||
#endif
#ifndef RENEWAL
		(bl->type == BL_PC && (((TBL_PC*)bl)->class_&MAPID_UPPERMASK) == MAPID_MONK &&
		(sc->data[SC_EXTREMITYFIST] || sc->data[SC_EXPLOSIONSPIRITS]) && (!sc->data[SC_SPIRIT] || sc->data[SC_SPIRIT]->val2 != SL_MONK)) ||
#else
		(bl->type == BL_PC && (((TBL_PC*)bl)->class_&MAPID_UPPERMASK) == MAPID_MONK &&
		sc->data[SC_EXTREMITYFIST] && (!sc->data[SC_SPIRIT] || sc->data[SC_SPIRIT]->val2 != SL_MONK)) ||
#endif
		sc->data[SC_OBLIVIONCURSE] || sc->data[SC_VITALITYACTIVATION])
		regen->flag &= ~RGN_SP;
