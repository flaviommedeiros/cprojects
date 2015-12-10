switch(skill_id) {
		case MER_CRASH:
		case SM_BASH:
		case MS_BASH:
		case MC_MAMMONITE:
		case TF_DOUBLE:
		case AC_DOUBLE:
		case MA_DOUBLE:
		case AS_SONICBLOW:
		case KN_PIERCE:
		case ML_PIERCE:
		case KN_SPEARBOOMERANG:
		case TF_POISON:
		case TF_SPRINKLESAND:
		case AC_CHARGEARROW:
		case MA_CHARGEARROW:
		case RG_INTIMIDATE:
		case AM_ACIDTERROR:
		case BA_MUSICALSTRIKE:
		case DC_THROWARROW:
		case BA_DISSONANCE:
		case CR_HOLYCROSS:
		case NPC_DARKCROSS:
		case CR_SHIELDCHARGE:
		case CR_SHIELDBOOMERANG:
		case NPC_PIERCINGATT:
		case NPC_MENTALBREAKER:
		case NPC_RANGEATTACK:
		case NPC_CRITICALSLASH:
		case NPC_COMBOATTACK:
		case NPC_GUIDEDATTACK:
		case NPC_POISON:
		case NPC_RANDOMATTACK:
		case NPC_WATERATTACK:
		case NPC_GROUNDATTACK:
		case NPC_FIREATTACK:
		case NPC_WINDATTACK:
		case NPC_POISONATTACK:
		case NPC_HOLYATTACK:
		case NPC_DARKNESSATTACK:
		case NPC_TELEKINESISATTACK:
		case NPC_UNDEADATTACK:
		case NPC_ARMORBRAKE:
		case NPC_WEAPONBRAKER:
		case NPC_HELMBRAKE:
		case NPC_SHIELDBRAKE:
		case NPC_BLINDATTACK:
		case NPC_SILENCEATTACK:
		case NPC_STUNATTACK:
		case NPC_PETRIFYATTACK:
		case NPC_CURSEATTACK:
		case NPC_SLEEPATTACK:
		case LK_AURABLADE:
		case LK_SPIRALPIERCE:
		case ML_SPIRALPIERCE:
		case LK_HEADCRUSH:
		case CG_ARROWVULCAN:
		case HW_MAGICCRASHER:
		case ITM_TOMAHAWK:
		case MO_TRIPLEATTACK:
		case CH_CHAINCRUSH:
		case CH_TIGERFIST:
		case PA_SHIELDCHAIN:
		case PA_SACRIFICE:
		case WS_CARTTERMINATION:
		case AS_VENOMKNIFE:
		case HT_PHANTASMIC:
		case TK_DOWNKICK:
		case TK_COUNTER:
		case GS_CHAINACTION:
		case GS_TRIPLEACTION:
		case GS_MAGICALBULLET:
		case GS_TRACKING:
		case GS_PIERCINGSHOT:
		case GS_RAPIDSHOWER:
		case GS_DUST:
		case GS_DISARM:
		case GS_FULLBUSTER:
		case NJ_SYURIKEN:
		case NJ_KUNAI:
#ifndef RENEWAL
		case ASC_BREAKER:
#endif
		case HFLI_MOON: //[orn]
		case HFLI_SBR44: //[orn]
		case NPC_BLEEDING:
		case NPC_CRITICALWOUND:
		case NPC_HELLPOWER:
		case RK_SONICWAVE:
		case RK_STORMBLAST:
		case AB_DUPLELIGHT_MELEE:
		case RA_AIMEDBOLT:
		case NC_AXEBOOMERANG:
		case NC_POWERSWING:
		case GC_CROSSIMPACT:
		case GC_VENOMPRESSURE:
		case SC_TRIANGLESHOT:
		case SC_FEINTBOMB:
		case LG_BANISHINGPOINT:
		case LG_SHIELDPRESS:
		case LG_RAGEBURST:
		case LG_RAYOFGENESIS:
		case LG_HESPERUSLIT:
		case SR_FALLENEMPIRE:
		case SR_CRESCENTELBOW_AUTOSPELL:
		case SR_GATEOFHELL:
		case SR_GENTLETOUCH_QUIET:
		case WM_SEVERE_RAINSTORM_MELEE:
		case WM_GREAT_ECHO:
		case GN_SLINGITEM_RANGEMELEEATK:
		case KO_SETSUDAN:
		case GC_DARKCROW:
		case LG_OVERBRAND_BRANDISH:
		case LG_OVERBRAND:
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
		break;

		/**
		 * Mechanic (MADO GEAR)
		 **/
		case NC_BOOSTKNUCKLE:
		case NC_PILEBUNKER:
		case NC_COLDSLOWER:
			if (sd) pc->overheat(sd,1);
			/* Fall through */
		case RK_WINDCUTTER:
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag|SD_ANIMATION);
			break;

		case LK_JOINTBEAT: // decide the ailment first (affects attack damage and effect)
			switch( rnd()%6 ){
			case 0: flag |= BREAK_ANKLE; break;
			case 1: flag |= BREAK_WRIST; break;
			case 2: flag |= BREAK_KNEE; break;
			case 3: flag |= BREAK_SHOULDER; break;
			case 4: flag |= BREAK_WAIST; break;
			case 5: flag |= BREAK_NECK; break;
			}
			//TODO: is there really no cleaner way to do this?
			sc = status->get_sc(bl);
			if (sc) sc->jb_flag = flag;
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case MO_COMBOFINISH:
			if (!(flag&1) && sc && sc->data[SC_SOULLINK] && sc->data[SC_SOULLINK]->val2 == SL_MONK) {
				//Becomes a splash attack when Soul Linked.
				map->foreachinrange(skill->area_sub, bl,
				                    skill->get_splash(skill_id, skill_lv),splash_target(src),
				                    src,skill_id,skill_lv,tick, flag|BCT_ENEMY|1,
				                    skill->castend_damage_id);
			} else
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case TK_STORMKICK: // Taekwon kicks [Dralnu]
			clif->skill_nodamage(src,bl,skill_id,skill_lv,1);
			skill->area_temp[1] = 0;
			map->foreachinrange(skill->attack_area, src,
			                    skill->get_splash(skill_id, skill_lv), splash_target(src),
			                    BF_WEAPON, src, src, skill_id, skill_lv, tick, flag, BCT_ENEMY);
			break;

		case KN_CHARGEATK: {
				bool path_exists = path->search_long(NULL, src, src->m, src->x, src->y, bl->x, bl->y,CELL_CHKWALL);
				unsigned int dist = distance_bl(src, bl);
				uint8 dir = map->calc_dir(bl, src->x, src->y);

				// teleport to target (if not on WoE grounds)
				if( !map_flag_gvg2(src->m) && !map->list[src->m].flag.battleground && unit->movepos(src, bl->x, bl->y, 0, 1) )
					clif->slide(src, bl->x, bl->y);

				// cause damage and knockback if the path to target was a straight one
				if( path_exists ) {
					skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, dist);
					skill->blown(src, bl, dist, dir, 0);
					//HACK: since knockback officially defaults to the left, the client also turns to the left... therefore,
					// make the caster look in the direction of the target
					unit->setdir(src, (dir+4)%8);
				}

			}
			break;

		case NC_FLAMELAUNCHER:
			if (sd) pc->overheat(sd,1);
			/* Fall through */
		case SN_SHARPSHOOTING:
		case MA_SHARPSHOOTING:
		case NJ_KAMAITACHI:
		case LG_CANNONSPEAR:
			//It won't shoot through walls since on castend there has to be a direct
			//line of sight between caster and target.
			skill->area_temp[1] = bl->id;
			map->foreachinpath(skill->attack_area,src->m,src->x,src->y,bl->x,bl->y,
			                   skill->get_splash(skill_id, skill_lv),skill->get_maxcount(skill_id,skill_lv), splash_target(src),
			                   skill->get_type(skill_id),src,src,skill_id,skill_lv,tick,flag,BCT_ENEMY);
			break;

		case NPC_ACIDBREATH:
		case NPC_DARKNESSBREATH:
		case NPC_FIREBREATH:
		case NPC_ICEBREATH:
		case NPC_THUNDERBREATH:
			skill->area_temp[1] = bl->id;
			map->foreachinpath(skill->attack_area,src->m,src->x,src->y,bl->x,bl->y,
			                   skill->get_splash(skill_id, skill_lv),skill->get_maxcount(skill_id,skill_lv), splash_target(src),
			                   skill->get_type(skill_id),src,src,skill_id,skill_lv,tick,flag,BCT_ENEMY);
			break;

		case MO_INVESTIGATE:
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			status_change_end(src, SC_BLADESTOP, INVALID_TIMER);
			break;

		case RG_BACKSTAP:
			{
				uint8 dir = map->calc_dir(src, bl->x, bl->y), t_dir = unit->getdir(bl);
				if ((!check_distance_bl(src, bl, 0) && !map->check_dir(dir, t_dir)) || bl->type == BL_SKILL) {
					status_change_end(src, SC_HIDING, INVALID_TIMER);
					skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag);
					dir = dir < 4 ? dir+4 : dir-4; // change direction [Celest]
					unit->setdir(bl,dir);
				}
				else if (sd)
					clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
			}
			break;

		case MO_FINGEROFFENSIVE:
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			if (battle_config.finger_offensive_type && sd) {
				int i;
				for (i = 1; i < sd->spiritball_old; i++)
					skill->addtimerskill(src, tick + i * 200, bl->id, 0, 0, skill_id, skill_lv, BF_WEAPON, flag);
			}
			status_change_end(src, SC_BLADESTOP, INVALID_TIMER);
			break;

		case MO_CHAINCOMBO:
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			status_change_end(src, SC_BLADESTOP, INVALID_TIMER);
			break;

		case NJ_ISSEN:
		case MO_EXTREMITYFIST:
			{
				short x, y, i = 2; // Move 2 cells for Issen(from target)
				struct block_list *mbl = bl;
				short dir = 0;

				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);

				if( skill_id == MO_EXTREMITYFIST ) {
					mbl = src;
					i = 3; // for Asura(from caster)
					status->set_sp(src, 0, 0);
					status_change_end(src, SC_EXPLOSIONSPIRITS, INVALID_TIMER);
					status_change_end(src, SC_BLADESTOP, INVALID_TIMER);
#ifdef RENEWAL
					sc_start(src, src,SC_EXTREMITYFIST2,100,skill_lv,skill->get_time(skill_id,skill_lv));
#endif // RENEWAL
				} else {
					status_change_end(src, SC_NJ_NEN, INVALID_TIMER);
					status_change_end(src, SC_HIDING, INVALID_TIMER);
#ifdef RENEWAL
					status->set_hp(src, max(status_get_max_hp(src)/100, 1), 0);
#else // not RENEWAL
					status->set_hp(src, 1, 0);
#endif // RENEWAL
				}
				dir = map->calc_dir(src,bl->x,bl->y);
				if( dir > 0 && dir < 4) x = -i;
				else if( dir > 4 ) x = i;
				else x = 0;
				if( dir > 2 && dir < 6 ) y = -i;
				else if( dir == 7 || dir < 2 ) y = i;
				else y = 0;
				if ((mbl == src || (!map_flag_gvg2(src->m) && !map->list[src->m].flag.battleground))) { // only NJ_ISSEN don't have slide effect in GVG
					if (!(unit->movepos(src, mbl->x+x, mbl->y+y, 1, 1))) {
						// The cell is not reachable (wall, object, ...), move next to the target
						if (x > 0) x = -1;
						else if (x < 0) x = 1;
						if (y > 0) y = -1;
						else if (y < 0) y = 1;

						unit->movepos(src, bl->x+x, bl->y+y, 1, 1);
					}
					clif->slide(src, src->x, src->y);
					clif->fixpos(src);
					clif->spiritball(src);
				}
			}
			break;

		case HT_POWER:
			if( tstatus->race == RC_BRUTE || tstatus->race == RC_INSECT )
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		//Splash attack skills.
		case AS_GRIMTOOTH:
		case MC_CARTREVOLUTION:
		case NPC_SPLASHATTACK:
			flag |= SD_PREAMBLE; // a fake packet will be sent for the first target to be hit
		case AS_SPLASHER:
		case HT_BLITZBEAT:
		case AC_SHOWER:
		case MA_SHOWER:
		case MG_NAPALMBEAT:
		case MG_FIREBALL:
		case RG_RAID:
		case HW_NAPALMVULCAN:
		case NJ_HUUMA:
		case NJ_BAKUENRYU:
		case ASC_METEORASSAULT:
		case GS_DESPERADO:
		case GS_SPREADATTACK:
		case NPC_PULSESTRIKE:
		case NPC_HELLJUDGEMENT:
		case NPC_VAMPIRE_GIFT:
		case RK_IGNITIONBREAK:
		case AB_JUDEX:
		case WL_SOULEXPANSION:
		case WL_CRIMSONROCK:
		case WL_COMET:
		case WL_JACKFROST:
		case RA_ARROWSTORM:
		case RA_WUGDASH:
		case NC_VULCANARM:
		case NC_ARMSCANNON:
		case NC_SELFDESTRUCTION:
		case NC_AXETORNADO:
		case GC_ROLLINGCUTTER:
		case GC_COUNTERSLASH:
		case LG_MOONSLASHER:
		case LG_EARTHDRIVE:
		case SR_TIGERCANNON:
		case SR_RAMPAGEBLASTER:
		case SR_SKYNETBLOW:
		case SR_WINDMILL:
		case SR_RIDEINLIGHTNING:
		case WM_REVERBERATION:
		case SO_VARETYR_SPEAR:
		case GN_CART_TORNADO:
		case GN_CARTCANNON:
		case KO_HAPPOKUNAI:
		case KO_HUUMARANKA:
		case KO_MUCHANAGE:
		case KO_BAKURETSU:
		case GN_ILLUSIONDOPING:
		case MH_XENO_SLASHER:
			if( flag&1 ) {//Recursive invocation
				// skill->area_temp[0] holds number of targets in area
				// skill->area_temp[1] holds the id of the original target
				// skill->area_temp[2] counts how many targets have already been processed
				int sflag = skill->area_temp[0] & 0xFFF, heal;
				struct status_change *tsc = status->get_sc(bl);
				if( flag&SD_LEVEL )
					sflag |= SD_LEVEL; // -1 will be used in packets instead of the skill level
				if( (skill->area_temp[1] != bl->id && !(skill->get_inf2(skill_id)&INF2_NPC_SKILL)) || flag&SD_ANIMATION )
					sflag |= SD_ANIMATION; // original target gets no animation (as well as all NPC skills)

				if ( tsc && tsc->data[SC_HOVERING] && ( skill_id == SR_WINDMILL || skill_id == LG_MOONSLASHER ) )
					break;

				heal = skill->attack(skill->get_type(skill_id), src, src, bl, skill_id, skill_lv, tick, sflag);
				if( skill_id == NPC_VAMPIRE_GIFT && heal > 0 ) {
					clif->skill_nodamage(NULL, src, AL_HEAL, heal, 1);
					status->heal(src,heal,0,0);
				}
			} else {
				switch ( skill_id ) {
					case NJ_BAKUENRYU:
					case LG_EARTHDRIVE:
					case GN_CARTCANNON:
						clif->skill_nodamage(src,bl,skill_id,skill_lv,1);
						break;
					case SR_TIGERCANNON:
					case GC_COUNTERSLASH:
					case GC_ROLLINGCUTTER:
						flag |= SD_ANIMATION;
						/* Fall through */
					case LG_MOONSLASHER:
					case MH_XENO_SLASHER:
						clif->skill_damage(src,bl,tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
						break;
					default:
						break;
				}

				skill->area_temp[0] = 0;
				skill->area_temp[1] = bl->id;
				skill->area_temp[2] = 0;
				if( skill_id == WL_CRIMSONROCK ) {
					skill->area_temp[4] = bl->x;
					skill->area_temp[5] = bl->y;
				}

				if( skill_id == NC_VULCANARM )
					if (sd) pc->overheat(sd,1);

				// if skill damage should be split among targets, count them
				//SD_LEVEL -> Forced splash damage for Auto Blitz-Beat -> count targets
				//special case: Venom Splasher uses a different range for searching than for splashing
				if( flag&SD_LEVEL || skill->get_nk(skill_id)&NK_SPLASHSPLIT )
					skill->area_temp[0] = map->foreachinrange(skill->area_sub, bl, (skill_id == AS_SPLASHER)?1:skill->get_splash(skill_id, skill_lv), BL_CHAR, src, skill_id, skill_lv, tick, BCT_ENEMY, skill->area_sub_count);

				// recursive invocation of skill->castend_damage_id() with flag|1
				map->foreachinrange(skill->area_sub, bl, skill->get_splash(skill_id, skill_lv), splash_target(src), src, skill_id, skill_lv, tick, flag|BCT_ENEMY|SD_SPLASH|1, skill->castend_damage_id);
			}
			break;

		case SM_MAGNUM:
		case MS_MAGNUM:
			if( flag&1 ) {
				//Damage depends on distance, so add it to flag if it is > 1
				skill->attack(skill->get_type(skill_id), src, src, bl, skill_id, skill_lv, tick, flag|SD_ANIMATION|distance_bl(src, bl));
			}
			break;

		case KN_BRANDISHSPEAR:
		case ML_BRANDISH:
			//Coded apart for it needs the flag passed to the damage calculation.
			if (skill->area_temp[1] != bl->id)
				skill->attack(skill->get_type(skill_id), src, src, bl, skill_id, skill_lv, tick, flag|SD_ANIMATION);
			else
				skill->attack(skill->get_type(skill_id), src, src, bl, skill_id, skill_lv, tick, flag);
			break;

		case KN_BOWLINGBASH:
		case MS_BOWLINGBASH:
			{
				int min_x,max_x,min_y,max_y,i,c,dir,tx,ty;
				// Chain effect and check range gets reduction by recursive depth, as this can reach 0, we don't use blowcount
				c = (skill_lv-(flag&0xFFF)+1)/2;
				// Determine the Bowling Bash area depending on configuration
				if (battle_config.bowling_bash_area == 0) {
					// Gutter line system
					min_x = ((src->x)-c) - ((src->x)-c)%40;
					if(min_x < 0) min_x = 0;
					max_x = min_x + 39;
					min_y = ((src->y)-c) - ((src->y)-c)%40;
					if(min_y < 0) min_y = 0;
					max_y = min_y + 39;
				} else if (battle_config.bowling_bash_area == 1) {
					// Gutter line system without demi gutter bug
					min_x = src->x - (src->x)%40;
					max_x = min_x + 39;
					min_y = src->y - (src->y)%40;
					max_y = min_y + 39;
				} else {
					// Area around caster
					min_x = src->x - battle_config.bowling_bash_area;
					max_x = src->x + battle_config.bowling_bash_area;
					min_y = src->y - battle_config.bowling_bash_area;
					max_y = src->y + battle_config.bowling_bash_area;
				}
				// Initialization, break checks, direction
				if((flag&0xFFF) > 0) {
					// Ignore monsters outside area
					if(bl->x < min_x || bl->x > max_x || bl->y < min_y || bl->y > max_y)
						break;
					// Ignore monsters already in list
					if(idb_exists(skill->bowling_db, bl->id))
						break;
					// Random direction
					dir = rnd()%8;
				} else {
					// Create an empty list of already hit targets
					db_clear(skill->bowling_db);
					// Direction is walkpath
					dir = (unit->getdir(src)+4)%8;
				}
				// Add current target to the list of already hit targets
				idb_put(skill->bowling_db, bl->id, bl);
				// Keep moving target in direction square by square
				tx = bl->x;
				ty = bl->y;
				for(i=0;i<c;i++) {
					// Target coordinates (get changed even if knockback fails)
					tx -= dirx[dir];
					ty -= diry[dir];
					// If target cell is a wall then break
					if(map->getcell(bl->m, bl, tx, ty, CELL_CHKWALL))
						break;
					skill->blown(src,bl,1,dir,0);
					// Splash around target cell, but only cells inside area; we first have to check the area is not negative
					if((max(min_x,tx-1) <= min(max_x,tx+1)) &&
						(max(min_y,ty-1) <= min(max_y,ty+1)) &&
						(map->foreachinarea(skill->area_sub, bl->m, max(min_x,tx-1), max(min_y,ty-1), min(max_x,tx+1), min(max_y,ty+1), splash_target(src), src, skill_id, skill_lv, tick, flag|BCT_ENEMY, skill->area_sub_count))) {
						// Recursive call
						map->foreachinarea(skill->area_sub, bl->m, max(min_x,tx-1), max(min_y,ty-1), min(max_x,tx+1), min(max_y,ty+1), splash_target(src), src, skill_id, skill_lv, tick, (flag|BCT_ENEMY)+1, skill->castend_damage_id);
						// Self-collision
						if(bl->x >= min_x && bl->x <= max_x && bl->y >= min_y && bl->y <= max_y)
							skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,(flag&0xFFF)>0?SD_ANIMATION:0);
						break;
					}
				}
				// Original hit or chain hit depending on flag
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,(flag&0xFFF)>0?SD_ANIMATION:0);
			}
			break;

		case KN_SPEARSTAB:
			if(flag&1) {
				if (bl->id==skill->area_temp[1])
					break;
				if (skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,SD_ANIMATION))
					skill->blown(src,bl,skill->area_temp[2],-1,0);
			} else {
				int x=bl->x,y=bl->y,i,dir;
				dir = map->calc_dir(bl,src->x,src->y);
				skill->area_temp[1] = bl->id;
				skill->area_temp[2] = skill->get_blewcount(skill_id,skill_lv);
				// all the enemies between the caster and the target are hit, as well as the target
				if (skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,0))
					skill->blown(src,bl,skill->area_temp[2],-1,0);
				for (i=0;i<4;i++) {
					map->foreachincell(skill->area_sub,bl->m,x,y,BL_CHAR,src,skill_id,skill_lv,
					                   tick,flag|BCT_ENEMY|1,skill->castend_damage_id);
					x += dirx[dir];
					y += diry[dir];
				}
			}
			break;

		case TK_TURNKICK:
		case MO_BALKYOUNG: //Active part of the attack. Skill-attack [Skotlex]
		{
			skill->area_temp[1] = bl->id; //NOTE: This is used in skill->castend_nodamage_id to avoid affecting the target.
			if (skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag))
				map->foreachinrange(skill->area_sub,bl,
				                    skill->get_splash(skill_id, skill_lv),BL_CHAR,
				                    src,skill_id,skill_lv,tick,flag|BCT_ENEMY|1,
				                    skill->castend_nodamage_id);
		}
			break;
		case CH_PALMSTRIKE: // Palm Strike takes effect 1sec after casting. [Skotlex]
			//clif->skill_nodamage(src,bl,skill_id,skill_lv,0); //Can't make this one display the correct attack animation delay :/
			clif->damage(src,bl,status_get_amotion(src),0,-1,1,BDT_ENDURE,0); //Display an absorbed damage attack.
			skill->addtimerskill(src, tick + (1000+status_get_amotion(src)), bl->id, 0, 0, skill_id, skill_lv, BF_WEAPON, flag);
			break;

		case PR_TURNUNDEAD:
		case ALL_RESURRECTION:
			if (!battle->check_undead(tstatus->race, tstatus->def_ele))
				break;
			skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case MG_SOULSTRIKE:
		case NPC_DARKSTRIKE:
		case MG_COLDBOLT:
		case MG_FIREBOLT:
		case MG_LIGHTNINGBOLT:
		case WZ_EARTHSPIKE:
		case AL_HEAL:
		case AL_HOLYLIGHT:
		case WZ_JUPITEL:
		case NPC_DARKTHUNDER:
		case PR_ASPERSIO:
		case MG_FROSTDIVER:
		case WZ_SIGHTBLASTER:
		case WZ_SIGHTRASHER:
		case NJ_KOUENKA:
		case NJ_HYOUSENSOU:
		case NJ_HUUJIN:
		case AB_ADORAMUS:
		case AB_RENOVATIO:
		case AB_HIGHNESSHEAL:
		case AB_DUPLELIGHT_MAGIC:
		case WM_METALICSOUND:
		case MH_ERASER_CUTTER:
		case KO_KAIHOU:
			skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case NPC_MAGICALATTACK:
			skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
			sc_start(src, src,status->skill2sc(skill_id),100,skill_lv,skill->get_time(skill_id,skill_lv));
			break;

		case HVAN_CAPRICE: //[blackhole89]
			{
				int ran=rnd()%4;
				int sid = 0;
				switch(ran)
				{
				case 0: sid=MG_COLDBOLT; break;
				case 1: sid=MG_FIREBOLT; break;
				case 2: sid=MG_LIGHTNINGBOLT; break;
				case 3: sid=WZ_EARTHSPIKE; break;
				}
				skill->attack(BF_MAGIC,src,src,bl,sid,skill_lv,tick,flag|SD_LEVEL);
			}
			break;
		case WZ_WATERBALL:
			{
				int range = skill_lv / 2;
				int maxlv = skill->get_max(skill_id); // learnable level
				int count = 0;
				int x, y;
				struct skill_unit *su;

				if( skill_lv > maxlv ) {
					if( src->type == BL_MOB && skill_lv == 10 )
						range = 4;
					else
						range = maxlv / 2;
				}

				for( y = src->y - range; y <= src->y + range; ++y )
					for( x = src->x - range; x <= src->x + range; ++x ) {
						if( !map->find_skill_unit_oncell(src,x,y,SA_LANDPROTECTOR,NULL,1) ) {
							if (src->type != BL_PC || map->getcell(src->m, src, x, y, CELL_CHKWATER)) // non-players bypass the water requirement
								count++; // natural water cell
							else if( (su = map->find_skill_unit_oncell(src,x,y,SA_DELUGE,NULL,1)) != NULL
							      || (su = map->find_skill_unit_oncell(src,x,y,NJ_SUITON,NULL,1)) != NULL ) {
								count++; // skill-induced water cell
								skill->delunit(su); // consume cell
							}
						}
					}

				if( count > 1 ) // queue the remaining count - 1 timerskill Waterballs
					skill->addtimerskill(src,tick+150,bl->id,0,0,skill_id,skill_lv,count-1,flag);
			}
			skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case PR_BENEDICTIO:
			//Should attack undead and demons. [Skotlex]
			if (battle->check_undead(tstatus->race, tstatus->def_ele) || tstatus->race == RC_DEMON)
				skill->attack(BF_MAGIC, src, src, bl, skill_id, skill_lv, tick, flag);
		break;

		case SL_SMA:
			status_change_end(src, SC_SMA_READY, INVALID_TIMER);
			/* Fall through */
		case SL_STIN:
		case SL_STUN:
			if (sd && !battle_config.allow_es_magic_pc && bl->type != BL_MOB) {
				status->change_start(src,src,SC_STUN,10000,skill_lv,0,0,0,500,SCFLAG_FIXEDTICK|SCFLAG_FIXEDRATE);
				clif->skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
				break;
			}
			skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case NPC_DARKBREATH:
			clif->emotion(src,E_AG);
			/* Fall through */
		case SN_FALCONASSAULT:
		case PA_PRESSURE:
		case CR_ACIDDEMONSTRATION:
		case TF_THROWSTONE:
		case NPC_SMOKING:
		case GS_FLING:
		case NJ_ZENYNAGE:
		case GN_THORNS_TRAP:
		case GN_HELLS_PLANT_ATK:
