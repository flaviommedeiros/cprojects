switch(type) {
			case SC_ADORAMUS:
				sc_start(src,bl,SC_BLIND,100,val1,skill->get_time(status->sc2skill(type),val1));
				// Fall through to SC_INC_AGI
			case SC_DEC_AGI:
			case SC_INC_AGI:
				val2 = 2 + val1; //Agi change
				break;
			case SC_ENDURE:
				val2 = 7; // Hit-count [Celest]
				if( !(flag&SCFLAG_NOAVOID) && (bl->type&(BL_PC|BL_MER)) && !map_flag_gvg(bl->m) && !map->list[bl->m].flag.battleground && !val4 ) {
					struct map_session_data *tsd;
					if( sd ) {
						int i;
						for( i = 0; i < MAX_PC_DEVOTION; i++ ) {
							if (sd->devotion[i] && (tsd = map->id2sd(sd->devotion[i])) != NULL)
								status->change_start(bl, &tsd->bl, type, 10000, val1, val2, val3, val4, tick, SCFLAG_ALL);
						}
					} else if (bl->type == BL_MER && ((TBL_MER*)bl)->devotion_flag && (tsd = ((TBL_MER*)bl)->master) != NULL) {
						status->change_start(bl, &tsd->bl, type, 10000, val1, val2, val3, val4, tick, SCFLAG_ALL);
					}
				}
				//val4 signals infinite endure (if val4 == 2 it is infinite endure from Berserk)
				if( val4 )
					tick = -1;
				break;
			case SC_AUTOBERSERK:
				if (st->hp < st->max_hp>>2 &&
					(!sc->data[SC_PROVOKE] || sc->data[SC_PROVOKE]->val2==0))
					sc_start4(src,bl,SC_PROVOKE,100,10,1,0,0,60000);
				tick = -1;
				break;
			case SC_CRUCIS:
				val2 = 10 + 4*val1; //Def reduction
				tick = -1;
				clif->emotion(bl,E_SWT);
				break;
			case SC_MAXIMIZEPOWER:
				tick_time = val2 = tick>0?tick:60000;
				tick = -1; // duration sent to the client should be infinite
				break;
			case SC_EDP: // [Celest]
				//Chance to Poison enemies.
#ifdef RENEWAL_EDP
				val2 = ((val1 + 1) / 2 + 2);
#else
				val2 = val1 + 2;
#endif
				val3 = 50 * (val1 + 1); //Damage increase (+50 +50*lv%)
				if( sd )//[Ind] - iROwiki says each level increases its duration by 3 seconds
					tick += pc->checkskill(sd,GC_RESEARCHNEWPOISON)*3000;
				break;
			case SC_POISONREACT:
				val2=(val1+1)/2 + val1/10; // Number of counters [Skotlex]
				val3=50; // + 5*val1; //Chance to counter. [Skotlex]
				break;
			case SC_MAGICROD:
				val2 = val1*20; //SP gained
				break;
			case SC_KYRIE:
				val2 = APPLY_RATE(st->max_hp, (val1 * 2 + 10)); //%Max HP to absorb
				// val4 holds current about of party memebers when casting AB_PRAEFATIO,
				// as Praefatio's barrier has more health and blocks more hits than Kyrie Elesion.
				if( val4 < 1 ) //== PR_KYRIE
					val3 = (val1 / 2 + 5); // Hits
				else { //== AB_PRAEFATIO
					val2 += val4 * 2; //Increase barrier strength per party member.
					val3 = 6 + val1;
				}
				if( sd )
					val1 = min(val1,pc->checkskill(sd,PR_KYRIE)); // use skill level to determine barrier health.
				break;
			case SC_MAGICPOWER:
				//val1: Skill lv
				val2 = 1; //Lasts 1 invocation
				val3 = 5*val1; //Matk% increase
				val4 = 0; // 0 = ready to be used, 1 = activated and running
				break;
			case SC_SACRIFICE:
				val2 = 5; //Lasts 5 hits
				tick = -1;
				break;
			case SC_ENCHANTPOISON:
				val2= 250+50*val1; //Poisoning Chance (2.5+0.5%) in 1/10000 rate
			case SC_ASPERSIO:
			case SC_PROPERTYFIRE:
			case SC_PROPERTYWATER:
			case SC_PROPERTYWIND:
			case SC_PROPERTYGROUND:
			case SC_PROPERTYDARK:
			case SC_PROPERTYTELEKINESIS:
				skill->enchant_elemental_end(bl,type);
				break;
			case SC_ARMOR_PROPERTY:
				// val1 : Element Lvl (if called by skill lvl 1, takes random value between 1 and 4)
				// val2 : Element (When no element, random one is picked)
				// val3 : 0 = called by skill 1 = called by script (fixed level)
				if( !val2 ) val2 = rnd()%ELE_MAX;

				if( val1 == 1 && val3 == 0 )
					val1 = 1 + rnd()%4;
				else if( val1 > 4 )
					val1 = 4; // Max Level
				val3 = 0; // Not need to keep this info.
				break;
			case SC_PROVIDENCE:
				val2=val1*5; //Race/Ele resist
				break;
			case SC_REFLECTSHIELD:
				val2=10+val1*3; // %Dmg reflected
				if( !(flag&SCFLAG_NOAVOID) && (bl->type&(BL_PC|BL_MER)) ) {
					struct map_session_data *tsd;
					if( sd ) {
						int i;
						for( i = 0; i < MAX_PC_DEVOTION; i++ ) {
							if (sd->devotion[i] && (tsd = map->id2sd(sd->devotion[i])) != NULL)
								status->change_start(bl, &tsd->bl, type, 10000, val1, val2, 0, 0, tick, SCFLAG_ALL);
						}
					} else if (bl->type == BL_MER && ((TBL_MER*)bl)->devotion_flag && (tsd = ((TBL_MER*)bl)->master) != NULL) {
						status->change_start(bl, &tsd->bl, type, 10000, val1, val2, 0, 0, tick, SCFLAG_ALL);
					}
				}
				break;
			case SC_NOEQUIPWEAPON:
				if (!sd) //Watk reduction
					val2 = 25;
				break;
			case SC_NOEQUIPSHIELD:
				if (!sd) //Def reduction
					val2 = 15;
				break;
			case SC_NOEQUIPARMOR:
				if (!sd) //Vit reduction
					val2 = 40;
				break;
			case SC_NOEQUIPHELM:
				if (!sd) //Int reduction
					val2 = 40;
				break;
			case SC_AUTOSPELL:
				//Val1 Skill LV of Autospell
				//Val2 Skill ID to cast
				//Val3 Max Lv to cast
				val4 = 5 + val1*2; //Chance of casting
				break;
			case SC_VOLCANO:
				val2 = val1*10; //Watk increase
	#ifndef RENEWAL
				if (st->def_ele != ELE_FIRE)
					val2 = 0;
	#endif
				break;
			case SC_VIOLENTGALE:
				val2 = val1*3; //Flee increase
	#ifndef RENEWAL
				if (st->def_ele != ELE_WIND)
					val2 = 0;
	#endif
				break;
			case SC_DELUGE:
				val2 = skill->deluge_eff[val1-1]; //HP increase
	#ifndef RENEWAL
				if(st->def_ele != ELE_WATER)
					val2 = 0;
	#endif
				break;
			case SC_NJ_SUITON:
				if (!val2 || (sd && (sd->class_&MAPID_BASEMASK) == MAPID_NINJA)) {
					//No penalties.
					val2 = 0; //Agi penalty
					val3 = 0; //Walk speed penalty
					break;
				}
				val3 = 50;
				val2 = 3*((val1+1)/3);
				if (val1 > 4) val2--;
				break;
			case SC_ONEHANDQUICKEN:
			case SC_TWOHANDQUICKEN:
				val2 = 300;
				if (val1 > 10) //For boss casted skills [Skotlex]
					val2 += 20*(val1-10);
				break;
			case SC_MER_QUICKEN:
				val2 = 300;
				break;
	#ifndef RENEWAL_ASPD
			case SC_SPEARQUICKEN:
				val2 = 200+10*val1;
				break;
	#endif
			case SC_DANCING:
				//val1 : Skill ID + LV
				//val2 : Skill Group of the Dance.
				//val3 : Brings the skill_lv (merged into val1 here)
				//val4 : Partner
				if (val1 == CG_MOONLIT)
					clif->status_change(bl,SI_MOON,1,tick,0, 0, 0);
				val1|= (val3<<16);
				val3 = tick/1000; //Tick duration
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_LONGING:
	#ifdef RENEWAL
				val2 = 50 + 10 * val1;
	#else
				val2 = 500-100*val1; //Aspd penalty.
	#endif
				break;
			case SC_EXPLOSIONSPIRITS:
				val2 = 75 + 25*val1; //Cri bonus
				break;

			case SC_ATTHASTE_POTION1:
			case SC_ATTHASTE_POTION2:
			case SC_ATTHASTE_POTION3:
			case SC_ATTHASTE_INFINITY:
				val2 = 50*(2+type-SC_ATTHASTE_POTION1);
				break;

			case SC_WEDDING:
			case SC_XMAS:
			case SC_SUMMER:
			case SC_HANBOK:
			case SC_OKTOBERFEST:
				if (!vd) return 0;
				//Store previous values as they could be removed.
				unit->stop_attack(bl);
				break;
			case SC_NOCHAT:
				// A hardcoded interval of 60 seconds is expected, as the time that SC_NOCHAT uses is defined by
				// mmocharstatus.manner, each negative point results in 1 minute with this status activated
				// This is done this way because the message that the client displays is hardcoded, and only
				// shows how many minutes are remaining. [Panikon]
				tick = 60000;
				val1 = battle_config.manner_system; //Mute filters.
				if (sd)
				{
					clif->changestatus(sd,SP_MANNER,sd->status.manner);
					clif->updatestatus(sd,SP_MANNER);
				}
				break;

			case SC_STONE:
				val3 = tick/1000; //Petrified HP-damage iterations.
				if(val3 < 1) val3 = 1;
				tick = val4; //Petrifying time.
				if(val4 > 500) // not with WL_SIENNAEXECRATE
					tick = max(tick, 1000); //Min time
				calc_flag = 0; //Actual status changes take effect on petrified state.
				break;

			case SC_DPOISON:
				//Lose 10/15% of your life as long as it doesn't brings life below 25%
				if (st->hp > st->max_hp>>2) {
					int diff = st->max_hp*(bl->type==BL_PC?10:15)/100;
					if (st->hp - diff < st->max_hp>>2)
						diff = st->hp - (st->max_hp>>2);
					if( val2 && bl->type == BL_MOB ) {
						struct block_list* src2 = map->id2bl(val2);
						if( src2 )
							mob->log_damage((TBL_MOB*)bl,src2,diff);
					}
					status_zap(bl, diff, 0);
				}
				// fall through
			case SC_POISON:
				val3 = tick/1000; //Damage iterations
				if(val3 < 1) val3 = 1;
				tick_time = 1000; // [GodLesZ] tick time
				//val4: HP damage
				if (bl->type == BL_PC)
					val4 = (type == SC_DPOISON) ? 3 + st->max_hp/50 : 3 + st->max_hp*3/200;
				else
					val4 = (type == SC_DPOISON) ? 3 + st->max_hp/100 : 3 + st->max_hp/200;

				break;
			case SC_CONFUSION:
				clif->emotion(bl,E_WHAT);
				break;
			case SC_BLOODING:
				val4 = tick/10000;
				if (!val4) val4 = 1;
				tick_time = 10000; // [GodLesZ] tick time
				break;
			case SC_S_LIFEPOTION:
			case SC_L_LIFEPOTION:
				if( val1 == 0 ) return 0;
				// val1 = heal percent/amout
				// val2 = seconds between heals
				// val4 = total of heals
				if( val2 < 1 ) val2 = 1;
				if( (val4 = tick/(val2 * 1000)) < 1 )
					val4 = 1;
				tick_time = val2 * 1000; // [GodLesZ] tick time
				break;
			case SC_CASH_BOSS_ALARM:
				if( sd != NULL ) {
					struct mob_data *boss_md = map->getmob_boss(bl->m); // Search for Boss on this Map
					if( boss_md == NULL || boss_md->bl.prev == NULL ) {
						// No MVP on this map - MVP is dead
						clif->bossmapinfo(sd->fd, boss_md, 1);
						return 0; // No need to start SC
					}
					val1 = boss_md->bl.id;
					if( (val4 = tick/1000) < 1 )
						val4 = 1;
					tick_time = 1000; // [GodLesZ] tick time
				}
				break;
			case SC_HIDING:
				val2 = tick/1000;
				tick_time = 1000; // [GodLesZ] tick time
				val3 = 0; // unused, previously speed adjustment
				val4 = val1+3; //Seconds before SP substraction happen.
				break;
			case SC_CHASEWALK:
				val2 = tick>0?tick:10000; //Interval at which SP is drained.
				val3 = 35 - 5 * val1; //Speed adjustment.
				if (sc->data[SC_SOULLINK] && sc->data[SC_SOULLINK]->val2 == SL_ROGUE)
					val3 -= 40;
				val4 = 10+val1*2; //SP cost.
				if (map_flag_gvg(bl->m) || map->list[bl->m].flag.battleground) val4 *= 5;
				break;
			case SC_CLOAKING:
				if (!sd) //Monsters should be able to walk with no penalties. [Skotlex]
					val1 = 10;
				tick_time = val2 = tick>0?tick:60000; //SP consumption rate.
				tick = -1; // duration sent to the client should be infinite
				val3 = 0; // unused, previously walk speed adjustment
				//val4&1 signals the presence of a wall.
				//val4&2 makes cloak not end on normal attacks [Skotlex]
				//val4&4 makes cloak not end on using skills
				if (bl->type == BL_PC || (bl->type == BL_MOB && ((TBL_MOB*)bl)->special_state.clone) ) //Standard cloaking.
					val4 |= battle_config.pc_cloak_check_type&7;
				else
					val4 |= battle_config.monster_cloak_check_type&7;
				break;
			case SC_SIGHT: /* splash status */
			case SC_RUWACH:
			case SC_WZ_SIGHTBLASTER:
				val3 = skill->get_splash(val2, val1); //Val2 should bring the skill-id.
				val2 = tick/20;
				tick_time = 20; // [GodLesZ] tick time
				break;

				//Permanent effects.
			case SC_LEXAETERNA:
			case SC_MODECHANGE:
			case SC_WEIGHTOVER50:
			case SC_WEIGHTOVER90:
			case SC_BROKENWEAPON:
			case SC_BROKENARMOR:
			case SC_STORMKICK_READY:
			case SC_DOWNKICK_READY:
			case SC_COUNTERKICK_READY:
			case SC_TURNKICK_READY:
			case SC_DODGE_READY:
			case SC_PUSH_CART:
				tick = -1;
				break;

			case SC_AUTOGUARD:
				if( !(flag&SCFLAG_NOAVOID) ) {
					struct map_session_data *tsd;
					int i;
					for (i = val2 = 0; i < val1; i++) {
						int t = 5-(i>>1);
						val2 += (t < 0)? 1:t;
					}

					if( bl->type&(BL_PC|BL_MER) ) {
						if( sd ) {
							for( i = 0; i < MAX_PC_DEVOTION; i++ ) {
								if (sd->devotion[i] && (tsd = map->id2sd(sd->devotion[i])) != NULL)
									status->change_start(bl, &tsd->bl, type, 10000, val1, val2, 0, 0, tick, SCFLAG_ALL);
							}
						}
						else if (bl->type == BL_MER && ((TBL_MER*)bl)->devotion_flag && (tsd = ((TBL_MER*)bl)->master) != NULL) {
							status->change_start(bl, &tsd->bl, type, 10000, val1, val2, 0, 0, tick, SCFLAG_ALL);
						}
					}
				}
				break;

			case SC_DEFENDER:
				if (!(flag&SCFLAG_NOAVOID)) {
					val2 = 5 + 15*val1; //Damage reduction
					val3 = 0; // unused, previously speed adjustment
					val4 = 250 - 50*val1; //Aspd adjustment

					if (sd) {
						struct map_session_data *tsd;
						int i;
						for (i = 0; i < MAX_PC_DEVOTION; i++) {
							//See if there are devoted characters, and pass the status to them. [Skotlex]
							if (sd->devotion[i] && (tsd = map->id2sd(sd->devotion[i])) != NULL)
								status->change_start(bl, &tsd->bl,type,10000,val1,5+val1*5,val3,val4,tick,SCFLAG_NOAVOID);
						}
					}
				}
				break;

			case SC_TENSIONRELAX:
				if (sd) {
					pc_setsit(sd);
					clif->sitting(&sd->bl);
				}
				val2 = 12; //SP cost
				val4 = 10000; //Decrease at 10secs intervals.
				val3 = tick/val4;
				tick = -1; // duration sent to the client should be infinite
				tick_time = val4; // [GodLesZ] tick time
				break;
			case SC_PARRYING:
				val2 = 20 + val1*3; //Block Chance
				break;

			case SC_WINDWALK:
				val2 = (val1+1)/2; // Flee bonus is 1/1/2/2/3/3/4/4/5/5
				break;

			case SC_JOINTBEAT:
				if( val2&BREAK_NECK )
					sc_start2(src,bl,SC_BLOODING,100,val1,val3,skill->get_time2(status->sc2skill(type),val1));
				break;

			case SC_BERSERK:
				if( val3 == SC__BLOODYLUST )
					sc_start(src,bl,(sc_type)val3,100,val1,tick);
				if (!val3 && (!sc->data[SC_ENDURE] || !sc->data[SC_ENDURE]->val4))
					sc_start4(src, bl, SC_ENDURE, 100,10,0,0,2, tick);
				//HP healing is performing after the calc_status call.
				//Val2 holds HP penalty
				if (!val4) val4 = skill->get_time2(status->sc2skill(type),val1);
				if (!val4) val4 = 10000; //Val4 holds damage interval
				val3 = tick/val4; //val3 holds skill duration
				tick_time = val4; // [GodLesZ] tick time
				break;

			case SC_GOSPEL:
				if(val4 == BCT_SELF) {
					// self effect
					val2 = tick/10000;
					tick_time = 10000; // [GodLesZ] tick time
					status->change_clear_buffs(bl,3); //Remove buffs/debuffs
				}
				break;

			case SC_MARIONETTE_MASTER:
			{
				int stat;

				val3 = 0;
				val4 = 0;
				stat = ( sd ? sd->status.str : status->get_base_status(bl)->str ) / 2; val3 |= cap_value(stat,0,0xFF)<<16;
				stat = ( sd ? sd->status.agi : status->get_base_status(bl)->agi ) / 2; val3 |= cap_value(stat,0,0xFF)<<8;
				stat = ( sd ? sd->status.vit : status->get_base_status(bl)->vit ) / 2; val3 |= cap_value(stat,0,0xFF);
				stat = ( sd ? sd->status.int_: status->get_base_status(bl)->int_) / 2; val4 |= cap_value(stat,0,0xFF)<<16;
				stat = ( sd ? sd->status.dex : status->get_base_status(bl)->dex ) / 2; val4 |= cap_value(stat,0,0xFF)<<8;
				stat = ( sd ? sd->status.luk : status->get_base_status(bl)->luk ) / 2; val4 |= cap_value(stat,0,0xFF);
			}
				break;
			case SC_MARIONETTE:
			{
				int stat,max_stat;
				// fetch caster information
				struct block_list *pbl = map->id2bl(val1);
				struct status_change *psc = pbl ? status->get_sc(pbl) : NULL;
				struct status_change_entry *psce = psc ? psc->data[SC_MARIONETTE_MASTER] : NULL;
				// fetch target's stats
				struct status_data* tst = status->get_status_data(bl); // battle status

				if (!psce)
					return 0;

				val3 = 0;
				val4 = 0;
				max_stat = battle_config.max_parameter; //Cap to 99 (default)
				stat = (psce->val3 >>16)&0xFF; stat = min(stat, max_stat - tst->str ); val3 |= cap_value(stat,0,0xFF)<<16;
				stat = (psce->val3 >> 8)&0xFF; stat = min(stat, max_stat - tst->agi ); val3 |= cap_value(stat,0,0xFF)<<8;
				stat = (psce->val3 >> 0)&0xFF; stat = min(stat, max_stat - tst->vit ); val3 |= cap_value(stat,0,0xFF);
				stat = (psce->val4 >>16)&0xFF; stat = min(stat, max_stat - tst->int_); val4 |= cap_value(stat,0,0xFF)<<16;
				stat = (psce->val4 >> 8)&0xFF; stat = min(stat, max_stat - tst->dex ); val4 |= cap_value(stat,0,0xFF)<<8;
				stat = (psce->val4 >> 0)&0xFF; stat = min(stat, max_stat - tst->luk ); val4 |= cap_value(stat,0,0xFF);
			}
				break;
			case SC_SOULLINK:
				//1st Transcendent Spirit works similar to Marionette Control
				if(sd && val2 == SL_HIGH) {
					int stat,max_stat;
					// Fetch target's stats
					struct status_data* status2 = status->get_status_data(bl); // Battle status
					val3 = 0;
					val4 = 0;
					max_stat = (status->get_lv(bl)-10<50)?status->get_lv(bl)-10:50;
					stat = max(0, max_stat - status2->str ); val3 |= cap_value(stat,0,0xFF)<<16;
					stat = max(0, max_stat - status2->agi ); val3 |= cap_value(stat,0,0xFF)<<8;
					stat = max(0, max_stat - status2->vit ); val3 |= cap_value(stat,0,0xFF);
					stat = max(0, max_stat - status2->int_); val4 |= cap_value(stat,0,0xFF)<<16;
					stat = max(0, max_stat - status2->dex ); val4 |= cap_value(stat,0,0xFF)<<8;
					stat = max(0, max_stat - status2->luk ); val4 |= cap_value(stat,0,0xFF);
				}
				break;
			case SC_SWORDREJECT:
				val2 = 15*val1; //Reflect chance
				val3 = 3; //Reflections
				tick = -1;
				break;

			case SC_MEMORIZE:
				val2 = 5; //Memorized casts.
				tick = -1;
				break;

			case SC_GRAVITATION:
				val2 = 50*val1; //aspd reduction
				break;

			case SC_GDSKILL_REGENERATION:
				if (val1 == 1)
					val2 = 2;
				else
					val2 = val1; //HP Regerenation rate: 200% 200% 300%
				val3 = val1; //SP Regeneration Rate: 100% 200% 300%
				//if val4 comes set, this blocks regen rather than increase it.
				break;

			case SC_DEVOTION:
			{
				struct block_list *d_bl;
				struct status_change *d_sc;

				if ((d_bl = map->id2bl(val1)) && (d_sc = status->get_sc(d_bl)) != NULL && d_sc->count) {
					// Inherits Status From Source
					const enum sc_type types[] = { SC_AUTOGUARD, SC_DEFENDER, SC_REFLECTSHIELD, SC_ENDURE };
					int i = (map_flag_gvg(bl->m) || map->list[bl->m].flag.battleground)?2:3;
					while (i >= 0) {
						enum sc_type type2 = types[i];
						if (d_sc->data[type2]) {
							status->change_start(bl, bl, type2, 10000, d_sc->data[type2]->val1, 0, 0, 0,
							                     skill->get_time(status->sc2skill(type2),d_sc->data[type2]->val1),
							                     (type2 != SC_DEFENDER) ? SCFLAG_NOICON : SCFLAG_NONE);
						}
						i--;
					}
				}
				break;
			}

			case SC_COMA: //Coma. Sends a char to 1HP. If val2, do not zap sp
				if( val3 && bl->type == BL_MOB ) {
					struct block_list* src2 = map->id2bl(val3);
					if( src2 )
						mob->log_damage((TBL_MOB*)bl,src2,st->hp - 1);
				}
				status_zap(bl, st->hp-1, val2 ? 0 : st->sp);
				return 1;
				break;
			case SC_RG_CCONFINE_S:
			{
				struct block_list *src2 = val2 ? map->id2bl(val2) : NULL;
				struct status_change *sc2 = src ? status->get_sc(src2) : NULL;
				struct status_change_entry *sce2 = sc2 ? sc2->data[SC_RG_CCONFINE_M] : NULL;
				if (src2 && sc2) {
					if (!sce2) //Start lock on caster.
						sc_start4(src,src2,SC_RG_CCONFINE_M,100,val1,1,0,0,tick+1000);
					else { //Increase count of locked enemies and refresh time.
						(sce2->val2)++;
						timer->delete(sce2->timer, status->change_timer);
						sce2->timer = timer->add(timer->gettick()+tick+1000, status->change_timer, src2->id, SC_RG_CCONFINE_M);
					}
				} else //Status failed.
					return 0;
			}
				break;
			case SC_KAITE:
				val2 = 1+val1/5; //Number of bounces: 1 + skill_lv/5
				break;
			case SC_KAUPE:
				switch (val1) {
				case 3: //33*3 + 1 -> 100%
					val2++;
				case 1:
				case 2: //33, 66%
					val2 += 33*val1;
					val3 = 1; //Dodge 1 attack total.
					break;
				default: //Custom. For high level mob usage, higher level means more blocks. [Skotlex]
					val2 = 100;
					val3 = val1-2;
					break;
				}
				break;

			case SC_COMBOATTACK:
			{
				//val1: Skill ID
				//val2: When given, target (for autotargetting skills)
				//val3: When set, this combo time should NOT delay attack/movement
				//val3: If set to 2 this combo will delay ONLY attack
				//val3: TK: Last used kick
				//val4: TK: Combo time
				struct unit_data *ud = unit->bl2ud(bl);
				if( ud && (!val3 || val3 == 2) ) {
					tick += 300 * battle_config.combo_delay_rate/100;
					ud->attackabletime = timer->gettick()+tick;
					if( !val3 )
						unit->set_walkdelay(bl, timer->gettick(), tick, 1);
				}
				val3 = 0;
				val4 = tick;
				break;
			}
			case SC_EARTHSCROLL:
				val2 = 11-val1; //Chance to consume: 11-skill_lv%
				break;
			case SC_RUN:
			{
				//Store time at which you started running.
				int64 currenttick = timer->gettick();
				// Note: this int64 value is stored in two separate int32 variables (FIXME)
				val3 = (int)(currenttick&0x00000000ffffffffLL);
				val4 = (int)((currenttick&0xffffffff00000000LL)>>32);
			}
				tick = -1;
				break;
			case SC_KAAHI:
				val2 = 200*val1; //HP heal
				val3 = 5*val1; //SP cost
				val4 = INVALID_TIMER; //Kaahi Timer.
				break;
			case SC_BLESSING:
				if ((!undead_flag && st->race!=RC_DEMON) || bl->type == BL_PC)
					val2 = val1;
				else
					val2 = 0; //0 -> Half stat.
				break;
			case SC_TRICKDEAD:
				if (vd) vd->dead_sit = 1;
				tick = -1;
				break;
			case SC_CONCENTRATION:
				val2 = 2 + val1;
				if (sd) { //Store the card-bonus data that should not count in the %
					val3 = sd->param_bonus[1]; //Agi
					val4 = sd->param_bonus[4]; //Dex
				} else {
					val3 = val4 = 0;
				}
				break;
			case SC_OVERTHRUSTMAX:
				val2 = 20*val1; //Power increase
				break;
			case SC_OVERTHRUST:
				//val2 holds if it was casted on self, or is bonus received from others
				val3 = 5*val1; //Power increase
				if(sd && pc->checkskill(sd,BS_HILTBINDING)>0)
					tick += tick / 10;
				break;
			case SC_ADRENALINE2:
			case SC_ADRENALINE:
				val3 = (val2) ? 300 : 200; // aspd increase
			case SC_WEAPONPERFECT:
				if(sd && pc->checkskill(sd,BS_HILTBINDING)>0)
					tick += tick / 10;
				break;
			case SC_LKCONCENTRATION:
				val2 = 5*val1; //Batk/Watk Increase
				val3 = 10*val1; //Hit Increase
				val4 = 5*val1; //Def reduction
				sc_start(src, bl, SC_ENDURE, 100, 1, tick); //Endure effect
				break;
			case SC_ANGELUS:
				val2 = 5*val1; //def increase
				break;
			case SC_IMPOSITIO:
				val2 = 5*val1; //watk increase
				break;
			case SC_MELTDOWN:
				val2 = 100*val1; //Chance to break weapon
				val3 = 70*val1; //Change to break armor
				break;
			case SC_TRUESIGHT:
				val2 = 10*val1; //Critical increase
				val3 = 3*val1; //Hit increase
				break;
			case SC_SUN_COMFORT:
				val2 = (status->get_lv(bl) + st->dex + st->luk)/2; //def increase
				break;
			case SC_MOON_COMFORT:
				val2 = (status->get_lv(bl) + st->dex + st->luk)/10; //flee increase
				break;
			case SC_STAR_COMFORT:
				val2 = (status->get_lv(bl) + st->dex + st->luk); //Aspd increase
				break;
			case SC_QUAGMIRE:
				val2 = (sd?5:10)*val1; //Agi/Dex decrease.
				break;

				// gs_something1 [Vicious]
			case SC_GS_GATLINGFEVER:
				val2 = 20*val1; //Aspd increase
				val4 = 5*val1; //Flee decrease
	#ifndef RENEWAL
				val3 = 20+10*val1; //Batk increase
	#endif
				break;

			case SC_FLING:
				if (bl->type == BL_PC)
					val2 = 0; //No armor reduction to players.
				else
					val2 = 5*val1; //Def reduction
				val3 = 5*val1; //Def2 reduction
				break;
			case SC_PROVOKE:
				//val2 signals autoprovoke.
				val3 = 2+3*val1; //Atk increase
				val4 = 5+5*val1; //Def reduction.
				break;
			case SC_HLIF_AVOID:
				//val2 = 10*val1; //Speed change rate.
				break;
			case SC_HAMI_DEFENCE:
				val2 = 2*val1; //Def bonus
				break;
			case SC_HAMI_BLOODLUST:
				val2 = 20+10*val1; //Atk rate change.
				val3 = 3*val1; //Leech chance
				val4 = 20; //Leech percent
				break;
			case SC_HLIF_FLEET:
				val2 = 30*val1; //Aspd change
				val3 = 5+5*val1; //bAtk/wAtk rate change
				break;
			case SC_MINDBREAKER:
				val2 = 20*val1; //matk increase.
				val3 = 12*val1; //mdef2 reduction.
				break;
			case SC_SKA:
				val2 = tick/1000;
				val3 = rnd()%100; //Def changes randomly every second...
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_JAILED:
				// val1 is duration in minutes. Use INT_MAX to specify 'unlimited' time.
				// When first called:
				// val2 Jail map_index
				// val3 x
				// val4 y
				// When renewing status' information
				// val3 Return map_index
				// val4 return coordinates
				tick = val1>0?1000:250;
				if (sd)
				{
					if (sd->mapindex != val2)
					{
						int pos = (bl->x&0xFFFF)|(bl->y<<16); /// Current Coordinates
						int map_index = sd->mapindex; /// Current Map
						//1. Place in Jail (val2 -> Jail Map, val3 -> x, val4 -> y
						pc->setpos(sd,(unsigned short)val2,val3,val4, CLR_TELEPORT);
						//2. Set restore point (val3 -> return map, val4 return coords
						val3 = map_index;
						val4 = pos;
					} else if (!val3
						|| val3 == sd->mapindex
						|| !sd->sc.data[SC_JAILED] // If player is being jailed and is already in jail (issue: 8206)
					) { //Use save point.
						val3 = sd->status.save_point.map;
						val4 = (sd->status.save_point.x&0xFFFF)
							|(sd->status.save_point.y<<16);
					}
				}
				break;
			case SC_NJ_UTSUSEMI:
				val2=(val1+1)/2; // number of hits blocked
				val3=skill->get_blewcount(NJ_UTSUSEMI, val1); //knockback value.
				break;
			case SC_NJ_BUNSINJYUTSU:
				val2=(val1+1)/2; // number of hits blocked
				break;
			case SC_HLIF_CHANGE:
				val2= 30*val1; //Vit increase
				val3= 20*val1; //Int increase
				break;
			case SC_SWOO:
				if(st->mode&MD_BOSS)
					tick /= 5; //TODO: Reduce skill's duration. But for how long?
				break;
			case SC_SPIDERWEB:
				if( bl->type == BL_PC )
					tick /= 2;
				break;
			case SC_ARMOR:
				//NPC_DEFENDER:
				val2 = 80; //Damage reduction
				//Attack requirements to be blocked:
				val3 = BF_LONG; //Range
				val4 = BF_WEAPON|BF_MISC; //Type
				break;
			case SC_ENCHANTARMS:
				//end previous enchants
				skill->enchant_elemental_end(bl,type);
				//Make sure the received element is valid.
				if (val2 >= ELE_MAX)
					val2 = val2%ELE_MAX;
				else if (val2 < 0)
					val2 = rnd()%ELE_MAX;
				break;
			case SC_CRITICALWOUND:
				val2 = 20*val1; //Heal effectiveness decrease
				break;
			case SC_MAGICMIRROR:
			case SC_SLOWCAST:
				val2 = 20*val1; //Magic reflection/cast rate
				break;

			case SC_STONESKIN:
				if (val2 == NPC_ANTIMAGIC) {
					//Boost mdef
					val2 =-20;
					val3 = 20;
				} else {
					//Boost def
					val2 = 20;
					val3 =-20;
				}
				val2*=val1; //20% per level
				val3*=val1;
				break;
			case SC_CASH_PLUSEXP:
			case SC_CASH_PLUSONLYJOBEXP:
				if (val1 < 0)
					val1 = 0;
				break;
			case SC_PLUSAVOIDVALUE:
			case SC_CRITICALPERCENT:
				val2 = val1*10; //Actual boost (since 100% = 1000)
				break;
			case SC_SUFFRAGIUM:
				val2 = 15 * val1; //Speed cast decrease
				break;
			case SC_HEALPLUS:
				if (val1 < 1)
					val1 = 1;
				break;
			case SC_ILLUSION:
				val2 = 5+val1; //Factor by which displayed damage is increased by
				break;
			case SC_DOUBLECASTING:
				val2 = 30+10*val1; //Trigger rate
				break;
			case SC_KAIZEL:
				val2 = 10*val1; //% of life to be revived with
				break;
				// case SC_ARMORPROPERTY:
				// case SC_ARMOR_RESIST:
				// Mod your resistance against elements:
				// val1 = water | val2 = earth | val3 = fire | val4 = wind
				// break;
				//case ????:
				//Place here SCs that have no SCB_* data, no skill associated, no ICON
				//associated, and yet are not wrong/unknown. [Skotlex]
				//break;

			case SC_MER_FLEE:
			case SC_MER_ATK:
			case SC_MER_HIT:
				val2 = 15 * val1;
				break;
			case SC_MER_HP:
			case SC_MER_SP:
				val2 = 5 * val1;
				break;
			case SC_REBIRTH:
				val2 = 20*val1; //% of life to be revived with
				break;

			case SC_MANU_DEF:
			case SC_MANU_ATK:
			case SC_MANU_MATK:
				val2 = 1; // Manuk group
				break;
			case SC_SPL_DEF:
			case SC_SPL_ATK:
			case SC_SPL_MATK:
				val2 = 2; // Splendide group
				break;
				/**
				* General
				**/
			case SC_FEAR:
				val2 = 2;
				val4 = tick / 1000;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_BURNING:
				val4 = tick / 3000; // Total Ticks to Burn!!
				tick_time = 3000; // [GodLesZ] tick time
				break;
				/**
				* Rune Knight
				**/
			case SC_DEATHBOUND:
				val2 = 500 + 100 * val1;
				break;
			case SC_STONEHARDSKIN:
				if( sd )
					val1 = sd->status.job_level * pc->checkskill(sd, RK_RUNEMASTERY) / 4; //DEF/MDEF Increase
				break;
			case SC_ABUNDANCE:
				val4 = tick / 10000;
				tick_time = 10000; // [GodLesZ] tick time
				break;
				/**
				* Arch Bishop
				**/
			case SC_RENOVATIO:
				val4 = tick / 5000;
				tick_time = 5000;
				break;
			case SC_SECRAMENT:
				val2 = 10 * val1;
				break;
			case SC_VENOMIMPRESS:
				val2 = 10 * val1;
				break;
			case SC_WEAPONBLOCKING:
				val2 = 10 + 2 * val1; // Chance
				val4 = tick / 5000;
				tick_time = 5000; // [GodLesZ] tick time
				break;
			case SC_TOXIN:
				val4 = tick / 10000;
				tick_time = 10000; // [GodLesZ] tick time
				break;
			case SC_MAGICMUSHROOM:
				val4 = tick / 4000;
				tick_time = 4000; // [GodLesZ] tick time
				break;
			case SC_PYREXIA:
				status->change_start(src, bl,SC_BLIND,10000,val1,0,0,0,30000,SCFLAG_NOAVOID|SCFLAG_FIXEDTICK|SCFLAG_FIXEDRATE); // Blind status that last for 30 seconds
				val4 = tick / 3000;
				tick_time = 3000; // [GodLesZ] tick time
				break;
			case SC_LEECHESEND:
				val4 = tick / 1000;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_OBLIVIONCURSE:
				val4 = tick / 3000;
				tick_time = 3000; // [GodLesZ] tick time
				break;
			case SC_CLOAKINGEXCEED:
				val2 = ( val1 + 1 ) / 2; // Hits
				val3 = 90 + val1 * 10; // Walk speed
				if (bl->type == BL_PC)
					val4 |= battle_config.pc_cloak_check_type&7;
				else
					val4 |= battle_config.monster_cloak_check_type&7;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_HALLUCINATIONWALK:
				val2 = 50 * val1; // Evasion rate of physical attacks. Flee
				val3 = 10 * val1; // Evasion rate of magical attacks.
				break;
			case SC_WHITEIMPRISON:
				status_change_end(bl, SC_BURNING, INVALID_TIMER);
				status_change_end(bl, SC_FROSTMISTY, INVALID_TIMER);
				status_change_end(bl, SC_FREEZE, INVALID_TIMER);
				status_change_end(bl, SC_STONE, INVALID_TIMER);
				break;
			case SC_MARSHOFABYSS:
				val2 = 6 * val1;
				if( sd ) // half on players
					val2 >>= 1;
				break;
			case SC_FROSTMISTY:
				status_change_end(bl, SC_BURNING, INVALID_TIMER);
				break;
			case SC_READING_SB:
				// val2 = sp reduction per second
				tick_time = 10000; // [GodLesZ] tick time
				break;
			case SC_SUMMON1:
			case SC_SUMMON2:
			case SC_SUMMON3:
			case SC_SUMMON4:
			case SC_SUMMON5:
				val4 = tick / 1000;
				if( val4 < 1 )
					val4 = 1;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_SHAPESHIFT:
				switch( val1 )
				{
				case 1: val2 = ELE_FIRE; break;
				case 2: val2 = ELE_EARTH; break;
				case 3: val2 = ELE_WIND; break;
				case 4: val2 = ELE_WATER; break;
				}
				break;
			case SC_STEALTHFIELD_MASTER:
				val4 = tick / 1000;
				tick_time = 2000 + (1000 * val1);
				break;
			case SC_ELECTRICSHOCKER:
			case SC_COLD:
			case SC_MEIKYOUSISUI:
				val4 = tick / 1000;
				if( val4 < 1 )
					val4 = 1;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_CAMOUFLAGE:
				val4 = tick/1000;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_WUGDASH:
			{
				//Store time at which you started running.
				int64 currenttick = timer->gettick();
				// Note: this int64 value is stored in two separate int32 variables (FIXME)
				val3 = (int)(currenttick&0x00000000ffffffffLL);
				val4 = (int)((currenttick&0xffffffff00000000LL)>>32);
			}
				tick = -1;
				break;
			case SC__REPRODUCE:
				val4 = tick / 1000;
				tick_time = 1000;
				break;
			case SC__SHADOWFORM: {
				struct map_session_data * s_sd = map->id2sd(val2);
				if( s_sd )
					s_sd->shadowform_id = bl->id;
				val4 = tick / 1000;
				tick_time = 1000; // [GodLesZ] tick time
								 }
				break;
			case SC__STRIPACCESSARY:
				if (!sd)
					val2 = 20;
				break;
			case SC__INVISIBILITY:
				val2 = 50 - 10 * val1; // ASPD
				val3 = 200 * val1; // CRITICAL
				val4 = tick / 1000;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC__ENERVATION:
				val2 = 20 + 10 * val1; // ATK Reduction
				if (sd) {
					pc->delspiritball(sd, sd->spiritball, 0);
					pc->del_charm(sd, sd->charm_count, sd->charm_type);
				}
				break;
			case SC__GROOMY:
				val2 = 20 + 10 * val1; //ASPD. Need to confirm if Movement Speed reduction is the same. [Jobbie]
				val3 = 20 * val1; //HIT
				if( sd ) { // Removes Animals
					if (pc_isridingpeco(sd))
						pc->setridingpeco(sd, false);
					if (pc_isridingdragon(sd))
						pc->setridingdragon(sd, 0);
					if (pc_iswug(sd))
						pc->setoption(sd, sd->sc.option&~OPTION_WUG);
					if (pc_isridingwug(sd))
						pc->setridingwug(sd, false);
					if (pc_isfalcon(sd))
						pc->setfalcon(sd, false);
					if (sd->status.pet_id > 0)
						pet->menu(sd, 3);
					if (homun_alive(sd->hd))
						homun->vaporize(sd,HOM_ST_REST);
					if (sd->md)
						mercenary->delete(sd->md,3);
				}
				break;
			case SC__LAZINESS:
				val2 = 10 + 10 * val1; // Cast reduction
				val3 = 10 * val1; // Flee Reduction
				break;
			case SC__UNLUCKY:
				val2 = 10 * val1; // Crit and Flee2 Reduction
				break;
			case SC__WEAKNESS:
				val2 = 10 * val1;
				// bypasses coating protection and MADO
				sc_start(src, bl,SC_NOEQUIPWEAPON,100,val1,tick);
				sc_start(src, bl,SC_NOEQUIPSHIELD,100,val1,tick);
				break;
			case SC_GN_CARTBOOST:
				if( val1 < 3 )
					val2 = 50;
				else if( val1 < 5 )
					val2 = 75;
				else
					val2 = 100;
				break;
			case SC_PROPERTYWALK:
				val3 = 0;
				break;
			case SC_WARMER:
				status_change_end(bl, SC_FREEZE, INVALID_TIMER);
				status_change_end(bl, SC_FROSTMISTY, INVALID_TIMER);
				status_change_end(bl, SC_COLD, INVALID_TIMER);
				break;
			case SC_STRIKING:
				val1 = 6 - val1;//spcost = 6 - level (lvl1:5 ... lvl 5: 1)
				val4 = tick / 1000;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_BLOOD_SUCKER:
			{
				struct block_list *src2 = map->id2bl(val2);
				val3 = 1;
				if(src2)
					val3 = 200 + 100 * val1 + status_get_int(src2);
				val4 = tick / 1000;
				tick_time = 1000; // [GodLesZ] tick time
			}
				break;
			case SC_SWING:
				val3 = 5 * val1 + val2;//Movement Speed And ASPD Increase
				break;
			case SC_SYMPHONY_LOVE:
				val2 = 12 * val1 + val2 + (sd ? sd->status.job_level : 70) / 4;//MDEF Increase In %
				break;
			case SC_MOONLIT_SERENADE:
			case SC_RUSH_WINDMILL:
				val2 = 6 * val1 + val2 + (sd ? sd->status.job_level : 70) / 5;
				break;
			case SC_ECHOSONG:
				val3 = 6 * val1 + val2 + (sd ? sd->status.job_level : 70) / 4;//DEF Increase In %
				break;
			case SC_HARMONIZE:
				val2 = 5 + 5 * val1;
				break;
			case SC_SIREN:
				val4 = tick / 2000;
				tick_time = 2000; // [GodLesZ] tick time
				break;
			case SC_DEEP_SLEEP:
				val4 = tick / 2000;
				tick_time = 2000; // [GodLesZ] tick time
				break;
			case SC_SIRCLEOFNATURE:
				val2 = 40 * val1;//HP recovery
				val3 = 4 * val1;//SP drain
				val4 = tick / 1000;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_SONG_OF_MANA:
				val3 = 10 + 5 * val2;
				val4 = tick/5000;
				tick_time = 5000; // [GodLesZ] tick time
				break;
			case SC_SATURDAY_NIGHT_FEVER:
				/*val2 = 12000 - 2000 * val1;//HP/SP Drain Timer
				if ( val2 < 1000 )
					val2 = 1000;//Added to prevent val3 from dividing by 0 when using level 6 or higher through commands. [Rytech]
				val3 = tick/val2;*/
				val3 = tick / 3000;
				tick_time = 3000;// [GodLesZ] tick time
				break;
			case SC_GLOOMYDAY:
				if ( !val2 ) {
					val2 = (val4 > 0 ? max(15, rnd()%(val4*5)) : 0) + val1 * 10;
				}
				if ( rnd()%10000 < val1*100 ) { // 1% per SkillLv chance
					if ( !val3 )
						val3 = 50;
					if( sd ) {
						if (pc_isridingpeco(sd))
							pc->setridingpeco(sd, false);
						if (pc_isridingdragon(sd))
							pc->setridingdragon(sd, false);
					}
				}
				break;
			case SC_SITDOWN_FORCE:
			case SC_BANANA_BOMB_SITDOWN_POSTDELAY:
				if( sd && !pc_issit(sd) )
				{
					pc_setsit(sd);
					skill->sit(sd,1);
					clif->sitting(bl);
				}
				break;
			case SC_DANCE_WITH_WUG:
				val3 = 5 + 5 * val2;//ASPD Increase
				val4 = 20 + 10 * val2;//Fixed Cast Time Reduction
				break;
			case SC_LERADS_DEW:
				val3 = 200 * val1 + 300 * val2;//MaxHP Increase
				break;
			case SC_MELODYOFSINK:
				val3 = val1 * (2 + val2);//INT Reduction. Formula Includes Caster And 2nd Performer.
				val4 = tick/1000;
				tick_time = 1000;
				break;
			case SC_BEYOND_OF_WARCRY:
				val3 = val1 * (2 + val2);//STR And Crit Reduction. Formula Includes Caster And 2nd Performer.
				val4 = 4 * val1 + 4 * val2;//MaxHP Reduction
				break;
			case SC_UNLIMITED_HUMMING_VOICE:
				{
					struct unit_data *ud = unit->bl2ud(bl);
					if( ud == NULL ) return 0;
					ud->state.skillcastcancel = 0;
					val3 = 15 - (3 * val2);//Increased SP Cost.
				}
				break;
			case SC_LG_REFLECTDAMAGE:
				val2 = 15 + 5 * val1;
				val3 = 25 + 5 * val1; //Number of Reflects
				val4 = tick/1000;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_FORCEOFVANGUARD:
				val2 = 8 + 12 * val1; // Chance
				val3 = 5 + 2 * val1; // Max rage counters
				tick = -1; //endless duration in the client
				break;
			case SC_EXEEDBREAK:
				if( sd ){
					short index = sd->equip_index[EQI_HAND_R];
					val1 = 15 * (sd->status.job_level + val1 * 10);
					if( index >= 0 && sd->inventory_data[index] && sd->inventory_data[index]->type == IT_WEAPON )
						val1 += (sd->inventory_data[index]->weight / 10 * sd->inventory_data[index]->wlv) * status->get_lv(bl) / 100;
				}
				break;
			case SC_PRESTIGE:
				val2 = (st->int_ + st->luk) * val1 / 20;// Chance to evade magic damage.
				val2 = val2 * status->get_lv(bl) / 200;
				val2 += val1;
				val1 *= 15; // Defence added
				if( sd )
					val1 += 10 * pc->checkskill(sd,CR_DEFENDER);
				val1 = val1 *  status->get_lv(bl) / 100;
				break;
			case SC_BANDING:
				tick_time = 5000; // [GodLesZ] tick time
				break;
			case SC_MAGNETICFIELD:
				val3 = tick / 1000;
				tick_time = 1000; // [GodLesZ] tick time
				break;
			case SC_INSPIRATION:
				if( sd ) {
					val2 = 40 * val1 + 3 * sd->status.job_level;// ATK bonus
					val3 = sd->status.base_level / 10 + sd->status.job_level / 5;// All stat bonus
				}
				val4 = tick / 5000;
				tick_time = 5000; // [GodLesZ] tick time
				status->change_clear_buffs(bl,3); //Remove buffs/debuffs
				break;
			case SC_CRESCENTELBOW:
				val2 = (sd ? sd->status.job_level : 2) / 2 + 50 + 5 * val1;
				break;
			case SC_LIGHTNINGWALK: //  [(Job Level / 2) + (40 + 5 * Skill Level)] %
				val1 = (sd?sd->status.job_level:2)/2 + 40 + 5 * val1;
				break;
			case SC_RAISINGDRAGON:
				val3 = tick / 5000;
				tick_time = 5000; // [GodLesZ] tick time
				break;
			case SC_GENTLETOUCH_CHANGE:
			{// take note there is no def increase as skill desc says. [malufett]
				struct block_list * src2;
				val3 = st->agi * val1 / 60; // ASPD increase: [(Target AGI x Skill Level) / 60] %
				if( (src2 = map->id2bl(val2)) ){
					val4 = ( 200/(status_get_int(src2)?status_get_int(src2):1) ) * val1;// MDEF decrease: MDEF [(200 / Caster INT) x Skill Level]
					val2 = ( status_get_dex(src2)/4 + status_get_str(src2)/2 ) * val1 / 5; // ATK increase: ATK [{(Caster DEX / 4) + (Caster STR / 2)} x Skill Level / 5]
				}
			}
				break;
			case SC_GENTLETOUCH_REVITALIZE:
				if(val2 < 0)
					val2 = 0;
				else
					val2 = val2 / 4 * val1; // STAT DEF increase: [(Caster VIT / 4) x Skill Level]
				break;
			case SC_GENTLETOUCH_ENERGYGAIN:
				val2 = 10 + 5 * val1;
				break;
			case SC_PYROTECHNIC_OPTION:
				val2 = 60;
				break;
			case SC_HEATER_OPTION:
				val2 = 120; // Watk. TODO: Renewal (Atk2)
				val3 = (sd ? sd->status.job_level : 0); // % Increase damage.
				val4 = 3; // Change into fire element.
				break;
			case SC_TROPIC_OPTION:
				val2 = 180; // Watk. TODO: Renewal (Atk2)
				val3 = MG_FIREBOLT;
				break;
			case SC_AQUAPLAY_OPTION:
				val2 = 40;
				break;
			case SC_COOLER_OPTION:
				val2 = 80; // Bonus Matk
				val3 = (sd ? sd->status.job_level : 0); // % Freezing chance
				val4 = 1; // Change into water elemet
				break;
			case SC_CHILLY_AIR_OPTION:
				val2 = 120; // Matk. TODO: Renewal (Matk1)
				val3 = MG_COLDBOLT;
				break;
			case SC_WIND_STEP_OPTION:
				val2 = 50; // % Increase speed and flee.
				break;
			case SC_BLAST_OPTION:
				val2 = (sd ? sd->status.job_level : 0); // % Increase damage
				val3 = ELE_WIND;
				break;
			case SC_WILD_STORM_OPTION:
				val2 = MG_LIGHTNINGBOLT;
				break;
			case SC_PETROLOGY_OPTION:
				val2 = 5;
				val3 = 50;
				break;
			case SC_SOLID_SKIN_OPTION:
				val2 = 33; // % Increase DEF
				break;
			case SC_CURSED_SOIL_OPTION:
				val2 = 10;
				val3 = (sd ? sd->status.job_level : 0); // % Increase Damage
				val4 = 2;
				break;
			case SC_UPHEAVAL_OPTION:
				val2 = WZ_EARTHSPIKE;
				val3 = 15; // Bonus MaxHP
				break;
			case SC_CIRCLE_OF_FIRE_OPTION:
				val2 = 300;
				break;
			case SC_FIRE_CLOAK_OPTION:
			case SC_WATER_DROP_OPTION:
			case SC_WIND_CURTAIN_OPTION:
			case SC_STONE_SHIELD_OPTION:
				val2 = 100; // Elemental modifier.
				break;
			case SC_TROPIC:
			case SC_CHILLY_AIR:
			case SC_WILD_STORM:
			case SC_UPHEAVAL:
				val2 += 10;
			case SC_HEATER:
			case SC_COOLER:
			case SC_BLAST:
			case SC_CURSED_SOIL:
				val2 += 10;
			case SC_PYROTECHNIC:
			case SC_AQUAPLAY:
			case SC_GUST:
			case SC_PETROLOGY:
				val2 += 5;
				val3 += 9000;
			case SC_CIRCLE_OF_FIRE:
			case SC_WATER_SCREEN:
			case SC_WIND_STEP:
			case SC_SOLID_SKIN:
			case SC_FIRE_CLOAK:
			case SC_WATER_DROP:
			case SC_WIND_CURTAIN:
			case SC_STONE_SHIELD:
				val2 += 5;
				val3 += 1000;
				val4 = tick;
				tick_time = val3;
				break;
			case SC_WATER_BARRIER:
				val3 = 20; // Reductions. Atk2, Flee1
				break;
			case SC_ZEPHYR:
				val2 = 25; // Flee.
				break;
			case SC_TIDAL_WEAPON:
				val2 = 20; // Increase Elemental's attack.
				break;
			case SC_ROCK_CRUSHER:
			case SC_ROCK_CRUSHER_ATK:
			case SC_POWER_OF_GAIA:
				val2 = 33;
				break;
			case SC_MELON_BOMB:
			case SC_BANANA_BOMB:
				val1 = 15;
				break;
			case SC_STOMACHACHE:
				val2 = 8; // SP consume.
				val4 = tick / 10000;
				tick_time = 10000; // [GodLesZ] tick time
				break;
			case SC_KYOUGAKU: {
				int min = val1*2;
				int max = val1*3;
				val3 = rnd()%(max-min)+min;
					val2 = val1;
					val1 = 1002; // Monster ID
				}
				break;
			case SC_KAGEMUSYA:
				val3 = val1 * 2;
			case SC_IZAYOI:
				val2 = tick/1000;
				tick_time = 1000;
				break;
			case SC_ZANGETSU:
				val2 = val4 = status->get_lv(bl) / 3 + 20 * val1;
				val3 = status->get_lv(bl) / 2 + 30 * val1;
				val2 = (!(status_get_hp(bl)%2) ? val2 : -val3);
				val3 = (!(status_get_sp(bl)%2) ? val4 : -val3);
				break;
			case SC_GENSOU:

#define PER( a, lvl ) do { \
	int temp__ = (a); \
	if( temp__ <= 15 ) (lvl) = 1; \
	else if( temp__ <= 30 ) (lvl) = 2; \
	else if( temp__ <= 50 ) (lvl) = 3; \
	else if( temp__ <= 75 ) (lvl) = 4; \
	else (lvl) = 5; \
} while(0)

			{
				int hp = status_get_hp(bl), sp = status_get_sp(bl), lv = 5;

				if (sp < 1) sp = 1;
				if (hp < 1) hp = 1;

				if( rnd()%100 > (25 + 10 * val1) - status_get_int(bl) / 2)
					return 0;

				PER( 100 / (status_get_max_hp(bl) / hp), lv );
				status->heal(bl, (!(hp%2) ? (6-lv) *4 / 100 : -(lv*4) / 100), 0, 1);

				PER( 100 / (status_get_max_sp(bl) / sp), lv );
				status->heal(bl, 0,(!(sp%2) ? (6-lv) *3 / 100 : -(lv*3) / 100), 1);
			}
