#ifdef MISSIONPACK
if( bg_itemlist[pm->ps->stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
		addTime /= 1.5;
	}
	else
	if( bg_itemlist[pm->ps->stats[STAT_PERSISTANT_POWERUP]].giTag == PW_AMMOREGEN ) {
		addTime /= 1.3;
  }
  else
#endif
	if ( pm->ps->powerups[PW_HASTE] ) {
		addTime /= 1.3;
	}