#ifdef RENEWAL
		case ASC_BREAKER:
#endif
			skill->attack(BF_MISC,src,src,bl,skill_id,skill_lv,tick,flag);
			break;
		/**
		 * Rune Knight
		 **/
		case RK_DRAGONBREATH_WATER:
		case RK_DRAGONBREATH:
		{
			struct status_change *tsc = NULL;
			if( (tsc = status->get_sc(bl)) && (tsc->data[SC_HIDING] )) {
				clif->skill_nodamage(src,src,skill_id,skill_lv,1);
			} else
				skill->attack(BF_MISC,src,src,bl,skill_id,skill_lv,tick,flag);
		}
			break;
		case NPC_SELFDESTRUCTION: {
			struct status_change *tsc = NULL;
			if( (tsc = status->get_sc(bl)) && tsc->data[SC_HIDING] )
				break;
			}
		case HVAN_EXPLOSION:
			if (src != bl)
				skill->attack(BF_MISC,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		// [Celest]
		case PF_SOULBURN:
			if (rnd()%100 < (skill_lv < 5 ? 30 + skill_lv * 10 : 70)) {
				clif->skill_nodamage(src,bl,skill_id,skill_lv,1);
				if (skill_lv == 5)
					skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
				status_percent_damage(src, bl, 0, 100, false);
			} else {
				clif->skill_nodamage(src,src,skill_id,skill_lv,1);
				if (skill_lv == 5)
					skill->attack(BF_MAGIC,src,src,src,skill_id,skill_lv,tick,flag);
				status_percent_damage(src, src, 0, 100, false);
			}
			break;

		case NPC_BLOODDRAIN:
		case NPC_ENERGYDRAIN:
		{
			int heal = skill->attack( (skill_id == NPC_BLOODDRAIN) ? BF_WEAPON : BF_MAGIC,
			                         src, src, bl, skill_id, skill_lv, tick, flag);
			if (heal > 0){
				clif->skill_nodamage(NULL, src, AL_HEAL, heal, 1);
				status->heal(src, heal, 0, 0);
			}
		}
			break;

		case GS_BULLSEYE:
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case NJ_KASUMIKIRI:
			if (skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag) > 0)
				sc_start(src,src,SC_HIDING,100,skill_lv,skill->get_time(skill_id,skill_lv));
			break;
		case NJ_KIRIKAGE:
			if( !map_flag_gvg2(src->m) && !map->list[src->m].flag.battleground ) {
				//You don't move on GVG grounds.
				short x, y;
				map->search_freecell(bl, 0, &x, &y, 1, 1, 0);
				if (unit->movepos(src, x, y, 0, 0))
					clif->slide(src,src->x,src->y);
			}
			status_change_end(src, SC_HIDING, INVALID_TIMER);
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			break;
		case RK_HUNDREDSPEAR:
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			if(rnd()%100 < (10 + 3*skill_lv)) {
				if( !sd || pc->checkskill(sd,KN_SPEARBOOMERANG) == 0 )
					break; // Spear Boomerang auto cast chance only works if you have mastered Spear Boomerang.
				skill->blown(src,bl,6,-1,0);
				skill->addtimerskill(src,tick+800,bl->id,0,0,skill_id,skill_lv,BF_WEAPON,flag);
				skill->castend_damage_id(src,bl,KN_SPEARBOOMERANG,1,tick,0);
			}
			break;
		case RK_PHANTOMTHRUST:
		{
			struct map_session_data *tsd = BL_CAST(BL_PC, bl);
			unit->setdir(src,map->calc_dir(src, bl->x, bl->y));
			clif->skill_nodamage(src,bl,skill_id,skill_lv,1);

			skill->blown(src,bl,distance_bl(src,bl)-1,unit->getdir(src),0);
			if( sd && tsd && sd->status.party_id && tsd->status.party_id && sd->status.party_id == tsd->status.party_id ) // Don't damage party members.
				; // No damage to Members
			else
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
		}
			break;

		case KO_JYUMONJIKIRI:
		case GC_DARKILLUSION:
			{
				short x, y;
				short dir = map->calc_dir(bl, src->x, src->y);

				if ( dir < 4 ) {
					x = bl->x + 2 * (dir > 0) - 3 * (dir > 0);
					y = bl->y + 1 - (dir / 2) - (dir > 2);
				} else {
					x = bl->x + 2 * (dir > 4) - 1 * (dir > 4);
					y = bl->y + (dir / 6) - 1 + (dir > 6);
				}

				if ( unit->movepos(src, x, y, 1, 1) ) {
					clif->slide(src, x, y);
					clif->fixpos(src); // the official server send these two packets.
					skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag);
					if ( rnd() % 100 < 4 * skill_lv &&	skill_id == GC_DARKILLUSION )
						skill->castend_damage_id(src, bl, GC_CROSSIMPACT, skill_lv, tick, flag);
				}
			}
			break;
		case GC_WEAPONCRUSH:
			if( sc && sc->data[SC_COMBOATTACK] && sc->data[SC_COMBOATTACK]->val1 == GC_WEAPONBLOCKING )
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			else if( sd )
				clif->skill_fail(sd,skill_id,USESKILL_FAIL_GC_WEAPONBLOCKING,0);
			break;

		case GC_CROSSRIPPERSLASHER:
			if( sd && !(sc && sc->data[SC_ROLLINGCUTTER]) )
				clif->skill_fail(sd,skill_id,USESKILL_FAIL_CONDITION,0);
			else
			{
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
				status_change_end(src,SC_ROLLINGCUTTER,INVALID_TIMER);
			}
			break;

		case GC_PHANTOMMENACE:
			if( flag&1 ) {
				// Only Hits Invisible Targets
				struct status_change *tsc = status->get_sc(bl);
				if(tsc && (tsc->option&(OPTION_HIDE|OPTION_CLOAK|OPTION_CHASEWALK) || tsc->data[SC__INVISIBILITY]) )
					skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			}
			break;
		case WL_CHAINLIGHTNING:
			clif->skill_nodamage(src,bl,skill_id,skill_lv,1);
			skill->addtimerskill(src,tick+status_get_amotion(src),bl->id,0,0,WL_CHAINLIGHTNING_ATK,skill_lv,0,flag);
			break;
		case WL_DRAINLIFE:
		{
			int heal = skill->attack(skill->get_type(skill_id), src, src, bl, skill_id, skill_lv, tick, flag);
			int rate = 70 + 5 * skill_lv;

			heal = heal * (5 + 5 * skill_lv) / 100;

			if( bl->type == BL_SKILL || status_get_hp(src) == status_get_max_hp(src)) // Don't absorb when caster was in full HP
				heal = 0; // Don't absorb heal from Ice Walls or other skill units.

			if( heal && rnd()%100 < rate ) {
				status->heal(src, heal, 0, 0);
				clif->skill_nodamage(NULL, src, AL_HEAL, heal, 1);
			}
		}
			break;

		case WL_TETRAVORTEX:
			if (sc) {
				int i = SC_SUMMON5, x = 0;
				int types[][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
				for(; i >= SC_SUMMON1; i--) {
					if (sc->data[i]) {
						int skillid = WL_TETRAVORTEX_FIRE + (sc->data[i]->val1 - WLS_FIRE) + (sc->data[i]->val1 == WLS_WIND) - (sc->data[i]->val1 == WLS_WATER);
						if (x < 4) {
							int sc_index = 0, rate = 0;
							types[x][0] = (sc->data[i]->val1 - WLS_FIRE) + 1;
							types[x][1] = 25; // 25% each for equal sharing
							if (x == 3) {
								x = 0;
								sc_index = types[rnd()%4][0];
								for(; x < 4; x++)
									if(types[x][0] == sc_index)
										rate += types[x][1];
							}
							skill->addtimerskill(src, tick + (SC_SUMMON5-i) * 206, bl->id, sc_index, rate, skillid, skill_lv, x, flag);
						}
						status_change_end(src, (sc_type)i, INVALID_TIMER);
						x++;
					}
				}
			}
			break;

		case WL_RELEASE:
			if (sd) {
				int i;
				clif->skill_nodamage(src, bl, skill_id, skill_lv, 1);
				skill->toggle_magicpower(src, skill_id);
				// Priority is to release SpellBook
				if (sc && sc->data[SC_READING_SB]) {
					// SpellBook
					uint16 spell_skill_id, spell_skill_lv, point, s = 0;
					int spell[SC_SPELLBOOK7-SC_SPELLBOOK1 + 1];
					int cooldown;

					for(i = SC_SPELLBOOK7; i >= SC_SPELLBOOK1; i--) // List all available spell to be released
					if( sc->data[i] ) spell[s++] = i;

					if ( s == 0 )
						break;

					i = spell[s==1?0:rnd()%s];// Random select of spell to be released.
					if( s && sc->data[i] ){// Now extract the data from the preserved spell
						spell_skill_id = sc->data[i]->val1;
						spell_skill_lv = sc->data[i]->val2;
						point = sc->data[i]->val3;
						status_change_end(src, (sc_type)i, INVALID_TIMER);
					} else {
						//something went wrong :(
						break;
					}

					if( sc->data[SC_READING_SB]->val2 > point )
						sc->data[SC_READING_SB]->val2 -= point;
					else // Last spell to be released
						status_change_end(src, SC_READING_SB, INVALID_TIMER);

					if( !skill->check_condition_castbegin(sd, spell_skill_id, spell_skill_lv) )
						break;

					switch( skill->get_casttype(spell_skill_id) ) {
						case CAST_GROUND:
							skill->castend_pos2(src, bl->x, bl->y, spell_skill_id, spell_skill_lv, tick, 0);
							break;
						case CAST_NODAMAGE:
							skill->castend_nodamage_id(src, bl, spell_skill_id, spell_skill_lv, tick, 0);
							break;
						case CAST_DAMAGE:
							skill->castend_damage_id(src, bl, spell_skill_id, spell_skill_lv, tick, 0);
							break;
					}

					sd->ud.canact_tick = tick + skill->delay_fix(src, spell_skill_id, spell_skill_lv);
					clif->status_change(src, SI_POSTDELAY, 1, skill->delay_fix(src, spell_skill_id, spell_skill_lv), 0, 0, 0);

					cooldown = skill->get_cooldown(spell_skill_id, spell_skill_lv);
					for (i = 0; i < ARRAYLENGTH(sd->skillcooldown) && sd->skillcooldown[i].id; i++) {
						if (sd->skillcooldown[i].id == spell_skill_id){
							cooldown += sd->skillcooldown[i].val;
							break;
						}
					}
					if(cooldown)
						skill->blockpc_start(sd, spell_skill_id, cooldown);
				}else if( sc ){ // Summon Balls
					for(i = SC_SUMMON5; i >= SC_SUMMON1; i--){
						if( sc->data[i] ){
							int skillid = WL_SUMMON_ATK_FIRE + (sc->data[i]->val1 - WLS_FIRE);
							skill->addtimerskill(src, tick + status_get_adelay(src) * (SC_SUMMON5 - i), bl->id, 0, 0, skillid, skill_lv, BF_MAGIC, flag);
							status_change_end(src, (sc_type)i, INVALID_TIMER);
							if(skill_lv == 1)
								break;
						}
					}
				}
			}
			break;
		case WL_FROSTMISTY:
			// Doesn't deal damage through non-shootable walls.
			if( path->search(NULL,src,src->m,src->x,src->y,bl->x,bl->y,1,CELL_CHKWALL) )
				skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag|SD_ANIMATION);
			break;
		case WL_HELLINFERNO:
			skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
			skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag|ELE_DARK);
			break;
		case RA_WUGSTRIKE:
			if( sd && pc_isridingwug(sd) ){
				short x[8]={0,-1,-1,-1,0,1,1,1};
				short y[8]={1,1,0,-1,-1,-1,0,1};
				uint8 dir = map->calc_dir(bl, src->x, src->y);

				if( unit->movepos(src, bl->x+x[dir], bl->y+y[dir], 1, 1) )
				{
					clif->slide(src, bl->x+x[dir], bl->y+y[dir]);
					clif->fixpos(src);
					skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag);
				}
				break;
			}
		case RA_WUGBITE:
			if( path->search(NULL,src,src->m,src->x,src->y,bl->x,bl->y,1,CELL_CHKNOREACH) ) {
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			}else if( sd && skill_id == RA_WUGBITE ) // Only RA_WUGBITE has the skill fail message.
				clif->skill_fail(sd, skill_id, USESKILL_FAIL_LEVEL, 0);

			break;

		case RA_SENSITIVEKEEN:
			if( bl->type != BL_SKILL ) { // Only Hits Invisible Targets
				struct status_change * tsc = status->get_sc(bl);
				if( tsc && tsc->option&(OPTION_HIDE|OPTION_CLOAK) ){
					skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
					status_change_end(bl, SC_CLOAKINGEXCEED, INVALID_TIMER);
				}
			} else {
				struct skill_unit *su = BL_CAST(BL_SKILL,bl);
				struct skill_unit_group* sg;

				if( su && (sg=su->group) != NULL && skill->get_inf2(sg->skill_id)&INF2_TRAP ) {
					if( !(sg->unit_id == UNT_USED_TRAPS || (sg->unit_id == UNT_ANKLESNARE && sg->val2 != 0 )) ) {
						struct item item_tmp;
						memset(&item_tmp,0,sizeof(item_tmp));
						item_tmp.nameid = sg->item_id?sg->item_id:ITEMID_TRAP;
						item_tmp.identify = 1;
						if( item_tmp.nameid )
							map->addflooritem(bl, &item_tmp, 1, bl->m, bl->x, bl->y, 0, 0, 0, 0);
					}
					skill->delunit(su);
				}
			}
			break;
		case NC_INFRAREDSCAN:
			if( flag&1 ) {
				//TODO: Need a confirmation if the other type of hidden status is included to be scanned. [Jobbie]
				sc_start(src, bl, SC_INFRAREDSCAN, 10000, skill_lv, skill->get_time(skill_id, skill_lv));
				status_change_end(bl, SC_HIDING, INVALID_TIMER);
				status_change_end(bl, SC_CLOAKING, INVALID_TIMER);
				status_change_end(bl, SC_CLOAKINGEXCEED, INVALID_TIMER); // Need confirm it.
			} else {
				map->foreachinrange(skill->area_sub, bl, skill->get_splash(skill_id, skill_lv), splash_target(src), src, skill_id, skill_lv, tick, flag|BCT_ENEMY|SD_SPLASH|1, skill->castend_damage_id);
				clif->skill_damage(src,src,tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
				if( sd ) pc->overheat(sd,1);
			}
			break;

		case NC_MAGNETICFIELD:
			sc_start2(src,bl,SC_MAGNETICFIELD,100,skill_lv,src->id,skill->get_time(skill_id,skill_lv));
			break;
		case SC_FATALMENACE:
			if( flag&1 )
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			else {
				short x, y;
				map->search_freecell(src, 0, &x, &y, -1, -1, 0);
				// Destination area
				skill->area_temp[4] = x;
				skill->area_temp[5] = y;
				map->foreachinrange(skill->area_sub, bl, skill->get_splash(skill_id, skill_lv), splash_target(src), src, skill_id, skill_lv, tick, flag|BCT_ENEMY|1, skill->castend_damage_id);
				skill->addtimerskill(src,tick + 800,src->id,x,y,skill_id,skill_lv,0,flag); // To teleport Self
				clif->skill_damage(src,src,tick,status_get_amotion(src),0,-30000,1,skill_id,skill_lv,BDT_SKILL);
			}
			break;
		case LG_PINPOINTATTACK:
			if( !map_flag_gvg2(src->m) && !map->list[src->m].flag.battleground && unit->movepos(src, bl->x, bl->y, 1, 1) )
				clif->slide(src,bl->x,bl->y);
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case LG_SHIELDSPELL:
			if ( skill_lv == 1 )
				skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			else if ( skill_lv == 2 )
				skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case SR_DRAGONCOMBO:
			skill->attack(BF_WEAPON,src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case SR_KNUCKLEARROW:
				if( !map_flag_gvg2(src->m) && !map->list[src->m].flag.battleground && unit->movepos(src, bl->x, bl->y, 1, 1) ) {
					clif->slide(src,bl->x,bl->y);
					clif->fixpos(src); // Aegis send this packet too.
				}

				if( flag&1 )
					skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag|SD_LEVEL);
				else
					skill->addtimerskill(src, tick + 300, bl->id, 0, 0, skill_id, skill_lv, BF_WEAPON, flag|SD_LEVEL|2);
			break;

		case SR_HOWLINGOFLION:
				status_change_end(bl, SC_SWING, INVALID_TIMER);
				status_change_end(bl, SC_SYMPHONY_LOVE, INVALID_TIMER);
				status_change_end(bl, SC_MOONLIT_SERENADE, INVALID_TIMER);
				status_change_end(bl, SC_RUSH_WINDMILL, INVALID_TIMER);
				status_change_end(bl, SC_ECHOSONG, INVALID_TIMER);
				status_change_end(bl, SC_HARMONIZE, INVALID_TIMER);
				status_change_end(bl, SC_NETHERWORLD, INVALID_TIMER);
				status_change_end(bl, SC_SIREN, INVALID_TIMER);
				status_change_end(bl, SC_GLOOMYDAY, INVALID_TIMER);
				status_change_end(bl, SC_SONG_OF_MANA, INVALID_TIMER);
				status_change_end(bl, SC_DANCE_WITH_WUG, INVALID_TIMER);
				status_change_end(bl, SC_SATURDAY_NIGHT_FEVER, INVALID_TIMER);
				status_change_end(bl, SC_MELODYOFSINK, INVALID_TIMER);
				status_change_end(bl, SC_BEYOND_OF_WARCRY, INVALID_TIMER);
				status_change_end(bl, SC_UNLIMITED_HUMMING_VOICE, INVALID_TIMER);
				skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag|SD_ANIMATION);
			break;

		case SR_EARTHSHAKER:
			if( flag&1 ) { //by default cloaking skills are remove by aoe skills so no more checking/removing except hiding and cloaking exceed.
				skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag);
				status_change_end(bl, SC_HIDING, INVALID_TIMER);
				status_change_end(bl, SC_CLOAKINGEXCEED, INVALID_TIMER);
			} else{
				map->foreachinrange(skill->area_sub, bl, skill->get_splash(skill_id, skill_lv), splash_target(src), src, skill_id, skill_lv, tick, flag|BCT_ENEMY|SD_SPLASH|1, skill->castend_damage_id);
				clif->skill_damage(src, src, tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
			}
			break;

		case WM_SOUND_OF_DESTRUCTION:
			{
				struct status_change *tsc = status->get_sc(bl);
				if( tsc && tsc->count && ( tsc->data[SC_SWING] || tsc->data[SC_SYMPHONY_LOVE] || tsc->data[SC_MOONLIT_SERENADE] ||
						tsc->data[SC_RUSH_WINDMILL] || tsc->data[SC_ECHOSONG] || tsc->data[SC_HARMONIZE] ||
						tsc->data[SC_SIREN] || tsc->data[SC_DEEP_SLEEP] || tsc->data[SC_SIRCLEOFNATURE] ||
						tsc->data[SC_GLOOMYDAY] || tsc->data[SC_SONG_OF_MANA] ||
						tsc->data[SC_DANCE_WITH_WUG] || tsc->data[SC_SATURDAY_NIGHT_FEVER] || tsc->data[SC_LERADS_DEW] ||
						tsc->data[SC_MELODYOFSINK] || tsc->data[SC_BEYOND_OF_WARCRY] || tsc->data[SC_UNLIMITED_HUMMING_VOICE] ) &&
						rnd()%100 < 4 * skill_lv + 2 * (sd ? pc->checkskill(sd,WM_LESSON) : 10) + 10 * battle->calc_chorusbonus(sd)) {
					skill->attack(BF_MISC,src,src,bl,skill_id,skill_lv,tick,flag);
					status->change_start(src,bl,SC_STUN,10000,skill_lv,0,0,0,skill->get_time(skill_id,skill_lv),SCFLAG_FIXEDRATE);
					status_change_end(bl, SC_SWING, INVALID_TIMER);
					status_change_end(bl, SC_SYMPHONY_LOVE, INVALID_TIMER);
					status_change_end(bl, SC_MOONLIT_SERENADE, INVALID_TIMER);
					status_change_end(bl, SC_RUSH_WINDMILL, INVALID_TIMER);
					status_change_end(bl, SC_ECHOSONG, INVALID_TIMER);
					status_change_end(bl, SC_HARMONIZE, INVALID_TIMER);
					status_change_end(bl, SC_SIREN, INVALID_TIMER);
					status_change_end(bl, SC_DEEP_SLEEP, INVALID_TIMER);
					status_change_end(bl, SC_SIRCLEOFNATURE, INVALID_TIMER);
					status_change_end(bl, SC_GLOOMYDAY, INVALID_TIMER);
					status_change_end(bl, SC_SONG_OF_MANA, INVALID_TIMER);
					status_change_end(bl, SC_DANCE_WITH_WUG, INVALID_TIMER);
					status_change_end(bl, SC_SATURDAY_NIGHT_FEVER, INVALID_TIMER);
					status_change_end(bl, SC_LERADS_DEW, INVALID_TIMER);
					status_change_end(bl, SC_MELODYOFSINK, INVALID_TIMER);
					status_change_end(bl, SC_BEYOND_OF_WARCRY, INVALID_TIMER);
					status_change_end(bl, SC_UNLIMITED_HUMMING_VOICE, INVALID_TIMER);
				}
			}
			break;

		case SO_POISON_BUSTER:
		{
			struct status_change *tsc = status->get_sc(bl);
			if( tsc && tsc->data[SC_POISON] ) {
				skill->attack(skill->get_type(skill_id), src, src, bl, skill_id, skill_lv, tick, flag);
				status_change_end(bl, SC_POISON, INVALID_TIMER);
			} else if( sd )
				clif->skill_fail(sd, skill_id, USESKILL_FAIL_LEVEL, 0);
		}
			break;

		case GN_SPORE_EXPLOSION:
			if( flag&1 )
				skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag);
			else {
				clif->skill_nodamage(src, bl, skill_id, 0, 1);
				skill->addtimerskill(src, timer->gettick() + skill->get_time(skill_id, skill_lv), bl->id, 0, 0, skill_id, skill_lv, 0, 0);
			}
			break;

		case EL_FIRE_BOMB:
		case EL_FIRE_WAVE:
		case EL_WATER_SCREW:
		case EL_HURRICANE:
		case EL_TYPOON_MIS:
			if( flag&1 )
				skill->attack(skill->get_type(skill_id+1),src,src,bl,skill_id+1,skill_lv,tick,flag);
			else {
				int i = skill->get_splash(skill_id,skill_lv);
				clif->skill_nodamage(src,battle->get_master(src),skill_id,skill_lv,1);
				clif->skill_damage(src, bl, tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
				if( rnd()%100 < 30 )
					map->foreachinrange(skill->area_sub,bl,i,BL_CHAR,src,skill_id,skill_lv,tick,flag|BCT_ENEMY|1,skill->castend_damage_id);
				else
					skill->attack(skill->get_type(skill_id),src,src,bl,skill_id,skill_lv,tick,flag);
			}
			break;

		case EL_ROCK_CRUSHER:
			clif->skill_nodamage(src,battle->get_master(src),skill_id,skill_lv,1);
			clif->skill_damage(src, src, tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
			if( rnd()%100 < 50 )
				skill->attack(BF_MAGIC,src,src,bl,skill_id,skill_lv,tick,flag);
			else
				skill->attack(BF_WEAPON,src,src,bl,EL_ROCK_CRUSHER_ATK,skill_lv,tick,flag);
			break;

		case EL_STONE_RAIN:
			if( flag&1 )
				skill->attack(skill->get_type(skill_id),src,src,bl,skill_id,skill_lv,tick,flag);
			else {
				int i = skill->get_splash(skill_id,skill_lv);
				clif->skill_nodamage(src,battle->get_master(src),skill_id,skill_lv,1);
				clif->skill_damage(src, src, tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
				if( rnd()%100 < 30 )
					map->foreachinrange(skill->area_sub,bl,i,BL_CHAR,src,skill_id,skill_lv,tick,flag|BCT_ENEMY|1,skill->castend_damage_id);
				else
					skill->attack(skill->get_type(skill_id),src,src,bl,skill_id,skill_lv,tick,flag);
			}
			break;

		case EL_FIRE_ARROW:
		case EL_ICE_NEEDLE:
		case EL_WIND_SLASH:
		case EL_STONE_HAMMER:
			clif->skill_nodamage(src,battle->get_master(src),skill_id,skill_lv,1);
			clif->skill_damage(src, bl, tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
			skill->attack(skill->get_type(skill_id),src,src,bl,skill_id,skill_lv,tick,flag);
			break;

		case EL_TIDAL_WEAPON:
			if( src->type == BL_ELEM ) {
				struct elemental_data *ele = BL_CAST(BL_ELEM,src);
				struct status_change *esc = status->get_sc(&ele->bl);
				struct status_change *tsc = status->get_sc(bl);
				sc_type type = status->skill2sc(skill_id), type2;
				type2 = type-1;

				clif->skill_nodamage(src,battle->get_master(src),skill_id,skill_lv,1);
				clif->skill_damage(src, src, tick, status_get_amotion(src), 0, -30000, 1, skill_id, skill_lv, BDT_SKILL);
				if( (esc && esc->data[type2]) || (tsc && tsc->data[type]) ) {
					elemental->clean_single_effect(ele, skill_id);
				}
				if( rnd()%100 < 50 )
					skill->attack(skill->get_type(skill_id),src,src,bl,skill_id,skill_lv,tick,flag);
				else {
					sc_start(src, src,type2,100,skill_lv,skill->get_time(skill_id,skill_lv));
					sc_start(src, battle->get_master(src),type,100,ele->bl.id,skill->get_time(skill_id,skill_lv));
				}
				clif->skill_nodamage(src,src,skill_id,skill_lv,1);
			}
			break;

		// Recursive homun skill
		case MH_MAGMA_FLOW:
		case MH_HEILIGE_STANGE:
			if(flag & 1)
				skill->attack(skill->get_type(skill_id), src, src, bl, skill_id, skill_lv, tick, flag);
			else {
				map->foreachinrange(skill->area_sub, bl, skill->get_splash(skill_id, skill_lv), splash_target(src), src, skill_id, skill_lv, tick, flag | BCT_ENEMY | SD_SPLASH | 1, skill->castend_damage_id);
			}
			break;

		case MH_STAHL_HORN:
		case MH_NEEDLE_OF_PARALYZE:
			skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag);
			break;
		case MH_TINDER_BREAKER:
			if (unit->movepos(src, bl->x, bl->y, 1, 1)) {
	#if PACKETVER >= 20111005
				clif->snap(src, bl->x, bl->y);
	#else
				clif->skill_poseffect(src,skill_id,skill_lv,bl->x,bl->y,tick);
	#endif
			}
					clif->skill_nodamage(src,bl,skill_id,skill_lv,
				sc_start4(src,bl,SC_RG_CCONFINE_S,100,skill_lv,src->id,0,0,skill->get_time(skill_id,skill_lv)));
					skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, flag);
			break;

		case 0:/* no skill - basic/normal attack */
			if(sd) {
				if (flag & 3){
					if (bl->id != skill->area_temp[1])
						skill->attack(BF_WEAPON, src, src, bl, skill_id, skill_lv, tick, SD_LEVEL|flag);
				} else {
					skill->area_temp[1] = bl->id;
					map->foreachinrange(skill->area_sub, bl,
					                    sd->bonus.splash_range, BL_CHAR,
					                    src, skill_id, skill_lv, tick, flag | BCT_ENEMY | 1,
					                    skill->castend_damage_id);
					flag|=1; //Set flag to 1 so ammo is not double-consumed. [Skotlex]
				}
			}
			break;

		default:
			if (skill->castend_damage_id_unknown(src, bl, &skill_id, &skill_lv, &tick, &flag, tstatus, sc))
				return 1;
			break;
	}
