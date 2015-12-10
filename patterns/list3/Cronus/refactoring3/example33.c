switch (sg->skill_id) {
				case SG_SUN_WARM: //SG skills [Komurka]
				case SG_MOON_WARM:
				case SG_STAR_WARM:
				{
					int count = 0;
					const int x = bl->x, y = bl->y;

					map->freeblock_lock();
					//If target isn't knocked back it should hit every "interval" ms [Playtester]
					do {
						if( bl->type == BL_PC )
							status_zap(bl, 0, 15); // sp damage to players
						else if( status->charge(ss, 0, 2) ) { // mobs
							// costs 2 SP per hit
							if( !skill->attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick+count*sg->interval,0) )
								status->charge(ss, 0, 8); //costs additional 8 SP if miss
						} else { // mobs
							//should end when out of sp.
							sg->limit = DIFF_TICK32(tick,sg->tick);
							break;
						}
					} while( x == bl->x && y == bl->y && sg->alive_count
					      && ++count < SKILLUNITTIMER_INTERVAL/sg->interval && !status->isdead(bl) );
					map->freeblock_unlock();
				}
				break;
		/**
		 * The storm gust counter was dropped in renewal
		 **/
		#ifndef RENEWAL
				case WZ_STORMGUST: //SG counter does not reset per stormgust. IE: One hit from a SG and two hits from another will freeze you.
					if (tsc)
						tsc->sg_counter++; //SG hit counter.
					if (skill->attack(skill->get_type(sg->skill_id),ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0) <= 0 && tsc)
						tsc->sg_counter=0; //Attack absorbed.
				break;
		#endif
				case GS_DESPERADO:
					if (rnd()%100 < src->val1)
						skill->attack(BF_WEAPON,ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
				break;
				default:
					skill->attack(skill->get_type(sg->skill_id),ss,&src->bl,bl,sg->skill_id,sg->skill_lv,tick,0);
			}
