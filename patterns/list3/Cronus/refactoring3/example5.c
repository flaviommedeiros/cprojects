switch(skill_id){
				case MG_NAPALMBEAT:
					skillratio += skill_lv * 10 - 30;
					break;
				case MG_FIREBALL:
			#ifdef RENEWAL
					skillratio += 20 * skill_lv;
			#else
					skillratio += skill_lv * 10 - 30;
			#endif
					break;
				case MG_SOULSTRIKE:
					if (battle->check_undead(tst->race,tst->def_ele))
						skillratio += 5*skill_lv;
					break;
				case MG_FIREWALL:
					skillratio -= 50;
					break;
				case MG_THUNDERSTORM:
					/**
					 * in Renewal Thunder Storm boost is 100% (in pre-re, 80%)
					 **/
					#ifndef RENEWAL
						skillratio -= 20;
					#endif
					break;
				case MG_FROSTDIVER:
					skillratio += 10 * skill_lv;
					break;
				case AL_HOLYLIGHT:
					skillratio += 25;
					if (sc && sc->data[SC_SOULLINK] && sc->data[SC_SOULLINK]->val2 == SL_PRIEST)
						skillratio *= 5; //Does 5x damage include bonuses from other skills?
					break;
				case AL_RUWACH:
					skillratio += 45;
					break;
				case WZ_FROSTNOVA:
					skillratio += (100+skill_lv*10) * 2 / 3 - 100;
					break;
				case WZ_FIREPILLAR:
					if (skill_lv > 10)
						skillratio += 2300; //200% MATK each hit
					else
						skillratio += -60 + 20*skill_lv; //20% MATK each hit
					break;
				case WZ_SIGHTRASHER:
					skillratio += 20 * skill_lv;
					break;
				case WZ_WATERBALL:
					skillratio += 30 * skill_lv;
					break;
				case WZ_STORMGUST:
					skillratio += 40 * skill_lv;
					break;
				case HW_NAPALMVULCAN:
					skillratio += 10 * skill_lv - 30;
					break;
				case SL_STIN:
					skillratio += (tst->size!=SZ_SMALL?-99:10*skill_lv); //target size must be small (0) for full damage.
					break;
				case SL_STUN:
					skillratio += (tst->size!=SZ_BIG?5*skill_lv:-99); //Full damage is dealt on small/medium targets
					break;
				case SL_SMA:
					skillratio += -60 + status->get_lv(src); //Base damage is 40% + lv%
					break;
				case NJ_KOUENKA:
					skillratio -= 10;
					if (sd && sd->charm_type == CHARM_TYPE_FIRE && sd->charm_count > 0)
						skillratio += 20 * sd->charm_count;
					break;
				case NJ_KAENSIN:
					skillratio -= 50;
					if (sd && sd->charm_type == CHARM_TYPE_FIRE && sd->charm_count > 0)
						skillratio += 10 * sd->charm_count;
					break;
				case NJ_BAKUENRYU:
					skillratio += 50 * (skill_lv - 1);
					if (sd && sd->charm_type == CHARM_TYPE_FIRE && sd->charm_count > 0)
						skillratio += 15 * sd->charm_count;
					break;
#ifdef RENEWAL
				case NJ_HYOUSENSOU:
					skillratio -= 30;
					if (sd && sd->charm_type == CHARM_TYPE_WATER && sd->charm_count > 0)
						skillratio += 5 * sd->charm_count;
					break;
#endif
				case NJ_HYOUSYOURAKU:
					skillratio += 50 * skill_lv;
					if (sd && sd->charm_type == CHARM_TYPE_WATER && sd->charm_count > 0)
						skillratio += 25 * sd->charm_count;
					break;
				case NJ_RAIGEKISAI:
					skillratio += 60 + 40 * skill_lv;
					if (sd && sd->charm_type == CHARM_TYPE_WIND && sd->charm_count > 0)
						skillratio += 15 * sd->charm_count;
					break;
				case NJ_KAMAITACHI:
					if (sd && sd->charm_type == CHARM_TYPE_WIND && sd->charm_count > 0)
						skillratio += 10 * sd->charm_count;
					/* Fall through */
				case NPC_ENERGYDRAIN:
					skillratio += 100 * skill_lv;
					break;
			#ifdef RENEWAL
				case WZ_HEAVENDRIVE:
				case WZ_METEOR:
					skillratio += 25;
					break;
				case WZ_VERMILION:
				{
					int interval = 0, per = interval, ratio = per;
					while( (per++) < skill_lv ){
						ratio += interval;
						if(per%3==0) interval += 20;
					}
					if( skill_lv > 9 )
						ratio -= 10;
					skillratio += ratio;
				}
					break;
				case NJ_HUUJIN:
					skillratio += 50;
					if (sd && sd->charm_type == CHARM_TYPE_WIND && sd->charm_count > 0)
						skillratio += 20 * sd->charm_count;
					break;
			#else
				case WZ_VERMILION:
					skillratio += 20*skill_lv-20;
					break;
			#endif
				/**
					* Arch Bishop
					**/
				case AB_JUDEX:
					skillratio = 300 + 20 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case AB_ADORAMUS:
					skillratio = 500 + 100 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case AB_DUPLELIGHT_MAGIC:
					skillratio = 200 + 20 * skill_lv;
					break;
				/**
					* Warlock
					**/
				case WL_SOULEXPANSION: // MATK [{( Skill Level + 4 ) x 100 ) + ( Caster's INT )} x ( Caster's Base Level / 100 )] %
					skillratio = 100 * (skill_lv + 4) + st->int_;
					RE_LVL_DMOD(100);
					break;
				case WL_FROSTMISTY: // MATK [{( Skill Level x 100 ) + 200 } x ( Caster's Base Level / 100 )] %
					skillratio += 100 + 100 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case WL_JACKFROST:
					if( tsc && tsc->data[SC_FROSTMISTY] ){
						skillratio += 900 + 300 * skill_lv;
						RE_LVL_DMOD(100);
					}else{
						skillratio += 400 + 100 * skill_lv;
						RE_LVL_DMOD(150);
					}
					break;
				case WL_DRAINLIFE:
					skillratio = 200 * skill_lv + status_get_int(src);
					RE_LVL_DMOD(100);
					break;
				case WL_CRIMSONROCK:
					skillratio = 300 * skill_lv;
					RE_LVL_DMOD(100);
					skillratio += 1300;
					break;
				case WL_HELLINFERNO:
					skillratio = 300 * skill_lv;
					RE_LVL_DMOD(100);
					// Shadow: MATK [{( Skill Level x 300 ) x ( Caster Base Level / 100 ) x 4/5 }] %
					// Fire : MATK [{( Skill Level x 300 ) x ( Caster Base Level / 100 ) /5 }] %
					if( flag&ELE_DARK )
						skillratio *= 4;
					skillratio /= 5;
					break;
				case WL_COMET:
					i = ( sc ? distance_xy(target->x, target->y, sc->comet_x, sc->comet_y) : 8 );
					if( i <= 3 ) skillratio += 2400 + 500 * skill_lv; // 7 x 7 cell
					else
					if( i <= 5 ) skillratio += 1900 + 500 * skill_lv; // 11 x 11 cell
					else
					if( i <= 7 ) skillratio += 1400 + 500 * skill_lv; // 15 x 15 cell
					else
						skillratio += 900 + 500 * skill_lv; // 19 x 19 cell

					if( sd && sd->status.party_id ){
						struct map_session_data* psd;
						int p_sd[5] = {0, 0, 0, 0, 0}, c; // just limit it to 5

						c = 0;
						memset (p_sd, 0, sizeof(p_sd));
						party->foreachsamemap(skill->check_condition_char_sub, sd, 3, &sd->bl, &c, &p_sd, skill_id);
						c = ( c > 1 ? rnd()%c : 0 );

						if( (psd = map->id2sd(p_sd[c])) && pc->checkskill(psd,WL_COMET) > 0 ){
							skillratio = skill_lv * 400; //MATK [{( Skill Level x 400 ) x ( Caster's Base Level / 120 )} + 2500 ] %
							RE_LVL_DMOD(120);
							skillratio += 2500;
							status_zap(&psd->bl, 0, skill->get_sp(skill_id, skill_lv) / 2);
						}
					}
					break;
				case WL_CHAINLIGHTNING_ATK:
					skillratio += 400 + 100 * skill_lv;
					RE_LVL_DMOD(100);
					if(flag > 0)
						skillratio += 100 * flag;
					break;
				case WL_EARTHSTRAIN:
					skillratio = 2000 + 100 * skill_lv;
					RE_LVL_DMOD(100);
					break;
				case WL_TETRAVORTEX_FIRE:
				case WL_TETRAVORTEX_WATER:
				case WL_TETRAVORTEX_WIND:
				case WL_TETRAVORTEX_GROUND:
					skillratio += 400 + 500 * skill_lv;
					break;
				case WL_SUMMON_ATK_FIRE:
				case WL_SUMMON_ATK_WATER:
				case WL_SUMMON_ATK_WIND:
				case WL_SUMMON_ATK_GROUND:
					skillratio = (1 + skill_lv) / 2 *  (status->get_lv(src) + (sd ? sd->status.job_level : 50));
					RE_LVL_DMOD(100);
					break;
				case LG_RAYOFGENESIS:
				{
					uint16 lv = skill_lv;
					int bandingBonus = 0;
					if( sc && sc->data[SC_BANDING] )
						bandingBonus = 200 * (sd ? skill->check_pc_partner(sd,skill_id,&lv,skill->get_splash(skill_id,skill_lv),0) : 1);
					skillratio = ((300 * skill_lv) + bandingBonus) * (sd ? sd->status.job_level : 1) / 25;
				}
					break;
				case LG_SHIELDSPELL:
					if ( sd && skill_lv == 2 ) // [(Casters Base Level x 4) + (Shield MDEF x 100) + (Casters INT x 2)] %
						skillratio = 4 * status->get_lv(src) + 100 * sd->bonus.shieldmdef + 2 * st->int_;
					else
						skillratio = 0;
					break;
				case WM_METALICSOUND:
					skillratio = 120 * skill_lv + 60 * ( sd? pc->checkskill(sd, WM_LESSON) : 10 );
					RE_LVL_DMOD(100);
					break;
				case WM_REVERBERATION_MAGIC:
					skillratio = 100 * skill_lv + 100;
					RE_LVL_DMOD(100);
					break;
				case SO_FIREWALK:
					skillratio = 60 * skill_lv;
					RE_LVL_DMOD(100);
					if( sc && sc->data[SC_HEATER_OPTION] )
						skillratio += sc->data[SC_HEATER_OPTION]->val3 / 2;
					break;
				case SO_ELECTRICWALK:
					skillratio = 60 * skill_lv;
					RE_LVL_DMOD(100);
					if( sc && sc->data[SC_BLAST_OPTION] )
						skillratio += sc->data[SC_BLAST_OPTION]->val2 / 2;
					break;
				case SO_EARTHGRAVE:
					skillratio = st->int_ * skill_lv + 200 * (sd ? pc->checkskill(sd,SA_SEISMICWEAPON) : 1);
					RE_LVL_DMOD(100);
					if( sc && sc->data[SC_CURSED_SOIL_OPTION] )
						skillratio += sc->data[SC_CURSED_SOIL_OPTION]->val3 * 5;
					break;
				case SO_DIAMONDDUST:
					skillratio = (st->int_ * skill_lv + 200 * (sd ? pc->checkskill(sd, SA_FROSTWEAPON) : 1)) * status->get_lv(src) / 100;
					if( sc && sc->data[SC_COOLER_OPTION] )
						skillratio += sc->data[SC_COOLER_OPTION]->val3 * 5;
					break;
				case SO_POISON_BUSTER:
					skillratio += 900 + 300 * skill_lv;
					RE_LVL_DMOD(100);
					if( sc && sc->data[SC_CURSED_SOIL_OPTION] )
						skillratio += sc->data[SC_CURSED_SOIL_OPTION]->val3 * 5;
					break;
				case SO_PSYCHIC_WAVE:
					skillratio = 70 * skill_lv + 3 * st->int_;
					RE_LVL_DMOD(100);
					if( sc && ( sc->data[SC_HEATER_OPTION] || sc->data[SC_COOLER_OPTION]
					         || sc->data[SC_BLAST_OPTION] || sc->data[SC_CURSED_SOIL_OPTION] ) )
						skillratio += skillratio * 20 / 100;
					break;
				case SO_VARETYR_SPEAR:
					skillratio = status_get_int(src) * skill_lv + ( sd ? pc->checkskill(sd, SA_LIGHTNINGLOADER) * 50 : 0 );
					RE_LVL_DMOD(100);
					if( sc && sc->data[SC_BLAST_OPTION] )
						skillratio += sc->data[SC_BLAST_OPTION]->val2 * 5;
					break;
				case SO_CLOUD_KILL:
					skillratio = 40 * skill_lv;
					RE_LVL_DMOD(100);
					if( sc && sc->data[SC_CURSED_SOIL_OPTION] )
						skillratio += sc->data[SC_CURSED_SOIL_OPTION]->val3;
					break;
				case GN_DEMONIC_FIRE: {
						int fire_expansion_lv = skill_lv / 100;
						skill_lv = skill_lv % 100;
						skillratio = 110 + 20 * skill_lv;
						if ( fire_expansion_lv == 1 )
							skillratio += status_get_int(src) + (sd?sd->status.job_level:50);
						else if ( fire_expansion_lv == 2 )
							skillratio += status_get_int(src) * 10;
					}
					break;
				// Magical Elemental Spirits Attack Skills
				case EL_FIRE_MANTLE:
				case EL_WATER_SCREW:
					skillratio += 900;
					break;
				case EL_FIRE_ARROW:
				case EL_ROCK_CRUSHER_ATK:
					skillratio += 200;
					break;
				case EL_FIRE_BOMB:
				case EL_ICE_NEEDLE:
				case EL_HURRICANE_ATK:
					skillratio += 400;
					break;
				case EL_FIRE_WAVE:
				case EL_TYPOON_MIS_ATK:
					skillratio += 1100;
					break;
				case MH_ERASER_CUTTER:
					skillratio += 400 + 100 * skill_lv + (skill_lv%2 > 0 ? 0 : 300);
					break;
				case MH_XENO_SLASHER:
					if(skill_lv%2) skillratio += 350 + 50 * skill_lv; //500:600:700
					else skillratio += 400 + 100 * skill_lv; //700:900
					break;
				case MH_HEILIGE_STANGE:
					skillratio += 400 + 250 * skill_lv;
					break;
				case MH_POISON_MIST:
					skillratio += 100 * skill_lv;
					break;
				case KO_KAIHOU:
					if (sd && sd->charm_type != CHARM_TYPE_NONE && sd->charm_count > 0) {
						skillratio += -100 + 200 * sd->charm_count;
						RE_LVL_DMOD(100);
						pc->del_charm(sd, sd->charm_count, sd->charm_type);
					}
					break;
				default:
					battle->calc_skillratio_magic_unknown(&attack_type, src, target, &skill_id, &skill_lv, &skillratio, &flag);
					break;
			}
