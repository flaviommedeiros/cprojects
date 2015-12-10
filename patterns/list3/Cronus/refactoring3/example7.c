switch( skill_id )
			{
				case SM_BASH:
				case MS_BASH:
					skillratio += 30 * skill_lv;
					break;
				case SM_MAGNUM:
				case MS_MAGNUM:
					skillratio += 20 * skill_lv;
					break;
				case MC_MAMMONITE:
					skillratio += 50 * skill_lv;
					break;
				case HT_POWER:
					skillratio += -50 + 8 * status_get_str(src);
					break;
				case AC_DOUBLE:
				case MA_DOUBLE:
					skillratio += 10 * (skill_lv-1);
					break;
				case AC_SHOWER:
				case MA_SHOWER:
					#ifdef RENEWAL
						skillratio += 50 + 10 * skill_lv;
					#else
						skillratio += -25 + 5 * skill_lv;
					#endif
					break;
				case AC_CHARGEARROW:
				case MA_CHARGEARROW:
					skillratio += 50;
					break;
	#ifndef RENEWAL
				case HT_FREEZINGTRAP:
				case MA_FREEZINGTRAP:
					skillratio += -50 + 10 * skill_lv;
					break;
	#endif
				case KN_PIERCE:
				case ML_PIERCE:
					skillratio += 10 * skill_lv;
					break;
				case MER_CRASH:
					skillratio += 10 * skill_lv;
					break;
				case KN_SPEARSTAB:
					skillratio += 15 * skill_lv;
					break;
				case KN_SPEARBOOMERANG:
					skillratio += 50*skill_lv;
					break;
				case KN_BRANDISHSPEAR:
				case ML_BRANDISH:
				{
					int ratio = 100 + 20 * skill_lv;
					skillratio += ratio - 100;
					if(skill_lv>3 && flag==1) skillratio += ratio / 2;
					if(skill_lv>6 && flag==1) skillratio += ratio / 4;
					if(skill_lv>9 && flag==1) skillratio += ratio / 8;
					if(skill_lv>6 && flag==2) skillratio += ratio / 2;
					if(skill_lv>9 && flag==2) skillratio += ratio / 4;
					if(skill_lv>9 && flag==3) skillratio += ratio / 2;
					break;
				}
				case KN_BOWLINGBASH:
				case MS_BOWLINGBASH:
					skillratio+= 40 * skill_lv;
					break;
				case AS_GRIMTOOTH:
					skillratio += 20 * skill_lv;
					break;
				case AS_POISONREACT:
					skillratio += 30 * skill_lv;
					break;
				case AS_SONICBLOW:
					skillratio += 300 + 40 * skill_lv;
					break;
				case TF_SPRINKLESAND:
					skillratio += 30;
					break;
				case MC_CARTREVOLUTION:
					skillratio += 50;
					if( sd && sd->cart_weight )
						skillratio += 100 * sd->cart_weight / sd->cart_weight_max; // +1% every 1% weight
					else if (!sd)
						skillratio += 100; //Max damage for non players.
					break;
				case NPC_RANDOMATTACK:
					skillratio += 100 * skill_lv;
					break;
				case NPC_WATERATTACK:
				case NPC_GROUNDATTACK:
				case NPC_FIREATTACK:
				case NPC_WINDATTACK:
				case NPC_POISONATTACK:
				case NPC_HOLYATTACK:
				case NPC_DARKNESSATTACK:
				case NPC_UNDEADATTACK:
				case NPC_TELEKINESISATTACK:
				case NPC_BLOODDRAIN:
				case NPC_ACIDBREATH:
				case NPC_DARKNESSBREATH:
				case NPC_FIREBREATH:
				case NPC_ICEBREATH:
				case NPC_THUNDERBREATH:
				case NPC_HELLJUDGEMENT:
				case NPC_PULSESTRIKE:
					skillratio += 100 * (skill_lv-1);
					break;
				case NPC_EARTHQUAKE:
					skillratio += 100 + 100 * skill_lv + 100 * (skill_lv / 2);
					break;
				case RG_BACKSTAP:
					if( sd && sd->status.weapon == W_BOW && battle_config.backstab_bow_penalty )
						skillratio += (200 + 40 * skill_lv) / 2;
					else
						skillratio += 200 + 40 * skill_lv;
					break;
				case RG_RAID:
					skillratio += 40 * skill_lv;
					break;
				case RG_INTIMIDATE:
					skillratio += 30 * skill_lv;
					break;
				case CR_SHIELDCHARGE:
					skillratio += 20 * skill_lv;
					break;
				case CR_SHIELDBOOMERANG:
					skillratio += 30 * skill_lv;
					break;
				case NPC_DARKCROSS:
				case CR_HOLYCROSS:
				{
					int ratio = 35 * skill_lv;
					#ifdef RENEWAL
						if(sd && sd->status.weapon == W_2HSPEAR)
							ratio *= 2;
					#endif
					skillratio += ratio;
					break;
				}
				case AM_DEMONSTRATION:
					skillratio += 20 * skill_lv;
					break;
				case AM_ACIDTERROR:
#ifdef RENEWAL
					skillratio += 80 * skill_lv + 100;
#else
					skillratio += 40 * skill_lv;
#endif
					break;
				case MO_FINGEROFFENSIVE:
					skillratio+= 50 * skill_lv;
					break;
				case MO_INVESTIGATE:
					skillratio += 75 * skill_lv;
					break;
				case MO_EXTREMITYFIST:
	#ifndef RENEWAL
					{
						//Overflow check. [Skotlex]
						unsigned int ratio = skillratio + 100*(8 + st->sp/10);
						//You'd need something like 6K SP to reach this max, so should be fine for most purposes.
						if (ratio > 60000) ratio = 60000; //We leave some room here in case skillratio gets further increased.
						skillratio = (unsigned short)ratio;
					}
#endif
					break;
				case MO_TRIPLEATTACK:
					skillratio += 20 * skill_lv;
					break;
				case MO_CHAINCOMBO:
					skillratio += 50 + 50 * skill_lv;
					break;
				case MO_COMBOFINISH:
					skillratio += 140 + 60 * skill_lv;
					break;
				case BA_MUSICALSTRIKE:
				case DC_THROWARROW:
					skillratio += 25 + 25 * skill_lv;
					break;
				case CH_TIGERFIST:
					skillratio += 100 * skill_lv - 60;
					break;
				case CH_CHAINCRUSH:
					skillratio += 300 + 100 * skill_lv;
					break;
				case CH_PALMSTRIKE:
					skillratio += 100 + 100 * skill_lv;
					break;
				case LK_HEADCRUSH:
					skillratio += 40 * skill_lv;
					break;
				case LK_JOINTBEAT:
					i = 10 * skill_lv - 50;
					// Although not clear, it's being assumed that the 2x damage is only for the break neck ailment.
					if (flag&BREAK_NECK) i*=2;
					skillratio += i;
					break;
				case ASC_METEORASSAULT:
					skillratio += 40 * skill_lv - 60;
					break;
				case SN_SHARPSHOOTING:
				case MA_SHARPSHOOTING:
					skillratio += 100 + 50 * skill_lv;
					break;
				case CG_ARROWVULCAN:
					skillratio += 100 + 100 * skill_lv;
					break;
				case AS_SPLASHER:
					skillratio += 400 + 50 * skill_lv;
					if(sd)
						skillratio += 20 * pc->checkskill(sd,AS_POISONREACT);
					break;
	#ifndef RENEWAL
				case ASC_BREAKER:
					skillratio += 100*skill_lv-100;
	#else
				case LK_SPIRALPIERCE:
				case ML_SPIRALPIERCE:
					skillratio += 50 * skill_lv;
	#endif
					break;
				case PA_SACRIFICE:
					skillratio += 10 * skill_lv - 10;
					break;
				case PA_SHIELDCHAIN:
					skillratio += 30 * skill_lv;
					break;
				case WS_CARTTERMINATION:
					i = 10 * (16 - skill_lv);
					if (i < 1) i = 1;
					//Preserve damage ratio when max cart weight is changed.
					if(sd && sd->cart_weight)
						skillratio += sd->cart_weight/i * 80000/battle_config.max_cart_weight - 100;
					else if (!sd)
						skillratio += 80000 / i - 100;
					break;
				case TK_DOWNKICK:
					skillratio += 60 + 20 * skill_lv;
					break;
				case TK_STORMKICK:
					skillratio += 60 + 20 * skill_lv;
					break;
				case TK_TURNKICK:
					skillratio += 90 + 30 * skill_lv;
					break;
				case TK_COUNTER:
					skillratio += 90 + 30 * skill_lv;
					break;
				case TK_JUMPKICK:
					skillratio += -70 + 10*skill_lv;
					if (sc && sc->data[SC_COMBOATTACK] && sc->data[SC_COMBOATTACK]->val1 == skill_id)
						skillratio += 10 * status->get_lv(src) / 3; //Tumble bonus
					if (flag) {
						skillratio += 10 * status->get_lv(src) / 3; //Running bonus (TODO: What is the real bonus?)
						if( sc && sc->data[SC_STRUP] )  // Spurt bonus
							skillratio *= 2;
					}
					break;
				case GS_TRIPLEACTION:
					skillratio += 50 * skill_lv;
					break;
				case GS_BULLSEYE:
					//Only works well against brute/demi-humans non bosses.
					if((tst->race == RC_BRUTE || tst->race == RC_DEMIHUMAN)
						&& !(tst->mode&MD_BOSS))
						skillratio += 400;
					break;
				case GS_TRACKING:
					skillratio += 100 * (skill_lv+1);
					break;
#ifndef RENEWAL
				case GS_PIERCINGSHOT:
						skillratio += 20 * skill_lv;
					break;
#endif
				case GS_RAPIDSHOWER:
					skillratio += 10 * skill_lv;
					break;
				case GS_DESPERADO:
					skillratio += 50 * (skill_lv-1);
					break;
				case GS_DUST:
					skillratio += 50 * skill_lv;
					break;
				case GS_FULLBUSTER:
					skillratio += 100 * (skill_lv+2);
					break;
				case GS_SPREADATTACK:
				#ifdef RENEWAL
					skillratio += 20 * (skill_lv);
				#else
					skillratio += 20 * (skill_lv-1);
				#endif
					break;
				case NJ_HUUMA:
					skillratio += 50 + 150 * skill_lv;
					break;
				case NJ_TATAMIGAESHI:
					skillratio += 10 * skill_lv;
					break;
				case NJ_KASUMIKIRI:
					skillratio += 10 * skill_lv;
					break;
				case NJ_KIRIKAGE:
					skillratio += 100 * (skill_lv-1);
					break;
				case KN_CHARGEATK:
					{
						int k = (flag-1)/3; //+100% every 3 cells of distance
						if( k > 2 ) k = 2; // ...but hard-limited to 300%.
						skillratio += 100 * k;
					}
					break;
				case HT_PHANTASMIC:
					skillratio += 50;
					break;
				case MO_BALKYOUNG:
					skillratio += 200;
					break;
				case HFLI_MOON: //[orn]
					skillratio += 10 + 110 * skill_lv;
					break;
				case HFLI_SBR44: //[orn]
					skillratio += 100 * (skill_lv-1);
					break;
				case NPC_VAMPIRE_GIFT:
					skillratio += ((skill_lv-1)%5+1) * 100;
					break;
				case RK_SONICWAVE:
					skillratio = (skill_lv + 5) * 100;
					skillratio = skillratio * (100 + (status->get_lv(src)-100) / 2) / 100;
					break;
				case RK_HUNDREDSPEAR:
						skillratio += 500 + (80 * skill_lv);
						if( sd ){
							short index = sd->equip_index[EQI_HAND_R];
							if( index >= 0 && sd->inventory_data[index]
								&& sd->inventory_data[index]->type == IT_WEAPON )
								skillratio += (10000 - min(10000, sd->inventory_data[index]->weight)) / 10;
							skillratio = skillratio * (100 + (status->get_lv(src)-100) / 2) / 100 + 50 * pc->checkskill(sd,LK_SPIRALPIERCE);
						}
					break;
				case RK_WINDCUTTER:
						skillratio = (skill_lv + 2) * 50;
						RE_LVL_DMOD(100);
					break;
				case RK_IGNITIONBREAK:
					i = distance_bl(src,target);
					if( i < 2 )
						skillratio = 300 * skill_lv;
					else if( i < 4 )
						skillratio = 250 * skill_lv;
					else
						skillratio = 200 * skill_lv;
					skillratio = skillratio * status->get_lv(src) / 100;
					if( st->rhw.ele == ELE_FIRE )
						skillratio += 100 * skill_lv;
					break;
				case RK_STORMBLAST:
					skillratio = ((sd ? pc->checkskill(sd,RK_RUNEMASTERY) : 1) + status_get_int(src) / 8) * 100;
					break;
				case RK_PHANTOMTHRUST:
					skillratio = 50 * skill_lv + 10 * (sd ? pc->checkskill(sd,KN_SPEARMASTERY) : 10);
					RE_LVL_DMOD(150);
					break;
				/**
					* GC Guillotine Cross
					**/
				case GC_CROSSIMPACT:
					skillratio += 900 + 100 * skill_lv;
					RE_LVL_DMOD(120);
					break;
				case GC_PHANTOMMENACE:
					skillratio += 200;
					break;
				case GC_COUNTERSLASH:
					//ATK [{(Skill Level x 100) + 300} x Caster's Base Level / 120]% + ATK [(AGI x 2) + (Caster's Job Level x 4)]%
					skillratio += 200 + (100 * skill_lv);
					RE_LVL_DMOD(120);
					break;
				case GC_ROLLINGCUTTER:
					skillratio = 50 + 50 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case GC_CROSSRIPPERSLASHER:
					skillratio += 300 + 80 * skill_lv;
					RE_LVL_DMOD(100);
					if( sc && sc->data[SC_ROLLINGCUTTER] )
						skillratio += sc->data[SC_ROLLINGCUTTER]->val1 * status_get_agi(src);
					break;
				case GC_DARKCROW:
					skillratio += 100 * (skill_lv - 1);
					break;
				/**
					* Arch Bishop
					**/
				case AB_DUPLELIGHT_MELEE:
					skillratio += 10 * skill_lv;
					break;
				/**
					* Ranger
					**/
				case RA_ARROWSTORM:
					skillratio += 900 + 80 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case RA_AIMEDBOLT:
					skillratio += 400 + 50 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case RA_CLUSTERBOMB:
					skillratio += 100 + 100 * skill_lv;
					break;
				case RA_WUGDASH:// ATK 300%
					skillratio = 300;
					if( sc && sc->data[SC_DANCE_WITH_WUG] )
						skillratio += 10 * sc->data[SC_DANCE_WITH_WUG]->val1 * (2 + battle->calc_chorusbonus(sd));
					break;
				case RA_WUGSTRIKE:
					skillratio = 200 * skill_lv;
					if( sc && sc->data[SC_DANCE_WITH_WUG] )
						skillratio += 10 * sc->data[SC_DANCE_WITH_WUG]->val1 * (2 + battle->calc_chorusbonus(sd));
					break;
				case RA_WUGBITE:
					skillratio += 300 + 200 * skill_lv;
					if ( skill_lv == 5 ) skillratio += 100;
					break;
				case RA_SENSITIVEKEEN:
					skillratio = 150 * skill_lv;
					break;
				/**
					* Mechanic
					**/
				case NC_BOOSTKNUCKLE:
					skillratio = skill_lv * 100 + 200 + st->dex;
					RE_LVL_DMOD(120);
					break;
				case NC_PILEBUNKER:
					skillratio = skill_lv*100 + 300 + status_get_str(src);
					RE_LVL_DMOD(100);
					break;
				case NC_VULCANARM:
					skillratio = 70 * skill_lv + status_get_dex(src);
					RE_LVL_DMOD(120);
					break;
				case NC_FLAMELAUNCHER:
				case NC_COLDSLOWER:
					skillratio += 200 + 300 * skill_lv;
					RE_LVL_DMOD(150);
					break;
				case NC_ARMSCANNON:
					switch( tst->size ) {
						case SZ_SMALL: skillratio = 300 + 350 * skill_lv; break; // Medium
						case SZ_MEDIUM: skillratio = 300 + 400 * skill_lv; break;  // Small
						case SZ_BIG: skillratio = 300 + 300 * skill_lv; break;    // Large
					}
					RE_LVL_DMOD(120);
					break;
				case NC_AXEBOOMERANG:
					skillratio = 250 + 50 * skill_lv;
					if( sd ) {
						short index = sd->equip_index[EQI_HAND_R];
						if( index >= 0 && sd->inventory_data[index] && sd->inventory_data[index]->type == IT_WEAPON )
						skillratio += sd->inventory_data[index]->weight / 10;
					}
					RE_LVL_DMOD(100);
					break;
				case NC_POWERSWING:
					skillratio = 300 + 100*skill_lv + ( status_get_str(src)+status_get_dex(src) ) * status->get_lv(src) / 100;
					break;
				case NC_AXETORNADO:
					skillratio = 200 + 100 * skill_lv + st->vit;
					RE_LVL_DMOD(100);
					if( st->rhw.ele == ELE_WIND )
						skillratio = skillratio * 125 / 100;
					if ( distance_bl(src, target) > 2 ) // Will deal 75% damage outside of 5x5 area.
						skillratio = skillratio * 75 / 100;
					break;
				case SC_FATALMENACE:
					skillratio = 100 * (skill_lv+1);
					RE_LVL_DMOD(100);
					break;
				case SC_TRIANGLESHOT:
					skillratio = ( 300 + (skill_lv-1) * status_get_agi(src)/2 );
					RE_LVL_DMOD(120);
					break;
				case SC_FEINTBOMB:
					skillratio = (skill_lv+1) * (st->dex/2) * (sd?sd->status.job_level:50)/10;
					RE_LVL_DMOD(120);
					break;
				case LG_CANNONSPEAR:
					skillratio = (50 + st->str) * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case LG_BANISHINGPOINT:
					skillratio = 50 * skill_lv + 30 * (sd ? pc->checkskill(sd,SM_BASH) : 10);
					RE_LVL_DMOD(100);
					break;
				case LG_SHIELDPRESS:
					skillratio = 150 * skill_lv + st->str;
					if( sd ) {
						short index = sd->equip_index[EQI_HAND_L];
						if( index >= 0 && sd->inventory_data[index] && sd->inventory_data[index]->type == IT_ARMOR )
						skillratio += sd->inventory_data[index]->weight / 10;
					}
					RE_LVL_DMOD(100);
					break;
				case LG_PINPOINTATTACK:
					skillratio = 100 * skill_lv + 5 * st->agi;
					RE_LVL_DMOD(120);
					break;
				case LG_RAGEBURST:
					if( sc ){
						skillratio += -100 + (status_get_max_hp(src) - status_get_hp(src)) / 100 + sc->fv_counter * 200;
						clif->millenniumshield(src, (sc->fv_counter = 0));
					}
					RE_LVL_DMOD(100);
					break;
				case LG_SHIELDSPELL:
					if ( sd && skill_lv == 1 ) {
						struct item_data *shield_data = sd->inventory_data[sd->equip_index[EQI_HAND_L]];
						if( shield_data )
							skillratio = 4 * status->get_lv(src) + 10 * shield_data->def + 2 * st->vit;
						}
					else
						skillratio = 0; // Prevents ATK damage from being done on LV 2 usage since LV 2 us MATK. [Rytech]
					break;
				case LG_MOONSLASHER:
					skillratio = 120 * skill_lv + 80 * (sd ? pc->checkskill(sd,LG_OVERBRAND) : 5);
					RE_LVL_DMOD(100);
					break;
				case LG_OVERBRAND:
					skillratio += -100 + 400 * skill_lv + 50 * ((sd) ? pc->checkskill(sd,CR_SPEARQUICKEN) : 1);
					RE_LVL_DMOD(100);
					break;
				case LG_OVERBRAND_BRANDISH:
					skillratio += -100 + 300 * skill_lv + status_get_str(src) + status_get_dex(src);
					RE_LVL_DMOD(100);
					break;
				case LG_OVERBRAND_PLUSATK:
					skillratio = 200 * skill_lv + rnd_value( 10, 100);
					RE_LVL_DMOD(100);
					break;
				case LG_RAYOFGENESIS:
					skillratio = 300 + 300 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case LG_EARTHDRIVE:
					if( sd ) {
						short index = sd->equip_index[EQI_HAND_L];
						if( index >= 0 && sd->inventory_data[index] && sd->inventory_data[index]->type == IT_ARMOR )
						skillratio = (1 + skill_lv) * sd->inventory_data[index]->weight / 10;
					}
					RE_LVL_DMOD(100);
					break;
				case LG_HESPERUSLIT:
					skillratio = 120 * skill_lv;
					if( sc && sc->data[SC_BANDING] )
						skillratio += 200 * sc->data[SC_BANDING]->val2;
					if( sc && sc->data[SC_BANDING] && sc->data[SC_BANDING]->val2 > 5 )
						skillratio = skillratio * 150 / 100;
					if( sc && sc->data[SC_INSPIRATION] )
						skillratio += 600;
					RE_LVL_DMOD(100);
					break;
				case SR_DRAGONCOMBO:
					skillratio += 40 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case SR_SKYNETBLOW:
					if( sc && sc->data[SC_COMBOATTACK] && sc->data[SC_COMBOATTACK]->val1 == SR_DRAGONCOMBO )//ATK [{(Skill Level x 100) + (Caster AGI) + 150} x Caster Base Level / 100] %
						skillratio += 100 * skill_lv + status_get_agi(src) + 50;
					else //ATK [{(Skill Level x 80) + (Caster AGI)} x Caster Base Level / 100] %
						skillratio += -100 + 80 * skill_lv + status_get_agi(src);
					RE_LVL_DMOD(100);
					break;
				case SR_EARTHSHAKER:
					if( tsc && (tsc->data[SC_HIDING] || tsc->data[SC_CLOAKING] || // [(Skill Level x 150) x (Caster Base Level / 100) + (Caster INT x 3)] %
						tsc->data[SC_CHASEWALK] || tsc->data[SC_CLOAKINGEXCEED] || tsc->data[SC__INVISIBILITY]) ){
						skillratio += -100 + 150 * skill_lv;
						RE_LVL_DMOD(100);
						skillratio += status_get_int(src) * 3;
					}else{ //[(Skill Level x 50) x (Caster Base Level / 100) + (Caster INT x 2)] %
						skillratio += 50 * (skill_lv-2);
						RE_LVL_DMOD(100);
						skillratio += status_get_int(src) * 2;
					}
					break;
				case SR_FALLENEMPIRE:// ATK [(Skill Level x 150 + 100) x Caster Base Level / 150] %
					skillratio += 150 *skill_lv;
					RE_LVL_DMOD(150);
					break;
				case SR_TIGERCANNON:// ATK [((Caster consumed HP + SP) / 4) x Caster Base Level / 100] %
					{
						int hp = status_get_max_hp(src) * (10 + 2 * skill_lv) / 100,
							sp = status_get_max_sp(src) * (6 + skill_lv) / 100;
						if( sc && sc->data[SC_COMBOATTACK] && sc->data[SC_COMBOATTACK]->val1 == SR_FALLENEMPIRE ) // ATK [((Caster consumed HP + SP) / 2) x Caster Base Level / 100] %
							skillratio += -100 + (hp+sp) / 2;
						else
							skillratio += -100 + (hp+sp) / 4;
						RE_LVL_DMOD(100);
					}
						break;
				case SR_RAMPAGEBLASTER:
					skillratio += 20 * skill_lv * (sd?sd->spiritball_old:5) - 100;
					if( sc && sc->data[SC_EXPLOSIONSPIRITS] ) {
						skillratio += sc->data[SC_EXPLOSIONSPIRITS]->val1 * 20;
						RE_LVL_DMOD(120);
					} else {
						RE_LVL_DMOD(150);
					}
					break;
				case SR_KNUCKLEARROW:
					if ( flag&4 || map->list[src->m].flag.gvg_castle || tst->mode&MD_BOSS ) {
						// ATK [(Skill Level x 150) + (1000 x Target current weight / Maximum weight) + (Target Base Level x 5) x (Caster Base Level / 150)] %
						skillratio = 150 * skill_lv + status->get_lv(target) * 5 * (status->get_lv(src) / 100) ;
						if( tsd && tsd->weight )
							skillratio += 100 * (tsd->weight / tsd->max_weight);
					}else // ATK [(Skill Level x 100 + 500) x Caster Base Level / 100] %
						skillratio += 400 + (100 * skill_lv);
					RE_LVL_DMOD(100);
					break;
				case SR_WINDMILL: // ATK [(Caster Base Level + Caster DEX) x Caster Base Level / 100] %
					skillratio = status->get_lv(src) + status_get_dex(src);
					RE_LVL_DMOD(100);
					break;
				case SR_GATEOFHELL:
					if( sc && sc->data[SC_COMBOATTACK]
						&& sc->data[SC_COMBOATTACK]->val1 == SR_FALLENEMPIRE )
						skillratio += 800 * skill_lv -100;
					else
						skillratio += 500 * skill_lv -100;
					RE_LVL_DMOD(100);
					break;
				case SR_GENTLETOUCH_QUIET:
					skillratio += 100 * skill_lv - 100 + status_get_dex(src);
					RE_LVL_DMOD(100);
					break;
				case SR_HOWLINGOFLION:
					skillratio += 300 * skill_lv - 100;
					RE_LVL_DMOD(150);
					break;
				case SR_RIDEINLIGHTNING: // ATK [{(Skill Level x 200) + Additional Damage} x Caster Base Level / 100] %
					if( (st->rhw.ele) == ELE_WIND || (st->lhw.ele) == ELE_WIND )
						skillratio += skill_lv * 50;
					skillratio += -100 + 200 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case WM_REVERBERATION_MELEE:
					skillratio += 200 + 100 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case WM_SEVERE_RAINSTORM_MELEE:
					skillratio = (st->agi + st->dex) * skill_lv / 5;
					RE_LVL_DMOD(100);
					break;
				case WM_GREAT_ECHO:
				{
					int chorusbonus = battle->calc_chorusbonus(sd);
					skillratio += 300 + 200 * skill_lv;
					//Chorus bonus don't count the first 2 Minstrel's/Wanderer's and only increases when their's 3 or more. [Rytech]
					if (chorusbonus >= 1 && chorusbonus <= 5)
						skillratio += 100<<(chorusbonus-1); // 1->100; 2->200; 3->400; 4->800; 5->1600
					RE_LVL_DMOD(100);
				}
					break;
				case GN_CART_TORNADO:
				{
					int strbonus = bst->str;
					skillratio = 50 * skill_lv + (sd ? sd->cart_weight : battle_config.max_cart_weight) / 10 / max(150 - strbonus, 1) + 50 * (sd ? pc->checkskill(sd, GN_REMODELING_CART) : 5);
				}
					break;
				case GN_CARTCANNON:
					skillratio += -100 + (int)(50.0f * (sd ? pc->checkskill(sd, GN_REMODELING_CART) : 5) * (st->int_ / 40.0f) + 60.0f * skill_lv);
					break;
				case GN_SPORE_EXPLOSION:
					skillratio = 100 * skill_lv + (200 + st->int_) * status->get_lv(src) / 100;
					/* Fall through */
				case GN_CRAZYWEED_ATK:
					skillratio += 400 + 100 * skill_lv;
					break;
				case GN_SLINGITEM_RANGEMELEEATK:
					if( sd ) {
						switch( sd->itemid ) {
							case ITEMID_APPLE_BOMB:
								skillratio = st->str + st->dex + 300;
								break;
							case ITEMID_MELON_BOMB:
								skillratio = st->str + st->dex + 500;
								break;
							case ITEMID_COCONUT_BOMB:
							case ITEMID_PINEAPPLE_BOMB:
							case ITEMID_BANANA_BOMB:
								skillratio = st->str + st->dex + 800;
								break;
							case ITEMID_BLACK_LUMP:
								skillratio = (st->str + st->agi + st->dex) / 3; // Black Lump
								break;
							case ITEMID_BLACK_HARD_LUMP:
								skillratio = (st->str + st->agi + st->dex) / 2; // Hard Black Lump
								break;
							case ITEMID_VERY_HARD_LUMP:
								skillratio = st->str + st->agi + st->dex; // Extremely Hard Black Lump
								break;
						}
					}
					break;
				case SO_VARETYR_SPEAR://ATK [{( Striking Level x 50 ) + ( Varetyr Spear Skill Level x 50 )} x Caster Base Level / 100 ] %
					skillratio += -100 + 50 * skill_lv + ( sd ? pc->checkskill(sd, SO_STRIKING) * 50 : 0 );
					if( sc && sc->data[SC_BLAST_OPTION] )
						skillratio += (sd ? sd->status.job_level * 5 : 0);
					break;
					// Physical Elemental Spirits Attack Skills
				case EL_CIRCLE_OF_FIRE:
				case EL_FIRE_BOMB_ATK:
				case EL_STONE_RAIN:
					skillratio += 200;
					break;
				case EL_FIRE_WAVE_ATK:
					skillratio += 500;
					break;
				case EL_TIDAL_WEAPON:
					skillratio += 1400;
					break;
				case EL_WIND_SLASH:
					skillratio += 100;
					break;
				case EL_HURRICANE:
					skillratio += 600;
					break;
				case EL_TYPOON_MIS:
				case EL_WATER_SCREW_ATK:
					skillratio += 900;
					break;
				case EL_STONE_HAMMER:
					skillratio += 400;
					break;
				case EL_ROCK_CRUSHER:
					skillratio += 700;
					break;
				case KO_JYUMONJIKIRI:
					skillratio += -100 + 150 * skill_lv;
					RE_LVL_DMOD(120);
					if( tsc && tsc->data[SC_KO_JYUMONJIKIRI] )
						skillratio += status->get_lv(src) * skill_lv;
					break;
				case KO_HUUMARANKA:
					skillratio += -100 + 150 * skill_lv + status_get_agi(src) + status_get_dex(src) + 100 * (sd ? pc->checkskill(sd, NJ_HUUMA) : 0);
					break;
				case KO_SETSUDAN:
					skillratio += -100 + 100 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case MH_NEEDLE_OF_PARALYZE:
					skillratio += 600 + 100 * skill_lv;
					break;
				case MH_STAHL_HORN:
					skillratio += 400 + 100 * skill_lv;
					break;
				case MH_LAVA_SLIDE:
					skillratio += -100 + 70 * skill_lv;
					break;
				case MH_TINDER_BREAKER:
				case MH_MAGMA_FLOW:
					skillratio += -100 + 100 * skill_lv;
					break;
				default:
					battle->calc_skillratio_weapon_unknown(&attack_type, src, target, &skill_id, &skill_lv, &skillratio, &flag);
					break;
			}
