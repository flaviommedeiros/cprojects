switch(skill_id) {
		case PR_BENEDICTIO:
			r = skill->get_splash(skill_id, skill_lv);
			skill->area_temp[1] = src->id;
			map->foreachinarea(skill->area_sub,
			                   src->m, x-r, y-r, x+r, y+r, BL_PC,
			                   src, skill_id, skill_lv, tick, flag|BCT_ALL|1,
			                   skill->castend_nodamage_id);
			map->foreachinarea(skill->area_sub,
			                   src->m, x-r, y-r, x+r, y+r, BL_CHAR,
			                   src, skill_id, skill_lv, tick, flag|BCT_ENEMY|1,
			                   skill->castend_damage_id);
			break;

		case BS_HAMMERFALL:
			r = skill->get_splash(skill_id, skill_lv);
			map->foreachinarea(skill->area_sub,
			                   src->m, x-r, y-r, x+r, y+r, BL_CHAR,
			                   src, skill_id, skill_lv, tick, flag|BCT_ENEMY|2,
			                   skill->castend_nodamage_id);
			break;

		case HT_DETECTING:
			r = skill->get_splash(skill_id, skill_lv);
			map->foreachinarea(status->change_timer_sub,
			                   src->m, x-r, y-r, x+r,y+r,BL_CHAR,
			                   src,NULL,SC_SIGHT,tick);
			if(battle_config.traps_setting&1)
			map->foreachinarea(skill_reveal_trap,
			                   src->m, x-r, y-r, x+r, y+r, BL_SKILL);
			break;

		case SR_RIDEINLIGHTNING:
			r = skill->get_splash(skill_id, skill_lv);
			map->foreachinarea(skill->area_sub, src->m, x-r, y-r, x+r, y+r, BL_CHAR,
			                   src, skill_id, skill_lv, tick, flag|BCT_ENEMY|1, skill->castend_damage_id);
			break;

		case SA_VOLCANO:
		case SA_DELUGE:
		case SA_VIOLENTGALE:
			//Does not consumes if the skill is already active. [Skotlex]
			if ((sg= skill->locate_element_field(src)) != NULL && ( sg->skill_id == SA_VOLCANO || sg->skill_id == SA_DELUGE || sg->skill_id == SA_VIOLENTGALE ))
			{
				if (sg->limit - DIFF_TICK(timer->gettick(), sg->tick) > 0) {
					skill->unitsetting(src,skill_id,skill_lv,x,y,0);
					return 0; // not to consume items
				} else
					sg->limit = 0; //Disable it.
			}
			skill->unitsetting(src,skill_id,skill_lv,x,y,0);
			break;

		case SC_CHAOSPANIC:
		case SC_MAELSTROM:
			if (sd && map->foreachinarea(&check_npc_chaospanic,src->m, x-3, y-3, x+3, y+3, BL_NPC) > 0 ) {
				clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
				break;
			}

		case MG_SAFETYWALL:
		{
			int alive = 1;
			if ( map->foreachincell(skill->cell_overlap, src->m, x, y, BL_SKILL, skill_id, &alive, src) ) {
				skill->unitsetting(src, skill_id, skill_lv, x, y, 0);
				return 0; // Don't consume gems if cast on LP
			}
		}
		case MG_FIREWALL:
		case MG_THUNDERSTORM:

		case AL_PNEUMA:
		case WZ_FIREPILLAR:
		case WZ_QUAGMIRE:
		case WZ_VERMILION:
		case WZ_STORMGUST:
		case WZ_HEAVENDRIVE:
		case PR_SANCTUARY:
		case PR_MAGNUS:
		case CR_GRANDCROSS:
		case NPC_GRANDDARKNESS:
		case HT_SKIDTRAP:
		case MA_SKIDTRAP:
		case HT_LANDMINE:
		case MA_LANDMINE:
		case HT_ANKLESNARE:
		case HT_SHOCKWAVE:
		case HT_SANDMAN:
		case MA_SANDMAN:
		case HT_FLASHER:
		case HT_FREEZINGTRAP:
		case MA_FREEZINGTRAP:
		case HT_BLASTMINE:
		case HT_CLAYMORETRAP:
		case AS_VENOMDUST:
		case AM_DEMONSTRATION:
		case PF_FOGWALL:
		case PF_SPIDERWEB:
		case HT_TALKIEBOX:
		case WE_CALLPARTNER:
		case WE_CALLPARENT:
		case WE_CALLBABY:
		case AC_SHOWER: //Ground-placed skill implementation.
		case MA_SHOWER:
		case SA_LANDPROTECTOR:
		case BD_LULLABY:
		case BD_RICHMANKIM:
		case BD_ETERNALCHAOS:
		case BD_DRUMBATTLEFIELD:
		case BD_RINGNIBELUNGEN:
		case BD_ROKISWEIL:
		case BD_INTOABYSS:
		case BD_SIEGFRIED:
		case BA_DISSONANCE:
		case BA_POEMBRAGI:
		case BA_WHISTLE:
		case BA_ASSASSINCROSS:
		case BA_APPLEIDUN:
		case DC_UGLYDANCE:
		case DC_HUMMING:
		case DC_DONTFORGETME:
		case DC_FORTUNEKISS:
		case DC_SERVICEFORYOU:
		case CG_MOONLIT:
		case GS_DESPERADO:
		case NJ_KAENSIN:
		case NJ_BAKUENRYU:
		case NJ_SUITON:
		case NJ_HYOUSYOURAKU:
		case NJ_RAIGEKISAI:
		case NJ_KAMAITACHI:
	#ifdef RENEWAL
		case NJ_HUUMA:
	#endif
		case NPC_EARTHQUAKE:
		case NPC_EVILLAND:
		case WL_COMET:
		case RA_ELECTRICSHOCKER:
		case RA_CLUSTERBOMB:
		case RA_MAGENTATRAP:
		case RA_COBALTTRAP:
		case RA_MAIZETRAP:
		case RA_VERDURETRAP:
		case RA_FIRINGTRAP:
		case RA_ICEBOUNDTRAP:
		case SC_MANHOLE:
		case SC_DIMENSIONDOOR:
		case SC_BLOODYLUST:
		case WM_REVERBERATION:
		case WM_SEVERE_RAINSTORM:
		case WM_POEMOFNETHERWORLD:
		case SO_PSYCHIC_WAVE:
		case SO_VACUUM_EXTREME:
		case GN_WALLOFTHORN:
		case GN_THORNS_TRAP:
		case GN_DEMONIC_FIRE:
		case GN_HELLS_PLANT:
		case GN_FIRE_EXPANSION_SMOKE_POWDER:
		case GN_FIRE_EXPANSION_TEAR_GAS:
		case SO_EARTHGRAVE:
		case SO_DIAMONDDUST:
		case SO_FIRE_INSIGNIA:
		case SO_WATER_INSIGNIA:
		case SO_WIND_INSIGNIA:
		case SO_EARTH_INSIGNIA:
		case KO_HUUMARANKA:
		case KO_MUCHANAGE:
		case KO_BAKURETSU:
		case KO_ZENKAI:
		case MH_LAVA_SLIDE:
		case MH_VOLCANIC_ASH:
		case MH_POISON_MIST:
		case MH_STEINWAND:
		case NC_MAGMA_ERUPTION:
		case SO_ELEMENTAL_SHIELD:
		case RL_B_TRAP:
		case MH_XENO_SLASHER:
			flag|=1;//Set flag to 1 to prevent deleting ammo (it will be deleted on group-delete).
		case GS_GROUNDDRIFT: //Ammo should be deleted right away.
			if ( skill_id == WM_SEVERE_RAINSTORM )
				sc_start(src,src,SC_NO_SWITCH_EQUIP,100,0,skill->get_time(skill_id,skill_lv));
			skill->unitsetting(src,skill_id,skill_lv,x,y,0);
			break;
		case WZ_ICEWALL:
			flag |= 1;
			if( skill->unitsetting(src,skill_id,skill_lv,x,y,0) )
				map->list[src->m].setcell(src->m, x, y, CELL_NOICEWALL, true);
			break;
		case RG_GRAFFITI:
			skill->clear_unitgroup(src);
			skill->unitsetting(src,skill_id,skill_lv,x,y,0);
			flag|=1;
			break;
		case HP_BASILICA:
			if( sc && sc->data[SC_BASILICA] )
				status_change_end(src, SC_BASILICA, INVALID_TIMER); // Cancel Basilica
			else { // Create Basilica. Start SC on caster. Unit timer start SC on others.
				if( map->foreachinrange(skill_count_wos, src, 2, BL_MOB|BL_PC, src) ) {
					if( sd )
						clif->skill_fail(sd,skill_id,USESKILL_FAIL,0);
					return 1;
				}

				skill->clear_unitgroup(src);
				if( skill->unitsetting(src,skill_id,skill_lv,x,y,0) )
					sc_start4(src,src,type,100,skill_lv,0,0,src->id,skill->get_time(skill_id,skill_lv));
				flag|=1;
			}
			break;
		case CG_HERMODE:
			skill->clear_unitgroup(src);
			if ((sg = skill->unitsetting(src,skill_id,skill_lv,x,y,0)))
				sc_start4(src,src,SC_DANCING,100,
					skill_id,0,skill_lv,sg->group_id,skill->get_time(skill_id,skill_lv));
			flag|=1;
			break;
		case RG_CLEANER: // [Valaris]
			r = skill->get_splash(skill_id, skill_lv);
			map->foreachinarea(skill->graffitiremover,src->m,x-r,y-r,x+r,y+r,BL_SKILL);
			break;

		case SO_WARMER:
			flag|= 8;
			/* Fall through */
		case SO_CLOUD_KILL:
			skill->unitsetting(src,skill_id,skill_lv,x,y,0);
			break;

		case WZ_METEOR:
			{
				int area = skill->get_splash(skill_id, skill_lv);
				short tmpx = 0, tmpy = 0, x1 = 0, y1 = 0;
				int i;

				for( i = 0; i < 2 + (skill_lv>>1); i++ ) {
					// Creates a random Cell in the Splash Area
					tmpx = x - area + rnd()%(area * 2 + 1);
					tmpy = y - area + rnd()%(area * 2 + 1);

					if (i == 0 && path->search_long(NULL, src, src->m, src->x, src->y, tmpx, tmpy, CELL_CHKWALL)
						&& !map->getcell(src->m, src, tmpx, tmpy, CELL_CHKLANDPROTECTOR))
						clif->skill_poseffect(src,skill_id,skill_lv,tmpx,tmpy,tick);

					if( i > 0 )
						skill->addtimerskill(src,tick+i*1000,0,tmpx,tmpy,skill_id,skill_lv,(x1<<16)|y1,0);

					x1 = tmpx;
					y1 = tmpy;
				}

				skill->addtimerskill(src,tick+i*1000,0,tmpx,tmpy,skill_id,skill_lv,-1,0);
			}
			break;

		case AL_WARP:
			if(sd)
			{
				clif->skill_warppoint(sd, skill_id, skill_lv, sd->status.save_point.map,
					(skill_lv >= 2) ? sd->status.memo_point[0].map : 0,
					(skill_lv >= 3) ? sd->status.memo_point[1].map : 0,
					(skill_lv >= 4) ? sd->status.memo_point[2].map : 0
				);
			}
			if( sc && sc->data[SC_CURSEDCIRCLE_ATKER] ) //Should only remove after the skill has been casted.
				status_change_end(src,SC_CURSEDCIRCLE_ATKER,INVALID_TIMER);
			return 0; // not to consume item.

		case MO_BODYRELOCATION:
			if (unit->movepos(src, x, y, 1, 1)) {
	#if PACKETVER >= 20111005
				clif->snap(src, src->x, src->y);
	#else
				clif->skill_poseffect(src,skill_id,skill_lv,src->x,src->y,tick);
	#endif
				if (sd)
					skill->blockpc_start (sd, MO_EXTREMITYFIST, 2000);
			}
			break;
		case NJ_SHADOWJUMP:
			if( !map_flag_gvg2(src->m) && !map->list[src->m].flag.battleground ) { //You don't move on GVG grounds.
				unit->movepos(src, x, y, 1, 0);
				clif->slide(src,x,y);
			}
			status_change_end(src, SC_HIDING, INVALID_TIMER);
			break;
		case AM_SPHEREMINE:
		case AM_CANNIBALIZE:
			{
				int summons[5] = { 1589, 1579, 1575, 1555, 1590 };
				//int summons[5] = { 1020, 1068, 1118, 1500, 1368 };
				int class_ = skill_id==AM_SPHEREMINE?1142:summons[skill_lv-1];
				struct mob_data *md;

				// Correct info, don't change any of this! [Celest]
				md = mob->once_spawn_sub(src, src->m, x, y, status->get_name(src), class_, "", SZ_SMALL, AI_NONE);
				if (md) {
					md->master_id = src->id;
					md->special_state.ai = (skill_id == AM_SPHEREMINE) ? AI_SPHERE : AI_FLORA;
					if( md->deletetimer != INVALID_TIMER )
						timer->delete(md->deletetimer, mob->timer_delete);
					md->deletetimer = timer->add(timer->gettick() + skill->get_time(skill_id,skill_lv), mob->timer_delete, md->bl.id, 0);
					mob->spawn (md); //Now it is ready for spawning.
				}
			}
			break;

		// Slim Pitcher [Celest]
		case CR_SLIMPITCHER:
			if (sd) {
				int i = skill_lv%11 - 1;
				int j = pc->search_inventory(sd,skill->dbs->db[skill_id].itemid[i]);
				if (j == INDEX_NOT_FOUND || skill->dbs->db[skill_id].itemid[i] <= 0
				 || sd->inventory_data[j] == NULL || sd->status.inventory[j].amount < skill->dbs->db[skill_id].amount[i]
				) {
					clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
					return 1;
				}
				script->potion_flag = 1;
				script->potion_hp = 0;
				script->potion_sp = 0;
				script->run_use_script(sd, sd->inventory_data[j], 0);
				script->potion_flag = 0;
				//Apply skill bonuses
				i = pc->checkskill(sd,CR_SLIMPITCHER)*10
					+ pc->checkskill(sd,AM_POTIONPITCHER)*10
					+ pc->checkskill(sd,AM_LEARNINGPOTION)*5
					+ pc->skillheal_bonus(sd, skill_id);

				script->potion_hp = script->potion_hp * (100+i)/100;
				script->potion_sp = script->potion_sp * (100+i)/100;

				if(script->potion_hp > 0 || script->potion_sp > 0) {
					i = skill->get_splash(skill_id, skill_lv);
					map->foreachinarea(skill->area_sub,
					                   src->m,x-i,y-i,x+i,y+i,BL_CHAR,
					                   src,skill_id,skill_lv,tick,flag|BCT_PARTY|BCT_GUILD|1,
					                   skill->castend_nodamage_id);
				}
			} else {
				int i = skill_lv%11 - 1;
				struct item_data *item;
				i = skill->dbs->db[skill_id].itemid[i];
				item = itemdb->search(i);
				script->potion_flag = 1;
				script->potion_hp = 0;
				script->potion_sp = 0;
				script->run(item->script,0,src->id,0);
				script->potion_flag = 0;
				i = skill->get_max(CR_SLIMPITCHER)*10;

				script->potion_hp = script->potion_hp * (100+i)/100;
				script->potion_sp = script->potion_sp * (100+i)/100;

				if(script->potion_hp > 0 || script->potion_sp > 0) {
					i = skill->get_splash(skill_id, skill_lv);
					map->foreachinarea(skill->area_sub,
					                   src->m,x-i,y-i,x+i,y+i,BL_CHAR,
					                   src,skill_id,skill_lv,tick,flag|BCT_PARTY|BCT_GUILD|1,
					                   skill->castend_nodamage_id);
				}
			}
			break;

		case HW_GANBANTEIN:
			if (rnd()%100 < 80) {
				int dummy = 1;
				clif->skill_poseffect(src,skill_id,skill_lv,x,y,tick);
				r = skill->get_splash(skill_id, skill_lv);
				map->foreachinarea(skill->cell_overlap, src->m, x-r, y-r, x+r, y+r, BL_SKILL, HW_GANBANTEIN, &dummy, src);
			} else {
				if (sd) clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
				return 1;
			}
			break;

		case HW_GRAVITATION:
			if ((sg = skill->unitsetting(src,skill_id,skill_lv,x,y,0)))
				sc_start4(src,src,type,100,skill_lv,0,BCT_SELF,sg->group_id,skill->get_time(skill_id,skill_lv));
			flag|=1;
			break;

		// Plant Cultivation [Celest]
		case CR_CULTIVATION:
			if (sd) {
				if( map->count_oncell(src->m,x,y,BL_CHAR,0) > 0 ) {
					clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
					return 1;
				}
				clif->skill_poseffect(src,skill_id,skill_lv,x,y,tick);
				if (rnd()%100 < 50) {
					clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
				} else {
					TBL_MOB* md = mob->once_spawn_sub(src, src->m, x, y, "--ja--",(skill_lv < 2 ? 1084+rnd()%2 : 1078+rnd()%6),"", SZ_SMALL, AI_NONE);
					int i;
					if (!md) break;
					if ((i = skill->get_time(skill_id, skill_lv)) > 0)
					{
						if( md->deletetimer != INVALID_TIMER )
							timer->delete(md->deletetimer, mob->timer_delete);
						md->deletetimer = timer->add(tick + i, mob->timer_delete, md->bl.id, 0);
					}
					mob->spawn (md);
				}
			}
			break;

		case SG_SUN_WARM:
		case SG_MOON_WARM:
		case SG_STAR_WARM:
			skill->clear_unitgroup(src);
			if ((sg = skill->unitsetting(src,skill_id,skill_lv,src->x,src->y,0)))
				sc_start4(src,src,type,100,skill_lv,0,0,sg->group_id,skill->get_time(skill_id,skill_lv));
			flag|=1;
			break;

		case PA_GOSPEL:
			if (sce && sce->val4 == BCT_SELF) {
				status_change_end(src, SC_GOSPEL, INVALID_TIMER);
				return 0;
			} else {
				sg = skill->unitsetting(src,skill_id,skill_lv,src->x,src->y,0);
				if (!sg) break;
				if (sce)
					status_change_end(src, type, INVALID_TIMER); //Was under someone else's Gospel. [Skotlex]
				status->change_clear_buffs(src,3);
				sc_start4(src,src,type,100,skill_lv,0,sg->group_id,BCT_SELF,skill->get_time(skill_id,skill_lv));
				clif->skill_poseffect(src, skill_id, skill_lv, 0, 0, tick); // PA_GOSPEL music packet
			}
			break;
		case NJ_TATAMIGAESHI:
			if (skill->unitsetting(src,skill_id,skill_lv,src->x,src->y,0))
				sc_start(src,src,type,100,skill_lv,skill->get_time2(skill_id,skill_lv));
			break;

		case AM_RESURRECTHOMUN: // [orn]
			if (sd) {
				if (!homun->ressurect(sd, 20*skill_lv, x, y)) {
					clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
					break;
				}
			}
			break;

		case RK_WINDCUTTER:
			clif->skill_damage(src, src, tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
			/* Fall through */
		case NC_COLDSLOWER:
		case RK_DRAGONBREATH:
		case RK_DRAGONBREATH_WATER:
			r = skill->get_splash(skill_id,skill_lv);
			map->foreachinarea(skill->area_sub,src->m,x-r,y-r,x+r,y+r,splash_target(src),
			                   src,skill_id,skill_lv,tick,flag|BCT_ENEMY|1,skill->castend_damage_id);
			break;
		case WM_GREAT_ECHO:
		case WM_SOUND_OF_DESTRUCTION:
			r = skill->get_splash(skill_id,skill_lv);
			map->foreachinarea(skill->area_sub,src->m,x-r,y-r,x+r,y+r,BL_CHAR,src,skill_id,skill_lv,tick,flag|BCT_ENEMY|1,skill->castend_damage_id);
			break;

		case WM_LULLABY_DEEPSLEEP:
			r = skill->get_splash(skill_id,skill_lv);
			map->foreachinarea(skill->area_sub,src->m,x-r,y-r,x+r,y+r,BL_CHAR,
				src,skill_id,skill_lv,tick,flag|BCT_ALL|1,skill->castend_damage_id);
			break;

		case WM_VOICEOFSIREN:
			r = skill->get_splash(skill_id,skill_lv);
			map->foreachinarea(skill->area_sub,src->m,x-r,y-r,x+r,y+r,BL_CHAR,
				src,skill_id,skill_lv,tick,flag|BCT_ALL|1,skill->castend_damage_id);
			break;
		case SO_ARRULLO:
			r = skill->get_splash(skill_id,skill_lv);
			map->foreachinarea(skill->area_sub,src->m,x-r,y-r,x+r,y+r,splash_target(src),
			                   src, skill_id, skill_lv, tick, flag|BCT_ENEMY|1, skill->castend_nodamage_id);
			break;
		/**
		 * Guilotine Cross
		 **/
		case GC_POISONSMOKE:
			if( !(sc && sc->data[SC_POISONINGWEAPON]) ) {
				if( sd )
					clif->skill_fail(sd,skill_id,USESKILL_FAIL_GC_POISONINGWEAPON,0);
				return 0;
			}
			clif->skill_damage(src,src,tick,status_get_amotion(src),0,-30000,1,skill_id,skill_lv,BDT_SKILL);
			skill->unitsetting(src, skill_id, skill_lv, x, y, flag);
			//status_change_end(src,SC_POISONINGWEAPON,INVALID_TIMER); // 08/31/2011 - When using poison smoke, you no longer lose the poisoning weapon effect.
			break;
		/**
		 * Arch Bishop
		 **/
		case AB_EPICLESIS:
			if( (sg = skill->unitsetting(src, skill_id, skill_lv, x, y, 0)) ) {
				r = skill->get_unit_range(skill_id, skill_lv);
				map->foreachinarea(skill->area_sub, src->m, x - r, y - r, x + r, y + r, BL_CHAR, src, ALL_RESURRECTION, 1, tick, flag|BCT_NOENEMY|1,skill->castend_nodamage_id);
			}
			break;

		case WL_EARTHSTRAIN:
			{
				int i, wave = skill_lv + 4, dir = map->calc_dir(src,x,y);
				int sx = x = src->x, sy = y = src->y; // Store first caster's location to avoid glitch on unit setting

				for( i = 1; i <= wave; i++ )
				{
					switch( dir ){
						case 0: case 1: case 7: sy = y + i; break;
						case 3: case 4: case 5: sy = y - i; break;
						case 2: sx = x - i; break;
						case 6: sx = x + i; break;
					}
					skill->addtimerskill(src,timer->gettick() + (140 * i),0,sx,sy,skill_id,skill_lv,dir,flag&2);
				}
			}
			break;
		/**
		 * Ranger
		 **/
		case RA_DETONATOR:
			r = skill->get_splash(skill_id, skill_lv);
			map->foreachinarea(skill->detonator, src->m, x-r, y-r, x+r, y+r, BL_SKILL, src);
			clif->skill_damage(src, src, tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
			break;
		/**
		 * Mechanic
		 **/
		case NC_NEUTRALBARRIER:
		case NC_STEALTHFIELD:
			skill->clear_unitgroup(src); // To remove previous skills - cannot used combined
			if( (sg = skill->unitsetting(src,skill_id,skill_lv,src->x,src->y,0)) != NULL ) {
				sc_start2(src,src,skill_id == NC_NEUTRALBARRIER ? SC_NEUTRALBARRIER_MASTER : SC_STEALTHFIELD_MASTER,100,skill_lv,sg->group_id,skill->get_time(skill_id,skill_lv));
				if( sd ) pc->overheat(sd,1);
			}
			break;

		case NC_SILVERSNIPER:
			{
				int class_ = 2042;
				struct mob_data *md;

				md = mob->once_spawn_sub(src, src->m, x, y, status->get_name(src), class_, "", SZ_SMALL, AI_NONE);
				if( md ) {
					md->master_id = src->id;
					md->special_state.ai = AI_FLORA;
					if( md->deletetimer != INVALID_TIMER )
						timer->delete(md->deletetimer, mob->timer_delete);
					md->deletetimer = timer->add(timer->gettick() + skill->get_time(skill_id, skill_lv), mob->timer_delete, md->bl.id, 0);
					mob->spawn( md );
				}
			}
			break;

		case NC_MAGICDECOY:
			if( sd ) clif->magicdecoy_list(sd,skill_lv,x,y);
			break;

		case SC_FEINTBOMB:
			skill->unitsetting(src, skill_id, skill_lv, x, y, 0); // Set bomb on current Position
			clif->skill_nodamage(src, src, skill_id, skill_lv, 1);
			if( skill->blown(src, src, 3 * skill_lv, unit->getdir(src), 0) && sc) {
				sc_start(src, src, SC__FEINTBOMB_MASTER, 100, 0, skill->get_unit_interval(SC_FEINTBOMB));
			}
			break;

		case SC_ESCAPE:
			clif->skill_nodamage(src,src,skill_id,-1,1);
			skill->unitsetting(src,HT_ANKLESNARE,skill_lv,x,y,2);
			skill->addtimerskill(src,tick,src->id,0,0,skill_id,skill_lv,0,0);
			break;

		case LG_OVERBRAND:
			skill->area_temp[1] = 0;
			map->foreachinpath(skill->attack_area,src->m,src->x,src->y,x,y,1,5,BL_CHAR,
				skill->get_type(skill_id),src,src,skill_id,skill_lv,tick,flag,BCT_ENEMY);
			skill->addtimerskill(src,timer->gettick() + status_get_amotion(src), 0, x, y, LG_OVERBRAND_BRANDISH, skill_lv, 0, flag);
			break;

		case LG_BANDING:
			if( sc && sc->data[SC_BANDING] )
				status_change_end(src,SC_BANDING,INVALID_TIMER);
			else if( (sg = skill->unitsetting(src,skill_id,skill_lv,src->x,src->y,0)) != NULL ) {
				sc_start4(src,src,SC_BANDING,100,skill_lv,0,0,sg->group_id,skill->get_time(skill_id,skill_lv));
				if( sd ) pc->banding(sd,skill_lv);
			}
			clif->skill_nodamage(src,src,skill_id,skill_lv,1);
			break;

		case LG_RAYOFGENESIS:
			if( status->charge(src,status_get_max_hp(src)*3*skill_lv / 100,0) ) {
				r = skill->get_splash(skill_id,skill_lv);
				map->foreachinarea(skill->area_sub,src->m,x-r,y-r,x+r,y+r,splash_target(src),
					src,skill_id,skill_lv,tick,flag|BCT_ENEMY|1,skill->castend_damage_id);
			} else if( sd )
				clif->skill_fail(sd,skill_id,USESKILL_FAIL,0);
			break;

		case WM_DOMINION_IMPULSE:
			r = skill->get_splash(skill_id, skill_lv);
			map->foreachinarea( skill->activate_reverberation,src->m, x-r, y-r, x+r,y+r,BL_SKILL);
			break;

		case GN_CRAZYWEED:
			{
				int area = skill->get_splash(skill_id, skill_lv);

				for( r = 0; r < 3 + (skill_lv>>1); r++ ) {
					// Creates a random Cell in the Splash Area
					int tmpx = x - area + rnd()%(area * 2 + 1);
					int tmpy = y - area + rnd()%(area * 2 + 1);

					skill->addtimerskill(src,tick+r*250,0,tmpx,tmpy,GN_CRAZYWEED_ATK,skill_lv,-1,0);
				}
			}
			break;

		case GN_FIRE_EXPANSION: {
			int i;
			int aciddemocast = 5;//If player doesent know Acid Demonstration or knows level 5 or lower, effect 5 will cast level 5 Acid Demo.
			struct unit_data *ud = unit->bl2ud(src);

			if( !ud ) break;

			r = skill->get_unit_range(GN_DEMONIC_FIRE, skill_lv);

			for (i = 0; i < MAX_SKILLUNITGROUP && ud->skillunit[i]; i++) {
				if (ud->skillunit[i]->skill_id != GN_DEMONIC_FIRE)
					continue;
				// FIXME: Code after this point assumes that the group has one and only one unit, regardless of what the skill_unit_db says.
				if (ud->skillunit[i]->unit.count != 1)
					continue;
				if (distance_xy(x, y, ud->skillunit[i]->unit.data[0].bl.x, ud->skillunit[i]->unit.data[0].bl.y) < r) {
					switch (skill_lv) {
						case 3:
							ud->skillunit[i]->unit_id = UNT_FIRE_EXPANSION_SMOKE_POWDER;
							clif->changetraplook(&ud->skillunit[i]->unit.data[0].bl, UNT_FIRE_EXPANSION_SMOKE_POWDER);
							break;
						case 4:
							ud->skillunit[i]->unit_id = UNT_FIRE_EXPANSION_TEAR_GAS;
							clif->changetraplook(&ud->skillunit[i]->unit.data[0].bl, UNT_FIRE_EXPANSION_TEAR_GAS);
							break;
						case 5:// If player knows a level of Acid Demonstration greater then 5, that level will be casted.
							if ( pc->checkskill(sd, CR_ACIDDEMONSTRATION) > 5 )
								aciddemocast = pc->checkskill(sd, CR_ACIDDEMONSTRATION);
							map->foreachinarea(skill->area_sub, src->m,
							                   ud->skillunit[i]->unit.data[0].bl.x - 2, ud->skillunit[i]->unit.data[0].bl.y - 2,
							                   ud->skillunit[i]->unit.data[0].bl.x + 2, ud->skillunit[i]->unit.data[0].bl.y + 2, BL_CHAR,
							                   src, CR_ACIDDEMONSTRATION, aciddemocast, tick, flag|BCT_ENEMY|1|SD_LEVEL, skill->castend_damage_id);
							skill->delunit(&ud->skillunit[i]->unit.data[0]);
							break;
						default:
							ud->skillunit[i]->unit.data[0].val2 = skill_lv;
							ud->skillunit[i]->val2 = skill_lv;
							break;
						}
					}
				}
			}
			break;

		case SO_FIREWALK:
		case SO_ELECTRICWALK:
			if( sce )
				status_change_end(src,type,INVALID_TIMER);
			clif->skill_nodamage(src, src ,skill_id, skill_lv,
								sc_start2(src,src, type, 100, skill_id, skill_lv, skill->get_time(skill_id, skill_lv)));
			break;

		case KO_MAKIBISHI:
		{
			int i;
			for( i = 0; i < (skill_lv+2); i++ ) {
				x = src->x - 1 + rnd()%3;
				y = src->y - 1 + rnd()%3;
				skill->unitsetting(src,skill_id,skill_lv,x,y,0);
			}
		}
			break;

		default:
			if (skill->castend_pos2_unknown(src, &x, &y, &skill_id, &skill_lv, &tick, &flag))
				return 1;
			break;
	}
