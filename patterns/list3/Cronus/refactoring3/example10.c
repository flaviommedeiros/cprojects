switch(skill_id) {
		case MG_FIREWALL:
			if ( tstatus->def_ele == ELE_FIRE || battle->check_undead(tstatus->race, tstatus->def_ele) )
				ad.blewcount = 0; //No knockback
			break;
		case NJ_KAENSIN:
		case PR_SANCTUARY:
			ad.dmotion = 0; //No flinch animation.
			break;
		case WL_HELLINFERNO:
			if( mflag&ELE_DARK )
				s_ele = ELE_DARK;
			break;
		case KO_KAIHOU:
			if (sd && sd->charm_type != CHARM_TYPE_NONE && sd->charm_count > 0) {
				s_ele = sd->charm_type;
			}
			break;
#ifdef RENEWAL
		case CR_ACIDDEMONSTRATION:
		case ASC_BREAKER:
		case HW_MAGICCRASHER:
			flag.imdef = 2;
			break;
#endif
	}
