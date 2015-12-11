#ifdef MISSIONPACK
if( bg_itemlist[ps->stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		}
		else
#endif
		if ( item->quantity == 5 || item->quantity == 100 ) {
			if ( ps->stats[STAT_HEALTH] >= ps->stats[STAT_MAX_HEALTH] * 2 ) {
				return qfalse;
			}
			return qtrue;
		}
