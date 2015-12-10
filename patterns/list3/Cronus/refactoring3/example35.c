switch( group->unit_id ) {
			case UNT_BLASTMINE:
#ifdef RENEWAL
			case UNT_CLAYMORETRAP:
#endif
			case UNT_GROUNDDRIFT_WIND:
			case UNT_GROUNDDRIFT_DARK:
			case UNT_GROUNDDRIFT_POISON:
			case UNT_GROUNDDRIFT_WATER:
			case UNT_GROUNDDRIFT_FIRE:
				group->unit_id = UNT_USED_TRAPS;
				//clif->changetraplook(bl, UNT_FIREPILLAR_ACTIVE);
				group->limit=DIFF_TICK32(tick+1500,group->tick);
				su->limit=DIFF_TICK32(tick+1500,group->tick);
			break;

			case UNT_ANKLESNARE:
			case UNT_ELECTRICSHOCKER:
				if( group->val2 > 0 || group->val3 == SC_ESCAPE ) {
					// Used Trap don't returns back to item
					skill->delunit(su);
					break;
				}
			case UNT_SKIDTRAP:
			case UNT_LANDMINE:
			case UNT_SHOCKWAVE:
			case UNT_SANDMAN:
			case UNT_FLASHER:
			case UNT_FREEZINGTRAP:
#ifndef RENEWAL
			case UNT_CLAYMORETRAP:
#endif
			case UNT_TALKIEBOX:
			case UNT_CLUSTERBOMB:
			case UNT_MAGENTATRAP:
			case UNT_COBALTTRAP:
			case UNT_MAIZETRAP:
			case UNT_VERDURETRAP:
			case UNT_FIRINGTRAP:
			case UNT_ICEBOUNDTRAP:

			{
				struct block_list* src;
				if( su->val1 > 0 && (src = map->id2bl(group->src_id)) != NULL && src->type == BL_PC ) {
					// revert unit back into a trap
					struct item item_tmp;
					memset(&item_tmp,0,sizeof(item_tmp));
					item_tmp.nameid = group->item_id?group->item_id:ITEMID_TRAP;
					item_tmp.identify = 1;
					map->addflooritem(bl, &item_tmp, 1, bl->m, bl->x, bl->y, 0, 0, 0, 0);
				}
				skill->delunit(su);
			}
			break;

			case UNT_WARP_ACTIVE:
				// warp portal opens (morph to a UNT_WARP_WAITING cell)
				group->unit_id = skill->get_unit_id(group->skill_id, 1); // UNT_WARP_WAITING
				clif->changelook(&su->bl, LOOK_BASE, group->unit_id);
				// restart timers
				group->limit = skill->get_time(group->skill_id,group->skill_lv);
				su->limit = skill->get_time(group->skill_id,group->skill_lv);
				// apply effect to all units standing on it
				map->foreachincell(skill->unit_effect,su->bl.m,su->bl.x,su->bl.y,group->bl_flag,&su->bl,timer->gettick(),1);
			break;

			case UNT_CALLFAMILY:
			{
				struct map_session_data *sd = NULL;
				if(group->val1) {
					sd = map->charid2sd(group->val1);
					group->val1 = 0;
					if (sd && !map->list[sd->bl.m].flag.nowarp)
						pc->setpos(sd,map_id2index(su->bl.m),su->bl.x,su->bl.y,CLR_TELEPORT);
				}
				if(group->val2) {
					sd = map->charid2sd(group->val2);
					group->val2 = 0;
					if (sd && !map->list[sd->bl.m].flag.nowarp)
						pc->setpos(sd,map_id2index(su->bl.m),su->bl.x,su->bl.y,CLR_TELEPORT);
				}
				skill->delunit(su);
			}
			break;

			case UNT_REVERBERATION:
				if( su->val1 <= 0 ) { // If it was deactivated.
					skill->delunit(su);
					break;
				}
				clif->changetraplook(bl,UNT_USED_TRAPS);
				map->foreachinrange(skill->trap_splash, bl, skill->get_splash(group->skill_id, group->skill_lv), group->bl_flag, bl, tick);
				group->limit = DIFF_TICK32(tick,group->tick)+1500;
				su->limit = DIFF_TICK32(tick,group->tick)+1500;
				group->unit_id = UNT_USED_TRAPS;
			break;

			case UNT_FEINTBOMB: {
				struct block_list *src = map->id2bl(group->src_id);
				if( src ) {
					map->foreachinrange(skill->area_sub, &su->bl, su->range, splash_target(src), src, SC_FEINTBOMB, group->skill_lv, tick, BCT_ENEMY|SD_ANIMATION|1, skill->castend_damage_id);
					status_change_end(src, SC__FEINTBOMB_MASTER, INVALID_TIMER);
				}
				skill->delunit(su);
				break;
			}

			case UNT_BANDING:
			{
				struct block_list *src = map->id2bl(group->src_id);
				struct status_change *sc;
				if( !src || (sc = status->get_sc(src)) == NULL || !sc->data[SC_BANDING] ) {
					skill->delunit(su);
					break;
				}
				// This unit isn't removed while SC_BANDING is active.
				group->limit = DIFF_TICK32(tick+group->interval,group->tick);
				su->limit = DIFF_TICK32(tick+group->interval,group->tick);
			}
			break;

			default:
				skill->delunit(su);
		}
