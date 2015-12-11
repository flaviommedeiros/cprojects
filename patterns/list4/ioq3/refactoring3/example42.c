switch( g_gametype.integer ) {
	case GT_CTF:
		teamgame.redStatus = -1; // Invalid to force update
		Team_SetFlagStatus( TEAM_RED, FLAG_ATBASE );
		 teamgame.blueStatus = -1; // Invalid to force update
		Team_SetFlagStatus( TEAM_BLUE, FLAG_ATBASE );
		break;
#ifdef MISSIONPACK
	case GT_1FCTF:
		teamgame.flagStatus = -1; // Invalid to force update
		Team_SetFlagStatus( TEAM_FREE, FLAG_ATBASE );
		break;
#endif
	default:
		break;
	}