#undef PER
				break;
			case SC_ANGRIFFS_MODUS:
				val2 = 50 + 20 * val1; //atk bonus
				val3 = 40 + 20 * val1; // Flee reduction.
				val4 = tick/1000; // hp/sp reduction timer
				tick_time = 1000;
				break;
			case SC_NEUTRALBARRIER:
				tick_time = tick;
				tick = -1;
				break;
			case SC_GOLDENE_FERSE:
				val2 = 10 + 10*val1; //max hp bonus
				val3 = 6 + 4 * val1; // Aspd Bonus
				val4 = 2 + 2 * val1; // Chance of holy attack
				break;
			case SC_OVERED_BOOST:
				val2 = 300 + 40*val1; //flee bonus
				val3 = 179 + 2*val1; //aspd bonus
				break;
			case SC_GRANITIC_ARMOR:
				val2 = 2*val1; //dmg reduction
				val3 = 6*val1; //dmg on status end
				break;
			case SC_MAGMA_FLOW:
				val2 = 3*val1; //activation chance
				break;
			case SC_PYROCLASTIC:
				val2 += 10*val1; //atk bonus
				break;
			case SC_NEEDLE_OF_PARALYZE: //[Lighta] need real info
				val2 = 2*val1; //def reduction
				val3 = 500*val1; //varcast augmentation
				break;
			case SC_PAIN_KILLER: //[Lighta] need real info
				val2 = 2*val1; //aspd reduction %
				val3 = 2*val1; //dmg reduction %
				if(sc->data[SC_NEEDLE_OF_PARALYZE])
					sc_start(src, bl, SC_ENDURE, 100, val1, tick); //start endure for same duration
				break;
			case SC_STYLE_CHANGE: //[Lighta] need real info
				tick = -1;
				if(val2 == MH_MD_FIGHTING) val2 = MH_MD_GRAPPLING;
				else val2 = MH_MD_FIGHTING;
				break;
			case SC_FULL_THROTTLE:
				status_percent_heal(bl,100,0);
				val2 = 7 - val1;
				tick_time = 1000;
				val4 = tick / tick_time;
				break;
			case SC_KINGS_GRACE:
				val2 = 3 + val1;
				tick_time = 1000;
				val4 = tick / tick_time;
				break;
			case SC_TELEKINESIS_INTENSE:
				val2 = 10 * val1;
				val3 = 40 * val1;
				break;
			case SC_OFFERTORIUM:
				val2 = 30 * val1;
				break;
			case SC_FRIGG_SONG:
				val2 = 5 * val1;
				val3 = (20 * val1) + 80;
				tick_time = 1000;
				val4 = tick / tick_time;
				break;
			case SC_DARKCROW:
				val2 = 30 * val1;
				break;
			case SC_MONSTER_TRANSFORM:
				if( !mob->db_checkid(val1) )
					val1 = 1002; // default poring
				break;
			case SC_ALL_RIDING:
				tick = -1;
				break;
			case SC_FLASHCOMBO:
				/**
				 * val1 = <IN>skill_id
				 * val2 = <OUT>attack addition
				 **/
				val2 = 20+(20*val1);
				break;
			default:
				if (calc_flag == SCB_NONE && status->dbs->SkillChangeTable[type] == 0 && status->dbs->IconChangeTable[type] == 0) {
					//Status change with no calc, no icon, and no skill associated...?
					ShowError("UnknownStatusChange [%d]\n", type);
					return 0;
				}
		}
