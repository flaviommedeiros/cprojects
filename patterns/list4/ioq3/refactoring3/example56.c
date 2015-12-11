switch ( itemNum ) {
	default:
	case HI_NONE:
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useNothingSound );
		break;

	case HI_TELEPORTER:
		break;

	case HI_MEDKIT:
		clientNum = cent->currentState.clientNum;
		if ( clientNum >= 0 && clientNum < MAX_CLIENTS ) {
			ci = &cgs.clientinfo[ clientNum ];
			ci->medkitUsageTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.medkitSound );
		break;

#ifdef MISSIONPACK
	case HI_KAMIKAZE:
		break;

	case HI_PORTAL:
		break;
	case HI_INVULNERABILITY:
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useInvulnerabilitySound );
		break;
#endif
	}
