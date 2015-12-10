switch( skill_id )
	{
#ifdef RENEWAL
	case HT_LANDMINE:
	case MA_LANDMINE:
	case HT_BLASTMINE:
	case HT_CLAYMORETRAP:
		md.damage = skill_lv * sstatus->dex * (3+status->get_lv(src)/100) * (1+sstatus->int_/35);
		md.damage += md.damage * (rnd()%20-10) / 100;
		md.damage += 40 * (sd?pc->checkskill(sd,RA_RESEARCHTRAP):0);
		break;
#else
	case HT_LANDMINE:
	case MA_LANDMINE:
		md.damage=skill_lv*(sstatus->dex+75)*(100+sstatus->int_)/100;
		break;
	case HT_BLASTMINE:
		md.damage=skill_lv*(sstatus->dex/2+50)*(100+sstatus->int_)/100;
		break;
	case HT_CLAYMORETRAP:
		md.damage=skill_lv*(sstatus->dex/2+75)*(100+sstatus->int_)/100;
		break;
#endif
	case HT_BLITZBEAT:
	case SN_FALCONASSAULT:
		//Blitz-beat Damage.
		if(!sd || (temp = pc->checkskill(sd,HT_STEELCROW)) <= 0)
			temp=0;
		md.damage=(sstatus->dex/10+sstatus->int_/2+temp*3+40)*2;
		if(mflag > 1) //Autocasted Blitz.
			nk|=NK_SPLASHSPLIT;

		if (skill_id == SN_FALCONASSAULT) {
			//Div fix of Blitzbeat
			temp = skill->get_num(HT_BLITZBEAT, 5);
			damage_div_fix(md.damage, temp);

			//Falcon Assault Modifier
			md.damage=md.damage*(150+70*skill_lv)/100;
		}
		break;
	case TF_THROWSTONE:
		md.damage=50;
		break;
	case BA_DISSONANCE:
		md.damage=30+skill_lv*10;
		if (sd)
			md.damage+= 3*pc->checkskill(sd,BA_MUSICALLESSON);
		break;
	case NPC_SELFDESTRUCTION:
		md.damage = sstatus->hp;
		break;
	case NPC_SMOKING:
		md.damage=3;
		break;
	case NPC_DARKBREATH:
		md.damage = 500 + (skill_lv-1)*1000 + rnd()%1000;
		if(md.damage > 9999) md.damage = 9999;
		break;
	case PA_PRESSURE:
		md.damage=500+300*skill_lv;
		break;
	case PA_GOSPEL:
		md.damage = 1+rnd()%9999;
		break;
	case CR_ACIDDEMONSTRATION:
#ifdef RENEWAL
		{// [malufett]
			int64 matk=0, atk;
			short tdef = status->get_total_def(target);
			short tmdef =  status->get_total_mdef(target);
			int targetVit = min(120, status_get_vit(target));
			short totaldef = (tmdef + tdef - ((uint64)(tmdef + tdef) >> 32)) >> 1; // FIXME: What's the >> 32 supposed to do here? tmdef and tdef are both 16-bit...

			matk = battle->calc_magic_attack(src, target, skill_id, skill_lv, mflag).damage;
			atk = battle->calc_base_damage(src, target, skill_id, skill_lv, nk, false, s_ele, ELE_NEUTRAL, EQI_HAND_R, (sc && sc->data[SC_MAXIMIZEPOWER]?1:0)|(sc && sc->data[SC_WEAPONPERFECT]?8:0), md.flag);
			md.damage = matk + atk;
			if( src->type == BL_MOB ){
				totaldef = (tdef + tmdef) >> 1;
				md.damage = 7 * targetVit * skill_lv * (atk + matk) / 100;
				/*
				// Pending [malufett]
				if( unknown condition ){
					md.damage = 7 * md.damage % 20;
					md.damage = 7 * md.damage / 20;
				}*/
			}else{
				float vitfactor = 0.0f, ftemp;

				if( (vitfactor=(status_get_vit(target)-120.0f)) > 0)
					vitfactor = (vitfactor * (matk + atk) / 10) / status_get_vit(target);
				ftemp = max(0, vitfactor) + (targetVit * (matk + atk)) / 10;
				md.damage = (int64)(ftemp * 70 * skill_lv / 100);
				if (target->type == BL_PC)
					md.damage >>= 1;
			}
			md.damage -= totaldef;
			if( tsc && tsc->data[SC_LEXAETERNA] ) {
				md.damage <<= 1;
				status_change_end(target, SC_LEXAETERNA, INVALID_TIMER);
			}
		}
#else
		// updated the formula based on a Japanese formula found to be exact [Reddozen]
		if(tstatus->vit+sstatus->int_) //crash fix
			md.damage = (int)(7*tstatus->vit*sstatus->int_*sstatus->int_ / (10*(tstatus->vit+sstatus->int_)));
		else
			md.damage = 0;
		if (tsd) md.damage>>=1;
#endif
		// Some monsters have totaldef higher than md.damage in some cases, leading to md.damage < 0
		if( md.damage < 0 )
			md.damage = 0;
		if( md.damage > INT_MAX>>1 )
			//Overflow prevention, will anyone whine if I cap it to a few billion?
			//Not capped to INT_MAX to give some room for further damage increase.
			md.damage = INT_MAX>>1;
		break;

	case KO_MUCHANAGE:
		md.damage = skill->get_zeny(skill_id ,skill_lv);
		md.damage = md.damage * (50 + rnd()%50) / 100;
		if ( is_boss(target) || (sd && !pc->checkskill(sd,NJ_TOBIDOUGU)) )
			md.damage >>= 1;
		break;
	case NJ_ZENYNAGE:
		md.damage = skill->get_zeny(skill_id ,skill_lv);
		if (!md.damage) md.damage = 2;
		md.damage = rnd()%md.damage + md.damage;
		if (is_boss(target))
			md.damage=md.damage / 3;
		else if (tsd)
			md.damage=md.damage / 2;
		break;
	case GS_FLING:
		md.damage = sd?sd->status.job_level:status->get_lv(src);
		break;
	case HVAN_EXPLOSION: //[orn]
		md.damage = sstatus->max_hp * (50 + 50 * skill_lv) / 100;
		break ;
	case ASC_BREAKER:
		{
#ifndef RENEWAL
		md.damage = 500+rnd()%500 + 5*skill_lv * sstatus->int_;
		nk|=NK_IGNORE_FLEE|NK_NO_ELEFIX; //These two are not properties of the weapon based part.
#else
		int ratio = 300 + 50 * skill_lv;
		int64 matk = battle->calc_magic_attack(src, target, skill_id, skill_lv, mflag).damage;
		short totaldef = status->get_total_def(target) + status->get_total_mdef(target);
		int64 atk = battle->calc_base_damage(src, target, skill_id, skill_lv, nk, false, s_ele, ELE_NEUTRAL, EQI_HAND_R, (sc && sc->data[SC_MAXIMIZEPOWER] ? 1 : 0) | (sc && sc->data[SC_WEAPONPERFECT] ? 8 : 0), md.flag);
#ifdef RENEWAL_EDP
		if( sc && sc->data[SC_EDP] )
			ratio >>= 1;
#endif
		md.damage = (matk + atk) * ratio / 100;
		md.damage -= totaldef;
#endif
		}
		break;
	case HW_GRAVITATION:
		md.damage = 200+200*skill_lv;
		md.dmotion = 0; //No flinch animation.
		break;
	case NPC_EVILLAND:
		md.damage = skill->calc_heal(src,target,skill_id,skill_lv,false);
		break;
	case RK_DRAGONBREATH:
	case RK_DRAGONBREATH_WATER:
		md.damage = ((status_get_hp(src) / 50) + (status_get_max_sp(src) / 4)) * skill_lv;
		RE_LVL_MDMOD(150);
		if (sd) md.damage = md.damage * (95 + 5 * pc->checkskill(sd,RK_DRAGONTRAINING)) / 100;
		md.flag |= BF_LONG|BF_WEAPON;
		break;
	/**
	 * Ranger
	 **/
	case RA_CLUSTERBOMB:
	case RA_FIRINGTRAP:
	case RA_ICEBOUNDTRAP:
		md.damage = (int64)skill_lv * sstatus->dex + sstatus->int_ * 5 ;
		RE_LVL_TMDMOD();
		if(sd)
		{
			int researchskill_lv = pc->checkskill(sd,RA_RESEARCHTRAP);
			if(researchskill_lv)
				md.damage = md.damage * 20 * researchskill_lv / (skill_id == RA_CLUSTERBOMB?50:100);
			else
				md.damage = 0;
		}else
			md.damage = md.damage * 200 / (skill_id == RA_CLUSTERBOMB?50:100);

		break;
	case WM_SOUND_OF_DESTRUCTION:
		md.damage = 1000 * (int64)skill_lv + sstatus->int_ * (sd ? pc->checkskill(sd,WM_LESSON) : 10);
		md.damage += md.damage * 10 * battle->calc_chorusbonus(sd) / 100;
		break;
	/**
	 * Mechanic
	 **/
	case NC_SELFDESTRUCTION:
		{
#ifdef RENEWAL
			short totaldef = status->get_total_def(target);
#else
			short totaldef = tstatus->def2 + (short)status->get_def(target);
#endif
			md.damage = ( (sd?pc->checkskill(sd,NC_MAINFRAME):10) + 8 ) * ( skill_lv + 1 ) * ( status_get_sp(src) + sstatus->vit );
			RE_LVL_MDMOD(100);
			md.damage += status_get_hp(src) - totaldef;
		}
		break;
	case NC_MAGMA_ERUPTION:
		md.damage = 1200 + 400 * skill_lv;
		break;
	case GN_THORNS_TRAP:
		md.damage = 100 + 200 * skill_lv + sstatus->int_;
		break;
	case GN_HELLS_PLANT_ATK:
		md.damage = skill_lv * status->get_lv(target) * 10 + sstatus->int_ * 7 / 2 * (18 + (sd ? sd->status.job_level : 0) / 4) * (5 / (10 - (sd ? pc->checkskill(sd, AM_CANNIBALIZE) : 0)));
		md.damage = md.damage*(1000 + tstatus->mdef) / (1000 + tstatus->mdef * 10) - tstatus->mdef2;
		break;
	case KO_HAPPOKUNAI:
		{
			struct Damage wd = battle->calc_weapon_attack(src, target, 0, 1, mflag);
#ifdef RENEWAL
			short totaldef = status->get_total_def(target);
#else
			short totaldef = tstatus->def2 + (short)status->get_def(target);
#endif
			if ( sd )	wd.damage += sd->bonus.arrow_atk;
			md.damage = (int)(3 * (1 + wd.damage) * (5 + skill_lv) / 5.0f);
			md.damage -= totaldef;

		}
		break;
	default:
		battle->calc_misc_attack_unknown(src, target, &skill_id, &skill_lv, &mflag, &md);
		break;
	}
