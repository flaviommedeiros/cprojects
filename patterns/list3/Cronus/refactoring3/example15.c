switch(skill_id){
			case SR_GATEOFHELL:
				if (wd.dmg_lv != ATK_FLEE)
					ATK_RATE(battle->calc_skillratio(BF_WEAPON, src, target, skill_id, skill_lv, skillratio, wflag));
				else
					wd.dmg_lv = ATK_DEF;
				break;

			case KO_BAKURETSU:
			{
#ifdef RENEWAL
				GET_NORMAL_ATTACK((sc && sc->data[SC_MAXIMIZEPOWER] ? 1 : 0) | (sc && sc->data[SC_WEAPONPERFECT] ? 8 : 0), skill_id);
#endif
				skillratio = skill_lv * (50 + status_get_dex(src) / 4);
				skillratio = (int)(skillratio * (sd ? pc->checkskill(sd, NJ_TOBIDOUGU) : 10) * 40.f / 100.0f * status->get_lv(src) / 120);
				ATK_RATE(skillratio + 10 * (sd ? sd->status.job_level : 0));
			}
				break;

	#ifdef RENEWAL
			case GS_MAGICALBULLET:
				GET_NORMAL_ATTACK((sc && sc->data[SC_MAXIMIZEPOWER] ? 1 : 0) | (sc && sc->data[SC_WEAPONPERFECT] ? 8 : 0), skill_id);
				ATK_ADD(battle->attr_fix(src, target,
					battle->calc_cardfix(BF_MAGIC, src, target, nk, s_ele, 0, status->get_matk(src, 2), 0, wd.flag), ELE_NEUTRAL, tstatus->def_ele, tstatus->ele_lv));
				break;
			case GS_PIERCINGSHOT:
				GET_NORMAL_ATTACK((sc && sc->data[SC_MAXIMIZEPOWER] ? 1 : 0) | (sc && sc->data[SC_WEAPONPERFECT] ? 8 : 0), 0);
				if ( wd.damage ) {
					if ( sd && sd->weapontype1 == W_RIFLE )
						ATK_RATE(30 * (skill_lv + 5));
					else
						ATK_RATE(20 * (skill_lv + 5));
				}
				break;
			case MO_EXTREMITYFIST: // [malufett]
			{
				short totaldef = status->get_total_def(target);
				GET_NORMAL_ATTACK((sc && sc->data[SC_MAXIMIZEPOWER] ? 1 : 0) | 8, skill_id);
				if ( wd.damage ) {
					ATK_ADD(250 * (skill_lv + 1) + (10 * (status_get_sp(src) + 1) * wd.damage / 100) + (8 * wd.damage));
					ATK_ADD(-totaldef);
				}
			}
				break;
			case PA_SHIELDCHAIN:
				GET_NORMAL_ATTACK((sc && sc->data[SC_MAXIMIZEPOWER] ? 1 : 0) | (sc && sc->data[SC_WEAPONPERFECT] ? 8 : 0), skill_id);
				if ( sd ) {
					short index = sd->equip_index[EQI_HAND_L];
					if ( index >= 0 && sd->inventory_data[index] && sd->inventory_data[index]->type == IT_ARMOR ) {
						ATK_ADD(sd->inventory_data[index]->weight / 10 + 4 * sd->status.inventory[index].refine);
					}
				} else
					ATK_ADD(sstatus->rhw.atk2); //Else use Atk2
				ATK_RATE(battle->calc_skillratio(BF_WEAPON, src, target, skill_id, skill_lv, skillratio, wflag));
				break;
			case AM_DEMONSTRATION:
			case AM_ACIDTERROR: // [malufett/Hercules]
			{
				int64 matk;
				int totaldef = status->get_total_def(target) + status->get_total_mdef(target);
				matk = battle->calc_cardfix(BF_MAGIC, src, target, nk, s_ele, 0, status->get_matk(src, 2), 0, wd.flag);
				matk = battle->attr_fix(src, target, matk, ELE_NEUTRAL, tstatus->def_ele, tstatus->ele_lv);
				matk = matk * battle->calc_skillratio(BF_WEAPON, src, target, skill_id, skill_lv, skillratio, wflag) / 100;
				GET_NORMAL_ATTACK((sc && sc->data[SC_MAXIMIZEPOWER] ? 1 : 0) | (sc && sc->data[SC_WEAPONPERFECT] ? 8 : 0), 0);
				ATK_RATE(battle->calc_skillratio(BF_WEAPON, src, target, skill_id, skill_lv, skillratio, wflag));
				ATK_ADD(matk);
				ATK_ADD(-totaldef);
				if ( skill_id == AM_ACIDTERROR && is_boss(target) )
					ATK_RATE(50);
				if ( skill_id == AM_DEMONSTRATION )
					wd.damage = max(wd.damage, 1);
			}
				break;
			case GN_CARTCANNON:
				GET_NORMAL_ATTACK((sc && sc->data[SC_MAXIMIZEPOWER] ? 1 : 0) | (sc && sc->data[SC_WEAPONPERFECT] ? 8 : 0), skill_id);
				ATK_ADD(sd ? sd->bonus.arrow_atk : 0);
				wd.damage = battle->calc_masteryfix(src, target, skill_id, skill_lv, wd.damage, wd.div_, 0, flag.weapon);
				ATK_RATE(battle->calc_skillratio(BF_WEAPON, src, target, skill_id, skill_lv, skillratio, wflag));
				if ( sd && s_ele != sd->bonus.arrow_ele )
					s_ele = sd->bonus.arrow_ele;
				break;
			case NJ_TATAMIGAESHI:
					ATK_RATE(200);
				/* Fall through */
			case LK_SPIRALPIERCE:
			case ML_SPIRALPIERCE: // [malufett]
				if( skill_id != NJ_TATAMIGAESHI ){
					short index = sd?sd->equip_index[EQI_HAND_R]:0;
					GET_NORMAL_ATTACK( (sc && sc->data[SC_MAXIMIZEPOWER]?1:0)|(sc && sc->data[SC_WEAPONPERFECT]?8:0), 0);
					wd.damage = wd.damage * 70 / 100;
					//n_ele = true; // FIXME: This is has no effect if it's after GET_NORMAL_ATTACK (was this intended, or was it supposed to be put above?)

					if (sd && index >= 0 &&
						sd->inventory_data[index] &&
						sd->inventory_data[index]->type == IT_WEAPON)
						ATK_ADD(sd->inventory_data[index]->weight * 7 / 100);

					switch (tstatus->size) {
						case SZ_SMALL: //Small: 115%
							ATK_RATE(115);
							break;
						case SZ_BIG: //Large: 85%
							ATK_RATE(85);
					}
					wd.damage = battle->calc_masteryfix(src, target, skill_id, skill_lv, wd.damage, wd.div_, 0, flag.weapon);
					wd.damage = battle->calc_cardfix2(src, target, wd.damage, s_ele, nk, wd.flag);
				}
				/* Fall through */
	#endif
			default:
				ATK_RATE(battle->calc_skillratio(BF_WEAPON, src, target, skill_id, skill_lv, skillratio, wflag));
		}
