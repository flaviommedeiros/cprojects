switch (skill_id) {
			//Calc base damage according to skill
			case PA_SACRIFICE:
				wd.damage = sstatus->max_hp* 9/100;
				wd.damage2 = 0;
#ifdef RENEWAL
				wd.damage = battle->calc_elefix(src, target, skill_id, skill_lv, wd.damage, nk, n_ele, s_ele, s_ele_, false, wd.flag); // temporary [malufett]
#endif
				break;
			case NJ_ISSEN: // [malufett]
#ifndef RENEWAL
				wd.damage = 40*sstatus->str +skill_lv*(sstatus->hp/10 + 35);
				wd.damage2 = 0;
#else
				{
					short totaldef = status->get_total_def(target);
					i = 0;
					GET_NORMAL_ATTACK( (sc && sc->data[SC_MAXIMIZEPOWER]?1:0)|(sc && sc->data[SC_WEAPONPERFECT]?8:0), 0 );
					if( sc && sc->data[SC_NJ_BUNSINJYUTSU] && (i=sc->data[SC_NJ_BUNSINJYUTSU]->val2) > 0 )
						wd.div_ = ~( i++ + 2 ) + 1;
					if( wd.damage ){
						wd.damage *= sstatus->hp * skill_lv;
						wd.damage = wd.damage / sstatus->max_hp + sstatus->hp + i * (wd.damage / sstatus->max_hp + sstatus->hp) / 5;
					}
					ATK_ADD(-totaldef);
					if( is_boss(target) )
						ATK_RATE(50);
				}
				break;
			case NJ_SYURIKEN: // [malufett]
				GET_NORMAL_ATTACK( (sc && sc->data[SC_MAXIMIZEPOWER]?1:0)|(sc && sc->data[SC_WEAPONPERFECT]?8:0), 0);
				ATK_ADD(battle->calc_masteryfix(src, target, skill_id, skill_lv, 4 * skill_lv + (sd ? sd->bonus.arrow_atk : 0), wd.div_, 0, flag.weapon));
#endif
				break;
#ifndef RENEWAL
			case LK_SPIRALPIERCE:
			case ML_SPIRALPIERCE:
				if (sd) {
					short index = sd->equip_index[EQI_HAND_R];

					if (index >= 0 &&
						sd->inventory_data[index] &&
						sd->inventory_data[index]->type == IT_WEAPON)
						wd.damage = sd->inventory_data[index]->weight*8/100; //80% of weight
					ATK_ADDRATE(50*skill_lv); //Skill modifier applies to weight only.
				} else {
					wd.damage = battle->calc_base_damage2(sstatus, &sstatus->rhw, sc, tstatus->size, sd, 0); //Monsters have no weight and use ATK instead
				}
				i = sstatus->str/10;
				i*=i;
				ATK_ADD(i); //Add str bonus.
				switch (tstatus->size) { //Size-fix. Is this modified by weapon perfection?
					case SZ_SMALL: //Small: 125%
						ATK_RATE(125);
						break;
					//case SZ_MEDIUM: //Medium: 100%
					case SZ_BIG: //Large: 75%
						ATK_RATE(75);
						break;
				}
				break;

			case PA_SHIELDCHAIN:
#endif
			case CR_SHIELDBOOMERANG:
				wd.damage = sstatus->batk;
				if (sd) {
					int damagevalue = 0;
					short index = sd->equip_index[EQI_HAND_L];

					if( index >= 0 && sd->inventory_data[index] && sd->inventory_data[index]->type == IT_ARMOR )
						damagevalue = sd->inventory_data[index]->weight/10;
					ATK_ADD(damagevalue);
				} else
					ATK_ADD(sstatus->rhw.atk2); //Else use Atk2
				break;
			case HFLI_SBR44: //[orn]
				if(src->type == BL_HOM) {
					wd.damage = ((TBL_HOM*)src)->homunculus.intimacy ;
					break;
				}
			default:
			{
				i = (flag.cri
#ifdef RENEWAL
					|| (sc && sc->data[SC_MAXIMIZEPOWER])
#endif
					?1:0)|
					(flag.arrow?2:0)|
#ifndef RENEWAL
					(skill_id == HW_MAGICCRASHER?4:0)|
					(skill_id == MO_EXTREMITYFIST?8:0)|
#endif
					(!skill_id && sc && sc->data[SC_HLIF_CHANGE]?4:0)|
					(sc && sc->data[SC_WEAPONPERFECT]?8:0);
				if (flag.arrow && sd)
				switch(sd->status.weapon) {
					case W_BOW:
					case W_REVOLVER:
					case W_GATLING:
					case W_SHOTGUN:
					case W_GRENADE:
						break;
					default:
						i |= 16; // for ex. shuriken must not be influenced by DEX
				}
#ifdef RENEWAL
				GET_NORMAL_ATTACK( i, skill_id);
				wd.damage = battle->calc_masteryfix(src, target, skill_id, skill_lv, wd.damage, wd.div_, 0, flag.weapon);
				wd.damage = battle->calc_cardfix2(src, target, wd.damage, s_ele, nk, wd.flag);
				if (flag.lh){
					GET_NORMAL_ATTACK2( i, skill_id );
					wd.damage2 = battle->calc_masteryfix(src, target, skill_id, skill_lv, wd.damage2, wd.div_, 1, flag.weapon);
					wd.damage2 = battle->calc_cardfix2(src, target, wd.damage2, s_ele, nk, wd.flag);
				}
#else
				wd.damage = battle->calc_base_damage2(sstatus, &sstatus->rhw, sc, tstatus->size, sd, i);
				if (flag.lh)
					wd.damage2 = battle->calc_base_damage2(sstatus, &sstatus->lhw, sc, tstatus->size, sd, i);
#endif
				if (nk&NK_SPLASHSPLIT){ // Divide ATK among targets
					if(wflag>0)
						wd.damage/= wflag;
					else
						ShowError("0 enemies targeted by %d:%s, divide per 0 avoided!\n", skill_id, skill->get_name(skill_id));
				}

				//Add any bonuses that modify the base baseatk+watk (pre-skills)
				if(sd) {
#ifndef RENEWAL
					if (sd->bonus.atk_rate)
						ATK_ADDRATE(sd->bonus.atk_rate);
#endif
					if(flag.cri && sd->bonus.crit_atk_rate)
						ATK_ADDRATE(sd->bonus.crit_atk_rate);
					if(flag.cri && sc && sc->data[SC_MTF_CRIDAMAGE])
						ATK_ADDRATE(25);// temporary it should be 'bonus.crit_atk_rate'
#ifndef RENEWAL

					if(sd->status.party_id && (temp=pc->checkskill(sd,TK_POWER)) > 0){
						if( (i = party->foreachsamemap(party->sub_count, sd, 0)) > 1 ) // exclude the player himself [Inkfish]
							ATK_ADDRATE(2*temp*i);
					}
#endif
				}
				break;
			} //End default case
		}
