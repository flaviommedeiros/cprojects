switch(skill_id) {
		case 0: { // Normal attacks (no skill used)
			if( attack_type&BF_SKILL )
				break; // If a normal attack is a skill, it's splash damage. [Inkfish]
			if(sd) {
				// Automatic trigger of Blitz Beat
				if (pc_isfalcon(sd) && sd->status.weapon == W_BOW && (temp=pc->checkskill(sd,HT_BLITZBEAT))>0 &&
					rnd()%1000 <= sstatus->luk*3 ) {
					rate = sd->status.job_level / 10 + 1;
					skill->castend_damage_id(src,bl,HT_BLITZBEAT,(temp<rate)?temp:rate,tick,SD_LEVEL);
				}
				// Automatic trigger of Warg Strike [Jobbie]
				if( pc_iswug(sd) && (temp=pc->checkskill(sd,RA_WUGSTRIKE)) > 0 && rnd()%1000 <= sstatus->luk*3 )
					skill->castend_damage_id(src,bl,RA_WUGSTRIKE,temp,tick,0);
				// Gank
				if(dstmd && sd->status.weapon != W_BOW &&
					(temp=pc->checkskill(sd,RG_SNATCHER)) > 0 &&
					(temp*15 + 55) + pc->checkskill(sd,TF_STEAL)*10 > rnd()%1000) {
					if(pc->steal_item(sd,bl,pc->checkskill(sd,TF_STEAL)))
						clif->skill_nodamage(src,bl,TF_STEAL,temp,1);
					else
						clif->skill_fail(sd,RG_SNATCHER,USESKILL_FAIL_LEVEL,0);
				}
				// Chance to trigger Taekwon kicks [Dralnu]
				if(sc && !sc->data[SC_COMBOATTACK]) {
					if(sc->data[SC_STORMKICK_READY] &&
						sc_start4(src,src,SC_COMBOATTACK, 15, TK_STORMKICK,
							bl->id, 2, 0,
							(2000 - 4*sstatus->agi - 2*sstatus->dex)))
						; //Stance triggered
					else if(sc->data[SC_DOWNKICK_READY] &&
						sc_start4(src,src,SC_COMBOATTACK, 15, TK_DOWNKICK,
							bl->id, 2, 0,
							(2000 - 4*sstatus->agi - 2*sstatus->dex)))
						; //Stance triggered
					else if(sc->data[SC_TURNKICK_READY] &&
						sc_start4(src,src,SC_COMBOATTACK, 15, TK_TURNKICK,
							bl->id, 2, 0,
							(2000 - 4*sstatus->agi - 2*sstatus->dex)))
						; //Stance triggered
						else if (sc->data[SC_COUNTERKICK_READY]) { //additional chance from SG_FRIEND [Komurka]
						rate = 20;
						if (sc->data[SC_SKILLRATE_UP] && sc->data[SC_SKILLRATE_UP]->val1 == TK_COUNTER) {
							rate += rate*sc->data[SC_SKILLRATE_UP]->val2/100;
							status_change_end(src, SC_SKILLRATE_UP, INVALID_TIMER);
						}
						sc_start2(src, src, SC_COMBOATTACK, rate, TK_COUNTER, bl->id,
							(2000 - 4*sstatus->agi - 2*sstatus->dex));
					}
				}
				if(sc && sc->data[SC_PYROCLASTIC] && (rnd() % 1000 <= sstatus->luk * 10 / 3 + 1) )
					skill->castend_pos2(src, bl->x, bl->y, BS_HAMMERFALL,sc->data[SC_PYROCLASTIC]->val1, tick, 0);
			}

			if (sc) {
				struct status_change_entry *sce;
				// Enchant Poison gives a chance to poison attacked enemies
				if((sce=sc->data[SC_ENCHANTPOISON])) //Don't use sc_start since chance comes in 1/10000 rate.
					status->change_start(src,bl,SC_POISON,sce->val2, sce->val1,src->id,0,0,
						skill->get_time2(AS_ENCHANTPOISON,sce->val1),SCFLAG_NONE);
				// Enchant Deadly Poison gives a chance to deadly poison attacked enemies
				if((sce=sc->data[SC_EDP]))
					sc_start4(src,bl,SC_DPOISON,sce->val2, sce->val1,src->id,0,0,
						skill->get_time2(ASC_EDP,sce->val1));
			}
		}
			break;

		case SM_BASH:
			if( sd && skill_lv > 5 && pc->checkskill(sd,SM_FATALBLOW)>0 )
				status->change_start(src,bl,SC_STUN,500*(skill_lv-5)*sd->status.base_level/50,
					skill_lv,0,0,0,skill->get_time2(SM_FATALBLOW,skill_lv),SCFLAG_NONE);
			break;

		case MER_CRASH:
			sc_start(src,bl,SC_STUN,(6*skill_lv),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case AS_VENOMKNIFE:
			if (sd) //Poison chance must be that of Envenom. [Skotlex]
				skill_lv = pc->checkskill(sd, TF_POISON);
			/* Fall through */
		case TF_POISON:
		case AS_SPLASHER:
			if (!sc_start2(src,bl,SC_POISON,(4*skill_lv+10),skill_lv,src->id,skill->get_time2(skill_id,skill_lv))
			 && sd && skill_id==TF_POISON
			)
				clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
			break;

		case AS_SONICBLOW:
			sc_start(src,bl,SC_STUN,(2*skill_lv+10),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case WZ_FIREPILLAR:
			unit->set_walkdelay(bl, tick, skill->get_time2(skill_id, skill_lv), 1);
			break;

		case MG_FROSTDIVER:
	#ifndef RENEWAL
		case WZ_FROSTNOVA:
	#endif
			if (!sc_start(src,bl,SC_FREEZE,skill_lv*3+35,skill_lv,skill->get_time2(skill_id,skill_lv))
			 && sd && skill_id == MG_FROSTDIVER
			)
				clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
			break;

	#ifdef RENEWAL
		case WZ_FROSTNOVA:
			sc_start(src,bl,SC_FREEZE,skill_lv*5+33,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;
	#endif

		case WZ_STORMGUST:
		/**
		 * Storm Gust counter was dropped in renewal
		 **/
		#ifdef RENEWAL
			sc_start(src,bl,SC_FREEZE,65-(5*skill_lv),skill_lv,skill->get_time2(skill_id,skill_lv));
		#else
			//On third hit, there is a 150% to freeze the target
			if(tsc->sg_counter >= 3 &&
				sc_start(src,bl,SC_FREEZE,150,skill_lv,skill->get_time2(skill_id,skill_lv)))
				tsc->sg_counter = 0;
			/**
			 * being it only resets on success it'd keep stacking and eventually overflowing on mvps, so we reset at a high value
			 **/
			else if( tsc->sg_counter > 250 )
				tsc->sg_counter = 0;
		#endif
			break;

		case WZ_METEOR:
			sc_start(src,bl,SC_STUN,3*skill_lv,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case WZ_VERMILION:
			sc_start(src,bl,SC_BLIND,4*skill_lv,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case HT_FREEZINGTRAP:
		case MA_FREEZINGTRAP:
			sc_start(src,bl,SC_FREEZE,(3*skill_lv+35),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case HT_FLASHER:
			sc_start(src,bl,SC_BLIND,(10*skill_lv+30),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case HT_LANDMINE:
		case MA_LANDMINE:
			sc_start(src,bl,SC_STUN,(5*skill_lv+30),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case HT_SHOCKWAVE:
			status_percent_damage(src, bl, 0, 15*skill_lv+5, false);
			break;

		case HT_SANDMAN:
		case MA_SANDMAN:
			sc_start(src,bl,SC_SLEEP,(10*skill_lv+40),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case TF_SPRINKLESAND:
			sc_start(src,bl,SC_BLIND,20,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case TF_THROWSTONE:
			if( !sc_start(src,bl,SC_STUN,3,skill_lv,skill->get_time(skill_id,skill_lv)) )
				sc_start(src,bl,SC_BLIND,3,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case NPC_DARKCROSS:
		case CR_HOLYCROSS:
			sc_start(src,bl,SC_BLIND,3*skill_lv,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case CR_GRANDCROSS:
		case NPC_GRANDDARKNESS:
			//Chance to cause blind status vs demon and undead element, but not against players
			if(!dstsd && (battle->check_undead(tstatus->race,tstatus->def_ele) || tstatus->race == RC_DEMON))
				sc_start(src,bl,SC_BLIND,100,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case AM_ACIDTERROR:
			sc_start2(src, bl, SC_BLOODING, (skill_lv * 3), skill_lv, src->id, skill->get_time2(skill_id, skill_lv));
			if ( bl->type == BL_PC && rnd() % 1000 < 10 * skill->get_time(skill_id, skill_lv) ) {
				skill->break_equip(bl, EQP_ARMOR, 10000, BCT_ENEMY);
				clif->emotion(bl, E_OMG); // emote icon still shows even there is no armor equip.
			}
			break;

		case AM_DEMONSTRATION:
			skill->break_equip(bl, EQP_WEAPON, 100*skill_lv, BCT_ENEMY);
			break;

		case CR_SHIELDCHARGE:
			sc_start(src,bl,SC_STUN,(15+skill_lv*5),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case PA_PRESSURE:
			status_percent_damage(src, bl, 0, 15+5*skill_lv, false);
			break;

		case RG_RAID:
			sc_start(src,bl,SC_STUN,(10+3*skill_lv),skill_lv,skill->get_time(skill_id,skill_lv));
			sc_start(src,bl,SC_BLIND,(10+3*skill_lv),skill_lv,skill->get_time2(skill_id,skill_lv));

	#ifdef RENEWAL
			sc_start(src,bl,SC_RAID,100,7,5000);
			break;

		case RG_BACKSTAP:
			sc_start(src,bl,SC_STUN,(5+2*skill_lv),skill_lv,skill->get_time(skill_id,skill_lv));
	#endif
			break;

		case BA_FROSTJOKER:
			sc_start(src,bl,SC_FREEZE,(15+5*skill_lv),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case DC_SCREAM:
			sc_start(src,bl,SC_STUN,(25+5*skill_lv),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case BD_LULLABY:
			sc_start(src,bl,SC_SLEEP,15,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case DC_UGLYDANCE:
			rate = 5+5*skill_lv;
			if (sd && (temp=pc->checkskill(sd,DC_DANCINGLESSON)) > 0)
				rate += 5+temp;
			status_zap(bl, 0, rate);
			break;
		case SL_STUN:
			if (tstatus->size==SZ_MEDIUM) //Only stuns mid-sized mobs.
				sc_start(src,bl,SC_STUN,(30+10*skill_lv),skill_lv,skill->get_time(skill_id,skill_lv));
			break;

		case NPC_PETRIFYATTACK:
			sc_start4(src,bl,status->skill2sc(skill_id),50+10*skill_lv,
				skill_lv,0,0,skill->get_time(skill_id,skill_lv),
				skill->get_time2(skill_id,skill_lv));
			break;
		case NPC_CURSEATTACK:
		case NPC_SLEEPATTACK:
		case NPC_BLINDATTACK:
		case NPC_POISON:
		case NPC_SILENCEATTACK:
		case NPC_STUNATTACK:
		case NPC_HELLPOWER:
			sc_start(src,bl,status->skill2sc(skill_id),50+10*skill_lv,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;
		case NPC_ACIDBREATH:
		case NPC_ICEBREATH:
			sc_start(src,bl,status->skill2sc(skill_id),70,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;
		case NPC_BLEEDING:
			sc_start2(src,bl,SC_BLOODING,(20*skill_lv),skill_lv,src->id,skill->get_time2(skill_id,skill_lv));
			break;
		case NPC_MENTALBREAKER:
		{
			//Based on observations by [Tharis], Mental Breaker should do SP damage
			//equal to Matk*skLevel.
			rate = status->get_matk(src, 2);
			rate*=skill_lv;
			status_zap(bl, 0, rate);
			break;
		}
		// Equipment breaking monster skills [Celest]
		case NPC_WEAPONBRAKER:
			skill->break_equip(bl, EQP_WEAPON, 150*skill_lv, BCT_ENEMY);
			break;
		case NPC_ARMORBRAKE:
			skill->break_equip(bl, EQP_ARMOR, 150*skill_lv, BCT_ENEMY);
			break;
		case NPC_HELMBRAKE:
			skill->break_equip(bl, EQP_HELM, 150*skill_lv, BCT_ENEMY);
			break;
		case NPC_SHIELDBRAKE:
			skill->break_equip(bl, EQP_SHIELD, 150*skill_lv, BCT_ENEMY);
			break;

		case CH_TIGERFIST:
			sc_start(src,bl,SC_STOP,(10+skill_lv*10),0,skill->get_time2(skill_id,skill_lv));
			break;

		case LK_SPIRALPIERCE:
		case ML_SPIRALPIERCE:
			if( dstsd || ( dstmd && !is_boss(bl) ) ) //Does not work on bosses
				sc_start(src,bl,SC_STOP,100,0,skill->get_time2(skill_id,skill_lv));
			break;

		case ST_REJECTSWORD:
			sc_start(src,bl,SC_AUTOCOUNTER,(skill_lv*15),skill_lv,skill->get_time(skill_id,skill_lv));
			break;

		case PF_FOGWALL:
			if (src != bl && !tsc->data[SC_DELUGE])
				sc_start(src,bl,SC_BLIND,100,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case LK_HEADCRUSH: // Headcrush has chance of causing Bleeding status, except on demon and undead element
			if (!(battle->check_undead(tstatus->race, tstatus->def_ele) || tstatus->race == RC_DEMON))
				sc_start2(src, bl, SC_BLOODING,50, skill_lv, src->id, skill->get_time2(skill_id,skill_lv));
			break;

		case LK_JOINTBEAT:
			if (tsc->jb_flag) {
				enum sc_type type = status->skill2sc(skill_id);
				sc_start4(src,bl,type,(5*skill_lv+5),skill_lv,tsc->jb_flag&BREAK_FLAGS,src->id,0,skill->get_time2(skill_id,skill_lv));
				tsc->jb_flag = 0;
			}
			break;
		case ASC_METEORASSAULT:
			//Any enemies hit by this skill will receive Stun, Darkness, or external bleeding status ailment with a 5%+5*skill_lv% chance.
			switch(rnd()%3) {
				case 0:
					sc_start(src,bl,SC_BLIND,(5+skill_lv*5),skill_lv,skill->get_time2(skill_id,1));
					break;
				case 1:
					sc_start(src,bl,SC_STUN,(5+skill_lv*5),skill_lv,skill->get_time2(skill_id,2));
					break;
				default:
					sc_start2(src,bl,SC_BLOODING,(5+skill_lv*5),skill_lv,src->id,skill->get_time2(skill_id,3));
			}
			break;

		case HW_NAPALMVULCAN:
			sc_start(src,bl,SC_CURSE,5*skill_lv,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case WS_CARTTERMINATION:
			sc_start(src,bl,SC_STUN,5*skill_lv,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case CR_ACIDDEMONSTRATION:
			skill->break_equip(bl, EQP_WEAPON|EQP_ARMOR, 100*skill_lv, BCT_ENEMY);
			break;

		case TK_DOWNKICK:
			sc_start(src,bl,SC_STUN,100,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case TK_JUMPKICK:
			if( dstsd && dstsd->class_ != MAPID_SOUL_LINKER && !tsc->data[SC_PRESERVE] )
			{// debuff the following statuses
				status_change_end(bl, SC_SOULLINK, INVALID_TIMER);
				status_change_end(bl, SC_ADRENALINE2, INVALID_TIMER);
				status_change_end(bl, SC_KAITE, INVALID_TIMER);
				status_change_end(bl, SC_KAAHI, INVALID_TIMER);
				status_change_end(bl, SC_ONEHANDQUICKEN, INVALID_TIMER);
				status_change_end(bl, SC_ATTHASTE_POTION3, INVALID_TIMER);
			}
			break;
		case TK_TURNKICK:
		case MO_BALKYOUNG: //Note: attack_type is passed as BF_WEAPON for the actual target, BF_MISC for the splash-affected mobs.
			if(attack_type&BF_MISC) //70% base stun chance...
				sc_start(src,bl,SC_STUN,70,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;
		case GS_BULLSEYE: //0.1% coma rate.
			if(tstatus->race == RC_BRUTE || tstatus->race == RC_DEMIHUMAN)
				status->change_start(src,bl,SC_COMA,10,skill_lv,0,src->id,0,0,SCFLAG_NONE);
			break;
		case GS_PIERCINGSHOT:
			sc_start2(src,bl,SC_BLOODING,(skill_lv*3),skill_lv,src->id,skill->get_time2(skill_id,skill_lv));
			break;
		case NJ_HYOUSYOURAKU:
			sc_start(src,bl,SC_FREEZE,(10+10*skill_lv),skill_lv,skill->get_time2(skill_id,skill_lv));
			break;
		case GS_FLING:
			sc_start(src,bl,SC_FLING,100, sd?sd->spiritball_old:5,skill->get_time(skill_id,skill_lv));
			break;
		case GS_DISARM:
			rate = 3*skill_lv;
			if (sstatus->dex > tstatus->dex)
				rate += (sstatus->dex - tstatus->dex)/5; //TODO: Made up formula
			skill->strip_equip(bl, EQP_WEAPON, rate, skill_lv, skill->get_time(skill_id,skill_lv));
			clif->skill_nodamage(src,bl,skill_id,skill_lv,1);
			break;
		case NPC_EVILLAND:
			sc_start(src,bl,SC_BLIND,5*skill_lv,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;
		case NPC_HELLJUDGEMENT:
			sc_start(src,bl,SC_CURSE,100,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;
		case NPC_CRITICALWOUND:
			sc_start(src,bl,SC_CRITICALWOUND,100,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;
		case RK_WINDCUTTER:
			sc_start(src,bl,SC_FEAR,3+2*skill_lv,skill_lv,skill->get_time(skill_id,skill_lv));
			break;
		case RK_DRAGONBREATH:
			sc_start4(src,bl,SC_BURNING,15,skill_lv,1000,src->id,0,skill->get_time(skill_id,skill_lv));
			break;
		case RK_DRAGONBREATH_WATER:
			sc_start4(src,bl,SC_FROSTMISTY,15,skill_lv,1000,src->id,0,skill->get_time(skill_id,skill_lv));
			break;
		case AB_ADORAMUS:
			if( tsc && !tsc->data[SC_DEC_AGI] ) //Prevent duplicate agi-down effect.
				sc_start(src, bl, SC_ADORAMUS, skill_lv * 4 + (sd? sd->status.job_level:50)/2, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case WL_CRIMSONROCK:
			sc_start(src, bl, SC_STUN, 40, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case WL_COMET:
			sc_start4(src,bl,SC_BURNING,100,skill_lv,0,src->id,0,skill->get_time2(skill_id,skill_lv));
			break;
		case WL_EARTHSTRAIN:
			{
				int i;
				const int pos[5] = { EQP_WEAPON, EQP_HELM, EQP_SHIELD, EQP_ARMOR, EQP_ACC };

				for( i = 0; i < skill_lv; i++ )
					skill->strip_equip(bl,pos[i], (5 + skill_lv) * skill_lv,
						skill_lv,skill->get_time2(skill_id,skill_lv));
			}
			break;
		case WL_JACKFROST:
			sc_start(src,bl,SC_FREEZE,100,skill_lv,skill->get_time(skill_id,skill_lv));
			break;
		case WL_FROSTMISTY:
			sc_start(src,bl,SC_FROSTMISTY,25 + 5 * skill_lv,skill_lv,skill->get_time(skill_id,skill_lv));
			break;
		case RA_WUGBITE:
			rate = 50 + 10 * skill_lv + 2 * (sd ? pc->checkskill(sd,RA_TOOTHOFWUG) : 0) - tstatus->agi / 4;
			if ( rate < 50 )
				rate = 50;
			sc_start(src,bl,SC_WUGBITE, rate, skill_lv, skill->get_time(skill_id, skill_lv) + (sd ? pc->checkskill(sd,RA_TOOTHOFWUG) * 500 : 0));
			break;
		case RA_SENSITIVEKEEN:
			if( rnd()%100 < 8 * skill_lv )
				skill->castend_damage_id(src, bl, RA_WUGBITE, sd ? pc->checkskill(sd, RA_WUGBITE):skill_lv, tick, SD_ANIMATION);
			break;
		case RA_MAGENTATRAP:
		case RA_COBALTTRAP:
		case RA_MAIZETRAP:
		case RA_VERDURETRAP:
			if( dstmd && !(dstmd->status.mode&MD_BOSS) )
				sc_start2(src,bl,SC_ARMOR_PROPERTY,100,skill_lv,skill->get_ele(skill_id,skill_lv),skill->get_time2(skill_id,skill_lv));
			break;
		case RA_FIRINGTRAP:
		case RA_ICEBOUNDTRAP:
			sc_start4(src, bl, (skill_id == RA_FIRINGTRAP) ? SC_BURNING:SC_FROSTMISTY, 50 + 10 * skill_lv, skill_lv, 0, src->id, 0, skill->get_time2(skill_id, skill_lv));
			break;
		case NC_PILEBUNKER:
			if( rnd()%100 < 25 + 15 *skill_lv ) {
				//Deactivatable Statuses: Kyrie Eleison, Auto Guard, Steel Body, Assumptio, and Millennium Shield
				status_change_end(bl, SC_KYRIE, INVALID_TIMER);
				status_change_end(bl, SC_ASSUMPTIO, INVALID_TIMER);
				status_change_end(bl, SC_STEELBODY, INVALID_TIMER);
				status_change_end(bl, SC_GENTLETOUCH_CHANGE, INVALID_TIMER);
				status_change_end(bl, SC_GENTLETOUCH_REVITALIZE, INVALID_TIMER);
				status_change_end(bl, SC_AUTOGUARD, INVALID_TIMER);
				status_change_end(bl, SC_REFLECTSHIELD, INVALID_TIMER);
				status_change_end(bl, SC_DEFENDER, INVALID_TIMER);
				status_change_end(bl, SC_LG_REFLECTDAMAGE, INVALID_TIMER);
				status_change_end(bl, SC_PRESTIGE, INVALID_TIMER);
				status_change_end(bl, SC_BANDING, INVALID_TIMER);
				status_change_end(bl, SC_MILLENNIUMSHIELD, INVALID_TIMER);
			}
			break;
		case NC_FLAMELAUNCHER:
			sc_start4(src, bl, SC_BURNING, 20 + 10 * skill_lv, skill_lv, 0, src->id, 0, skill->get_time2(skill_id, skill_lv));
			break;
		case NC_COLDSLOWER:
			sc_start(src, bl, SC_FREEZE, 10 * skill_lv, skill_lv, skill->get_time(skill_id, skill_lv));
			if ( tsc && !tsc->data[SC_FREEZE] )
				sc_start(src, bl, SC_FROSTMISTY, 20 + 10 * skill_lv, skill_lv, skill->get_time2(skill_id, skill_lv));
			break;
		case NC_POWERSWING:
			// Use flag=2, the stun duration is not vit-reduced.
			status->change_start(src, bl, SC_STUN, 5*skill_lv*100, skill_lv, 0, 0, 0, skill->get_time(skill_id, skill_lv), SCFLAG_FIXEDTICK);
			if( rnd()%100 < 5*skill_lv )
				skill->castend_damage_id(src, bl, NC_AXEBOOMERANG, pc->checkskill(sd, NC_AXEBOOMERANG), tick, 1);
			break;
		case NC_MAGMA_ERUPTION:
			sc_start4(src, bl, SC_BURNING, 10 * skill_lv, skill_lv, 0, src->id, 0, skill->get_time2(skill_id, skill_lv));
			sc_start(src, bl, SC_STUN, 10 * skill_lv, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case GC_WEAPONCRUSH:
			skill->castend_nodamage_id(src,bl,skill_id,skill_lv,tick,BCT_ENEMY);
			break;
		case GC_DARKCROW:
			sc_start(src, bl, SC_DARKCROW, 100, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case LG_SHIELDPRESS:
			rate = 30 + 8 * skill_lv + sstatus->dex / 10 + (sd? sd->status.job_level:0) / 4;
			sc_start(src, bl, SC_STUN, rate, skill_lv, skill->get_time(skill_id,skill_lv));
			break;
		case LG_HESPERUSLIT:
			if ( sc && sc->data[SC_BANDING] ) {
				if ( sc->data[SC_BANDING]->val2 == 4 ) // 4 banding RGs: Targets will be stunned at 100% chance for 4 ~ 8 seconds, irreducible by STAT.
					status->change_start(src, bl, SC_STUN, 10000, skill_lv, 0, 0, 0, 1000*(4+rnd()%4), SCFLAG_FIXEDTICK);
				else if ( sc->data[SC_BANDING]->val2 == 6 ) // 6 banding RGs: activate Pinpoint Attack Lv1-5
					skill->castend_damage_id(src,bl,LG_PINPOINTATTACK,1+rnd()%5,tick,0);
			}
			break;
		case LG_PINPOINTATTACK:
			rate = 30 + 5 * (sd ? pc->checkskill(sd,LG_PINPOINTATTACK) : 1) + (sstatus->agi + status->get_lv(src)) / 10;
			switch( skill_lv ) {
				case 1:
					sc_start(src, bl,SC_BLOODING,rate,skill_lv,skill->get_time(skill_id,skill_lv));
					break;
				case 2:
					skill->break_equip(bl, EQP_HELM, rate*100, BCT_ENEMY);
					break;
				case 3:
					skill->break_equip(bl, EQP_SHIELD, rate*100, BCT_ENEMY);
					break;
				case 4:
					skill->break_equip(bl, EQP_ARMOR, rate*100, BCT_ENEMY);
					break;
				case 5:
					skill->break_equip(bl, EQP_WEAPON, rate*100, BCT_ENEMY);
					break;
			}
			break;
		case LG_MOONSLASHER:
			rate = 32 + 8 * skill_lv;
			if( rnd()%100 < rate && dstsd ) // Uses skill->addtimerskill to avoid damage and setsit packet overlaping. Officially clif->setsit is received about 500 ms after damage packet.
				skill->addtimerskill(src,tick+500,bl->id,0,0,skill_id,skill_lv,BF_WEAPON,0);
			else if( dstmd && !is_boss(bl) )
				sc_start(src, bl,SC_STOP,100,skill_lv,skill->get_time(skill_id,skill_lv));
			break;
		case LG_RAYOFGENESIS: // 50% chance to cause Blind on Undead and Demon monsters.
			if ( battle->check_undead(tstatus->race, tstatus->def_ele) || tstatus->race == RC_DEMON )
				sc_start(src, bl, SC_BLIND,50, skill_lv, skill->get_time(skill_id,skill_lv));
			break;
		case LG_EARTHDRIVE:
			skill->break_equip(src, EQP_SHIELD, 100 * skill_lv, BCT_SELF);
			sc_start(src, bl, SC_EARTHDRIVE, 100, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case SR_DRAGONCOMBO:
			sc_start(src, bl, SC_STUN, 1 + skill_lv, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case SR_FALLENEMPIRE:
			sc_start(src, bl, SC_FALLENEMPIRE, 100, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case SR_WINDMILL:
			if( dstsd )
				skill->addtimerskill(src,tick+status_get_amotion(src),bl->id,0,0,skill_id,skill_lv,BF_WEAPON,0);
			else if( dstmd && !is_boss(bl) )
				sc_start(src, bl, SC_STUN, 100, skill_lv, 1000 + 1000 * (rnd() %3));
			break;
		case SR_GENTLETOUCH_QUIET:  //  [(Skill Level x 5) + (Caster?s DEX + Caster?s Base Level) / 10]
			sc_start(src, bl, SC_SILENCE, 5 * skill_lv + (sstatus->dex + status->get_lv(src)) / 10, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case SR_EARTHSHAKER:
			sc_start(src, bl,SC_STUN, 25 + 5 * skill_lv,skill_lv,skill->get_time(skill_id,skill_lv));
			break;
		case SR_HOWLINGOFLION:
			sc_start(src, bl, SC_FEAR, 5 + 5 * skill_lv, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case SO_EARTHGRAVE:
			sc_start2(src, bl, SC_BLOODING, 5 * skill_lv, skill_lv, src->id, skill->get_time2(skill_id, skill_lv)); // Need official rate. [LimitLine]
			break;
		case SO_DIAMONDDUST:
			rate = 5 + 5 * skill_lv;
			if( sc && sc->data[SC_COOLER_OPTION] )
				rate += sc->data[SC_COOLER_OPTION]->val3 / 5;
			sc_start(src, bl, SC_COLD, rate, skill_lv, skill->get_time2(skill_id, skill_lv));
			break;
		case SO_VARETYR_SPEAR:
			sc_start(src, bl, SC_STUN, 5 + 5 * skill_lv, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case GN_SLINGITEM_RANGEMELEEATK:
			if( sd ) {
				switch( sd->itemid ) {
					// Starting SCs here instead of do it in skill->additional_effect to simplify the code.
					case ITEMID_COCONUT_BOMB:
						sc_start(src, bl, SC_STUN, 100, skill_lv, 5000); // 5 seconds until I get official
						sc_start(src, bl, SC_BLOODING, 100, skill_lv, 10000);
						break;
					case ITEMID_MELON_BOMB:
						sc_start(src, bl, SC_MELON_BOMB, 100, skill_lv, 60000); // Reduces ASPD and movement speed
						break;
					case ITEMID_BANANA_BOMB:
						sc_start(src, bl, SC_BANANA_BOMB, 100, skill_lv, 60000); // Reduces LUK? Needed confirm it, may be it's bugged in kRORE?
						sc_start(src, bl, SC_BANANA_BOMB_SITDOWN_POSTDELAY, (sd? sd->status.job_level:0) + sstatus->dex / 6 + tstatus->agi / 4 - tstatus->luk / 5 - status->get_lv(bl) + status->get_lv(src), skill_lv, 1000); // Sit down for 3 seconds.
						break;
				}
				sd->itemid = -1;
			}
			break;
		case GN_HELLS_PLANT_ATK:
			sc_start(src, bl, SC_STUN,  20 + 10 * skill_lv, skill_lv, skill->get_time2(skill_id, skill_lv));
			sc_start2(src, bl, SC_BLOODING, 5 + 5 * skill_lv, skill_lv, src->id,skill->get_time2(skill_id, skill_lv));
			break;
		case EL_WIND_SLASH: // Non confirmed rate.
			sc_start2(src, bl, SC_BLOODING, 25, skill_lv, src->id, skill->get_time(skill_id,skill_lv));
			break;
		case EL_STONE_HAMMER:
			rate = 10 * skill_lv;
			sc_start(src, bl, SC_STUN, rate, skill_lv, skill->get_time(skill_id,skill_lv));
			break;
		case EL_ROCK_CRUSHER:
		case EL_ROCK_CRUSHER_ATK:
			sc_start(src, bl,status->skill2sc(skill_id),50,skill_lv,skill->get_time(EL_ROCK_CRUSHER,skill_lv));
			break;
		case EL_TYPOON_MIS:
			sc_start(src, bl,SC_SILENCE,10*skill_lv,skill_lv,skill->get_time(skill_id,skill_lv));
			break;
		case KO_JYUMONJIKIRI:
			sc_start(src, bl,SC_KO_JYUMONJIKIRI,90,skill_lv,skill->get_time(skill_id,skill_lv));
			break;
		case KO_MAKIBISHI:
			sc_start(src, bl, SC_STUN, 10 * skill_lv, skill_lv, 1000 * (skill_lv / 2 + 2));
			break;
		case MH_LAVA_SLIDE:
			if (tsc && !tsc->data[SC_BURNING]) sc_start4(src, bl, SC_BURNING, 10 * skill_lv, skill_lv, 0, src->id, 0, skill->get_time(skill_id, skill_lv));
			break;
		case MH_STAHL_HORN:
			sc_start(src, bl, SC_STUN, (20 + 4 * (skill_lv-1)), skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case MH_NEEDLE_OF_PARALYZE:
			sc_start(src, bl, SC_NEEDLE_OF_PARALYZE, 40 + (5*skill_lv), skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case GN_ILLUSIONDOPING:
			if( sc_start(src, bl, SC_ILLUSIONDOPING, 10 * skill_lv, skill_lv, skill->get_time(skill_id, skill_lv)) ) //custom rate.
				sc_start(src, bl, SC_ILLUSION, 100, skill_lv, skill->get_time(skill_id, skill_lv));
			break;
		case MH_XENO_SLASHER:
			sc_start2(src, bl, SC_BLOODING, 10 * skill_lv, skill_lv, src->id, skill->get_time(skill_id,skill_lv));
			break;
		default:
			skill->additional_effect_unknown(src, bl, &skill_id, &skill_lv, &attack_type, &dmg_lv, &tick);
			break;
	}
