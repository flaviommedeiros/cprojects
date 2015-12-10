switch( skill_id ){ // specific skill masteries
		case MO_INVESTIGATE:
		case MO_EXTREMITYFIST:
		case CR_GRANDCROSS:
		case NJ_ISSEN:
		case CR_ACIDDEMONSTRATION:
			return damage;
		case NJ_SYURIKEN:
			if( (skill2_lv = pc->checkskill(sd,NJ_TOBIDOUGU)) > 0
#ifndef RENEWAL
				&& weapon
#endif
				)
				damage += 3 * skill2_lv;
			break;
#ifndef RENEWAL
		case NJ_KUNAI:
			if( weapon )
				damage += 60;
			break;
#endif
		case RA_WUGDASH://(Caster Current Weight x 10 / 8)
			if( sd->weight )
				damage += sd->weight / 8;
			/* Fall through */
		case RA_WUGSTRIKE:
		case RA_WUGBITE:
			damage += 30*pc->checkskill(sd, RA_TOOTHOFWUG);
			break;
		case HT_FREEZINGTRAP:
			damage += 40 * pc->checkskill(sd, RA_RESEARCHTRAP);
			break;
		default:
			battle->calc_masteryfix_unknown(src, target, &skill_id, &skill_lv, &damage, &div, &left, &weapon);
			break;
	}
