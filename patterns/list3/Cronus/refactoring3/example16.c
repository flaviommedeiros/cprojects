switch (skill_id) {
#ifdef RENEWAL
			case HW_MAGICCRASHER:
				ATK_ADD(battle->calc_magic_attack(src, target, skill_id, skill_lv, wflag).damage / 5);
				break;
#else
			case MO_EXTREMITYFIST:
				ATK_ADD(250 + 150*skill_lv);
				break;
#endif
			case TK_DOWNKICK:
			case TK_STORMKICK:
			case TK_TURNKICK:
			case TK_COUNTER:
			case TK_JUMPKICK:
				//TK_RUN kick damage bonus.
				if(sd && sd->weapontype1 == W_FIST && sd->weapontype2 == W_FIST)
					ATK_ADD(10*pc->checkskill(sd, TK_RUN));
				break;

#ifndef RENEWAL
			case GS_MAGICALBULLET:
				ATK_ADD( status->get_matk(src, 2) );
				break;
			case NJ_SYURIKEN:
				ATK_ADD(4*skill_lv);
#endif
				break;
			case GC_COUNTERSLASH:
				ATK_ADD( status_get_agi(src) * 2 + (sd?sd->status.job_level:0) * 4 );
				break;
			case RA_WUGDASH:
				if( sc && sc->data[SC_DANCE_WITH_WUG] )
					ATK_ADD(2 * sc->data[SC_DANCE_WITH_WUG]->val1 * (2 + battle->calc_chorusbonus(sd)));
				break;
			case SR_TIGERCANNON:
				ATK_ADD( skill_lv * 240 + status->get_lv(target) * 40 );
				if( sc && sc->data[SC_COMBOATTACK]
					&& sc->data[SC_COMBOATTACK]->val1 == SR_FALLENEMPIRE )
						ATK_ADD( skill_lv * 500 + status->get_lv(target) * 40 );
				break;
			case RA_WUGSTRIKE:
			case RA_WUGBITE:
				if(sd)
					ATK_ADD(30*pc->checkskill(sd, RA_TOOTHOFWUG));
				if( sc && sc->data[SC_DANCE_WITH_WUG] )
					ATK_ADD(2 * sc->data[SC_DANCE_WITH_WUG]->val1 * (2 + battle->calc_chorusbonus(sd)));
				break;
			case LG_SHIELDPRESS:
				if( sd ) {
					int damagevalue = 0;
					short index = sd->equip_index[EQI_HAND_L];
					if( index >= 0 && sd->inventory_data[index] && sd->inventory_data[index]->type == IT_ARMOR )
						damagevalue = sstatus->vit * sd->status.inventory[index].refine;
					ATK_ADD(damagevalue);
				}
				break;
			case SR_GATEOFHELL:
				ATK_ADD(sstatus->max_hp - status_get_hp(src));
				if ( sc && sc->data[SC_COMBOATTACK] && sc->data[SC_COMBOATTACK]->val1 == SR_FALLENEMPIRE ) {
					ATK_ADD((sstatus->max_sp * (1 + skill_lv * 2 / 10)) + 40 * status->get_lv(src));
				} else {
					ATK_ADD((sstatus->sp * (1 + skill_lv * 2 / 10)) + 10 * status->get_lv(src));
				}
				break;
			case SR_FALLENEMPIRE:// [(Target Size value + Skill Level - 1) x Caster STR] + [(Target current weight x Caster DEX / 120)]
				ATK_ADD( ((tstatus->size+1)*2 + (int64)skill_lv - 1) * sstatus->str);
				if( tsd && tsd->weight ){
					ATK_ADD( (tsd->weight/10) * sstatus->dex / 120 );
				}else{
					ATK_ADD( status->get_lv(target) * 50 ); //mobs
				}
				break;
			case KO_SETSUDAN:
				if( tsc && tsc->data[SC_SOULLINK] ){
					ATK_ADDRATE(200*tsc->data[SC_SOULLINK]->val1);
					status_change_end(target,SC_SOULLINK,INVALID_TIMER);
				}
				break;
			case KO_MAKIBISHI:
				wd.damage = 20 * skill_lv;
				break;
		}
