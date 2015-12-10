switch(type){
		case SP_STR:
		case SP_AGI:
		case SP_VIT:
		case SP_INT:
		case SP_DEX:
		case SP_LUK:
			if(sd->state.lr_flag != 2)
				sd->param_bonus[type-SP_STR]+=val;
			break;
		case SP_ATK1:
			if(!sd->state.lr_flag) {
				bonus = bst->rhw.atk + val;
				bst->rhw.atk = cap_value(bonus, 0, USHRT_MAX);
			}
			else if(sd->state.lr_flag == 1) {
				bonus = bst->lhw.atk + val;
				bst->lhw.atk =  cap_value(bonus, 0, USHRT_MAX);
			}
			break;
		case SP_ATK2:
			if(!sd->state.lr_flag) {
				bonus = bst->rhw.atk2 + val;
				bst->rhw.atk2 = cap_value(bonus, 0, USHRT_MAX);
			}
			else if(sd->state.lr_flag == 1) {
				bonus = bst->lhw.atk2 + val;
				bst->lhw.atk2 =  cap_value(bonus, 0, USHRT_MAX);
			}
			break;
		case SP_BASE_ATK:
			if(sd->state.lr_flag != 2) {
#ifdef RENEWAL
				bst->equip_atk += val;
#else
				bonus = bst->batk + val;
				bst->batk = cap_value(bonus, 0, USHRT_MAX);
#endif
			}
			break;
		case SP_DEF1:
			if(sd->state.lr_flag != 2) {
				bonus = bst->def + val;
	#ifdef RENEWAL
				bst->def = cap_value(bonus, SHRT_MIN, SHRT_MAX);
	#else
				bst->def = cap_value(bonus, CHAR_MIN, CHAR_MAX);
	#endif
			}
			break;
		case SP_DEF2:
			if(sd->state.lr_flag != 2) {
				bonus = bst->def2 + val;
				bst->def2 = cap_value(bonus, SHRT_MIN, SHRT_MAX);
			}
			break;
		case SP_MDEF1:
			if(sd->state.lr_flag != 2) {
				bonus = bst->mdef + val;
	#ifdef RENEWAL
				bst->mdef = cap_value(bonus, SHRT_MIN, SHRT_MAX);
	#else
				bst->mdef = cap_value(bonus, CHAR_MIN, CHAR_MAX);
	#endif
				if( sd->state.lr_flag == 3 ) {//Shield, used for royal guard
					sd->bonus.shieldmdef += bonus;
				}
			}
			break;
		case SP_MDEF2:
			if(sd->state.lr_flag != 2) {
				bonus = bst->mdef2 + val;
				bst->mdef2 = cap_value(bonus, SHRT_MIN, SHRT_MAX);
			}
			break;
		case SP_HIT:
			if(sd->state.lr_flag != 2) {
				bonus = bst->hit + val;
				bst->hit = cap_value(bonus, SHRT_MIN, SHRT_MAX);
			} else
				sd->bonus.arrow_hit+=val;
			break;
		case SP_FLEE1:
			if(sd->state.lr_flag != 2) {
				bonus = bst->flee + val;
				bst->flee = cap_value(bonus, SHRT_MIN, SHRT_MAX);
			}
			break;
		case SP_FLEE2:
			if(sd->state.lr_flag != 2) {
				bonus = bst->flee2 + val*10;
				bst->flee2 = cap_value(bonus, SHRT_MIN, SHRT_MAX);
			}
			break;
		case SP_CRITICAL:
			if(sd->state.lr_flag != 2) {
				bonus = bst->cri + val*10;
				bst->cri = cap_value(bonus, SHRT_MIN, SHRT_MAX);
			} else
				sd->bonus.arrow_cri += val*10;
			break;
		case SP_ATKELE:
			if(val >= ELE_MAX) {
				ShowError("pc_bonus: SP_ATKELE: Invalid element %d\n", val);
				break;
			}
			switch (sd->state.lr_flag) {
			case 2:
				switch (sd->status.weapon) {
					case W_BOW:
					case W_REVOLVER:
					case W_RIFLE:
					case W_GATLING:
					case W_SHOTGUN:
					case W_GRENADE:
						//Become weapon element.
						bst->rhw.ele=val;
						break;
					default: //Become arrow element.
						sd->bonus.arrow_ele=val;
						break;
				}
				break;
			case 1:
				bst->lhw.ele=val;
				break;
			default:
				bst->rhw.ele=val;
				break;
			}
			break;
		case SP_DEFELE:
			if(val >= ELE_MAX) {
				ShowError("pc_bonus: SP_DEFELE: Invalid element %d\n", val);
				break;
			}
			if(sd->state.lr_flag != 2)
				bst->def_ele=val;
			break;
		case SP_MAXHP:
			if(sd->state.lr_flag == 2)
				break;
			val += (int)bst->max_hp;
			//Negative bonuses will underflow, this will be handled in status_calc_pc through casting
			//If this is called outside of status_calc_pc, you'd better pray they do not underflow and end with UINT_MAX max_hp.
			bst->max_hp = (unsigned int)val;
			break;
		case SP_MAXSP:
			if(sd->state.lr_flag == 2)
				break;
			val += (int)bst->max_sp;
			bst->max_sp = (unsigned int)val;
			break;
	#ifndef RENEWAL_CAST
		case SP_VARCASTRATE:
	#endif
		case SP_CASTRATE:
			if(sd->state.lr_flag != 2)
				sd->castrate+=val;
			break;
		case SP_MAXHPRATE:
			if(sd->state.lr_flag != 2)
				sd->hprate+=val;
			break;
		case SP_MAXSPRATE:
			if(sd->state.lr_flag != 2)
				sd->sprate+=val;
			break;
		case SP_SPRATE:
			if(sd->state.lr_flag != 2)
				sd->dsprate+=val;
			break;
		case SP_ATTACKRANGE:
			switch (sd->state.lr_flag) {
			case 2:
				switch (sd->status.weapon) {
					case W_BOW:
					case W_REVOLVER:
					case W_RIFLE:
					case W_GATLING:
					case W_SHOTGUN:
					case W_GRENADE:
						bst->rhw.range += val;
				}
				break;
			case 1:
				bst->lhw.range += val;
				break;
			default:
				bst->rhw.range += val;
				break;
			}
			break;
		case SP_SPEED_RATE: //Non stackable increase
			if(sd->state.lr_flag != 2)
				sd->bonus.speed_rate = min(sd->bonus.speed_rate, -val);
			break;
		case SP_SPEED_ADDRATE: //Stackable increase
			if(sd->state.lr_flag != 2)
				sd->bonus.speed_add_rate -= val;
			break;
		case SP_ASPD: //Raw increase
			if(sd->state.lr_flag != 2)
				sd->bonus.aspd_add -= 10*val;
			break;
		case SP_ASPD_RATE: //Stackable increase - Made it linear as per rodatazone
			if(sd->state.lr_flag != 2)
	#ifndef RENEWAL_ASPD
				bst->aspd_rate -= 10*val;
	#else
				bst->aspd_rate2 += val;
	#endif
			break;
		case SP_HP_RECOV_RATE:
			if(sd->state.lr_flag != 2)
				sd->hprecov_rate += val;
			break;
		case SP_SP_RECOV_RATE:
			if(sd->state.lr_flag != 2)
				sd->sprecov_rate += val;
			break;
		case SP_CRITICAL_DEF:
			if(sd->state.lr_flag != 2)
				sd->bonus.critical_def += val;
			break;
		case SP_NEAR_ATK_DEF:
			if(sd->state.lr_flag != 2)
				sd->bonus.near_attack_def_rate += val;
			break;
		case SP_LONG_ATK_DEF:
			if(sd->state.lr_flag != 2)
				sd->bonus.long_attack_def_rate += val;
			break;
		case SP_DOUBLE_RATE:
			if(sd->state.lr_flag == 0 && sd->bonus.double_rate < val)
				sd->bonus.double_rate = val;
			break;
		case SP_DOUBLE_ADD_RATE:
			if(sd->state.lr_flag == 0)
				sd->bonus.double_add_rate += val;
			break;
		case SP_MATK_RATE:
			if(sd->state.lr_flag != 2)
				sd->matk_rate += val;
			break;
		case SP_IGNORE_DEF_ELE:
			if(val >= ELE_MAX) {
				ShowError("pc_bonus: SP_IGNORE_DEF_ELE: Invalid element %d\n", val);
				break;
			}
			if(!sd->state.lr_flag)
				sd->right_weapon.ignore_def_ele |= 1<<val;
			else if(sd->state.lr_flag == 1)
				sd->left_weapon.ignore_def_ele |= 1<<val;
			break;
		case SP_IGNORE_DEF_RACE:
			if(!sd->state.lr_flag)
				sd->right_weapon.ignore_def_race |= 1<<val;
			else if(sd->state.lr_flag == 1)
				sd->left_weapon.ignore_def_race |= 1<<val;
			break;
		case SP_ATK_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.atk_rate += val;
			break;
		case SP_MAGIC_ATK_DEF:
			if(sd->state.lr_flag != 2)
				sd->bonus.magic_def_rate += val;
			break;
		case SP_MISC_ATK_DEF:
			if(sd->state.lr_flag != 2)
				sd->bonus.misc_def_rate += val;
			break;
		case SP_IGNORE_MDEF_RATE:
			if(sd->state.lr_flag != 2) {
				sd->ignore_mdef[RC_NONBOSS] += val;
				sd->ignore_mdef[RC_BOSS] += val;
			}
			break;
		case SP_IGNORE_MDEF_ELE:
			if(val >= ELE_MAX) {
				ShowError("pc_bonus: SP_IGNORE_MDEF_ELE: Invalid element %d\n", val);
				break;
			}
			if(sd->state.lr_flag != 2)
				sd->bonus.ignore_mdef_ele |= 1<<val;
			break;
		case SP_IGNORE_MDEF_RACE:
			if(sd->state.lr_flag != 2)
				sd->bonus.ignore_mdef_race |= 1<<val;
			break;
		case SP_PERFECT_HIT_RATE:
			if(sd->state.lr_flag != 2 && sd->bonus.perfect_hit < val)
				sd->bonus.perfect_hit = val;
			break;
		case SP_PERFECT_HIT_ADD_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.perfect_hit_add += val;
			break;
		case SP_CRITICAL_RATE:
			if(sd->state.lr_flag != 2)
				sd->critical_rate+=val;
			break;
		case SP_DEF_RATIO_ATK_ELE:
			if(val >= ELE_MAX) {
				ShowError("pc_bonus: SP_DEF_RATIO_ATK_ELE: Invalid element %d\n", val);
				break;
			}
			if(!sd->state.lr_flag)
				sd->right_weapon.def_ratio_atk_ele |= 1<<val;
			else if(sd->state.lr_flag == 1)
				sd->left_weapon.def_ratio_atk_ele |= 1<<val;
			break;
		case SP_DEF_RATIO_ATK_RACE:
			if(val >= RC_MAX) {
				ShowError("pc_bonus: SP_DEF_RATIO_ATK_RACE: Invalid race %d\n", val);
				break;
			}
			if(!sd->state.lr_flag)
				sd->right_weapon.def_ratio_atk_race |= 1<<val;
			else if(sd->state.lr_flag == 1)
				sd->left_weapon.def_ratio_atk_race |= 1<<val;
			break;
		case SP_HIT_RATE:
			if(sd->state.lr_flag != 2)
				sd->hit_rate += val;
			break;
		case SP_FLEE_RATE:
			if(sd->state.lr_flag != 2)
				sd->flee_rate += val;
			break;
		case SP_FLEE2_RATE:
			if(sd->state.lr_flag != 2)
				sd->flee2_rate += val;
			break;
		case SP_DEF_RATE:
			if(sd->state.lr_flag != 2)
				sd->def_rate += val;
			break;
		case SP_DEF2_RATE:
			if(sd->state.lr_flag != 2)
				sd->def2_rate += val;
			break;
		case SP_MDEF_RATE:
			if(sd->state.lr_flag != 2)
				sd->mdef_rate += val;
			break;
		case SP_MDEF2_RATE:
			if(sd->state.lr_flag != 2)
				sd->mdef2_rate += val;
			break;
		case SP_RESTART_FULL_RECOVER:
			if(sd->state.lr_flag != 2)
				sd->special_state.restart_full_recover = 1;
			break;
		case SP_NO_CASTCANCEL:
			if(sd->state.lr_flag != 2)
				sd->special_state.no_castcancel = 1;
			break;
		case SP_NO_CASTCANCEL2:
			if(sd->state.lr_flag != 2)
				sd->special_state.no_castcancel2 = 1;
			break;
		case SP_NO_SIZEFIX:
			if(sd->state.lr_flag != 2)
				sd->special_state.no_sizefix = 1;
			break;
		case SP_NO_MAGIC_DAMAGE:
			if(sd->state.lr_flag == 2)
				break;
			val+= sd->special_state.no_magic_damage;
			sd->special_state.no_magic_damage = cap_value(val,0,100);
			break;
		case SP_NO_WEAPON_DAMAGE:
			if(sd->state.lr_flag == 2)
				break;
			val+= sd->special_state.no_weapon_damage;
			sd->special_state.no_weapon_damage = cap_value(val,0,100);
			break;
		case SP_NO_MISC_DAMAGE:
			if(sd->state.lr_flag == 2)
				break;
			val+= sd->special_state.no_misc_damage;
			sd->special_state.no_misc_damage = cap_value(val,0,100);
			break;
		case SP_NO_GEMSTONE:
			if(sd->state.lr_flag != 2)
				sd->special_state.no_gemstone = 1;
			break;
		case SP_INTRAVISION: // Maya Purple Card effect allowing to see Hiding/Cloaking people [DracoRPG]
			if(sd->state.lr_flag != 2) {
				sd->special_state.intravision = 1;
				clif->status_change(&sd->bl, SI_CLAIRVOYANCE, 1, 0, 0, 0, 0);
			}
			break;
		case SP_NO_KNOCKBACK:
			if(sd->state.lr_flag != 2)
				sd->special_state.no_knockback = 1;
			break;
		case SP_SPLASH_RANGE:
			if(sd->bonus.splash_range < val)
				sd->bonus.splash_range = val;
			break;
		case SP_SPLASH_ADD_RANGE:
			sd->bonus.splash_add_range += val;
			break;
		case SP_SHORT_WEAPON_DAMAGE_RETURN:
			if(sd->state.lr_flag != 2)
				sd->bonus.short_weapon_damage_return += val;
			break;
		case SP_LONG_WEAPON_DAMAGE_RETURN:
			if(sd->state.lr_flag != 2)
				sd->bonus.long_weapon_damage_return += val;
			break;
		case SP_MAGIC_DAMAGE_RETURN: //AppleGirl Was Here
			if(sd->state.lr_flag != 2)
				sd->bonus.magic_damage_return += val;
			break;
		case SP_ALL_STATS: // [Valaris]
			if(sd->state.lr_flag!=2) {
				sd->param_bonus[SP_STR-SP_STR]+=val;
				sd->param_bonus[SP_AGI-SP_STR]+=val;
				sd->param_bonus[SP_VIT-SP_STR]+=val;
				sd->param_bonus[SP_INT-SP_STR]+=val;
				sd->param_bonus[SP_DEX-SP_STR]+=val;
				sd->param_bonus[SP_LUK-SP_STR]+=val;
			}
			break;
		case SP_AGI_VIT: // [Valaris]
			if(sd->state.lr_flag!=2) {
				sd->param_bonus[SP_AGI-SP_STR]+=val;
				sd->param_bonus[SP_VIT-SP_STR]+=val;
			}
			break;
		case SP_AGI_DEX_STR: // [Valaris]
			if(sd->state.lr_flag!=2) {
				sd->param_bonus[SP_AGI-SP_STR]+=val;
				sd->param_bonus[SP_DEX-SP_STR]+=val;
				sd->param_bonus[SP_STR-SP_STR]+=val;
			}
			break;
		case SP_PERFECT_HIDE: // [Valaris]
			if(sd->state.lr_flag!=2)
				sd->special_state.perfect_hiding=1;
			break;
		case SP_UNBREAKABLE:
			if(sd->state.lr_flag!=2)
				sd->bonus.unbreakable += val;
			break;
		case SP_UNBREAKABLE_WEAPON:
			if(sd->state.lr_flag != 2)
				sd->bonus.unbreakable_equip |= EQP_WEAPON;
			break;
		case SP_UNBREAKABLE_ARMOR:
			if(sd->state.lr_flag != 2)
				sd->bonus.unbreakable_equip |= EQP_ARMOR;
			break;
		case SP_UNBREAKABLE_HELM:
			if(sd->state.lr_flag != 2)
				sd->bonus.unbreakable_equip |= EQP_HELM;
			break;
		case SP_UNBREAKABLE_SHIELD:
			if(sd->state.lr_flag != 2)
				sd->bonus.unbreakable_equip |= EQP_SHIELD;
			break;
		case SP_UNBREAKABLE_GARMENT:
			if(sd->state.lr_flag != 2)
				sd->bonus.unbreakable_equip |= EQP_GARMENT;
			break;
		case SP_UNBREAKABLE_SHOES:
			if(sd->state.lr_flag != 2)
				sd->bonus.unbreakable_equip |= EQP_SHOES;
			break;
		case SP_CLASSCHANGE: // [Valaris]
			if(sd->state.lr_flag !=2)
				sd->bonus.classchange=val;
			break;
		case SP_LONG_ATK_RATE:
			if(sd->state.lr_flag != 2) //[Lupus] it should stack, too. As any other cards rate bonuses
				sd->bonus.long_attack_atk_rate+=val;
			break;
		case SP_BREAK_WEAPON_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.break_weapon_rate+=val;
			break;
		case SP_BREAK_ARMOR_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.break_armor_rate+=val;
			break;
		case SP_ADD_STEAL_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.add_steal_rate+=val;
			break;
		case SP_DELAYRATE:
			if(sd->state.lr_flag != 2)
				sd->delayrate+=val;
			break;
		case SP_CRIT_ATK_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.crit_atk_rate += val;
			break;
		case SP_NO_REGEN:
			if(sd->state.lr_flag != 2)
				sd->regen.state.block|=val;
			break;
		case SP_UNSTRIPABLE_WEAPON:
			if(sd->state.lr_flag != 2)
				sd->bonus.unstripable_equip |= EQP_WEAPON;
			break;
		case SP_UNSTRIPABLE:
		case SP_UNSTRIPABLE_ARMOR:
			if(sd->state.lr_flag != 2)
				sd->bonus.unstripable_equip |= EQP_ARMOR;
			break;
		case SP_UNSTRIPABLE_HELM:
			if(sd->state.lr_flag != 2)
				sd->bonus.unstripable_equip |= EQP_HELM;
			break;
		case SP_UNSTRIPABLE_SHIELD:
			if(sd->state.lr_flag != 2)
				sd->bonus.unstripable_equip |= EQP_SHIELD;
			break;
		case SP_HP_DRAIN_VALUE:
			if(!sd->state.lr_flag) {
				sd->right_weapon.hp_drain[RC_NONBOSS].value += val;
				sd->right_weapon.hp_drain[RC_BOSS].value += val;
			}
			else if(sd->state.lr_flag == 1) {
				sd->left_weapon.hp_drain[RC_NONBOSS].value += val;
				sd->left_weapon.hp_drain[RC_BOSS].value += val;
			}
			break;
		case SP_SP_DRAIN_VALUE:
			if(!sd->state.lr_flag) {
				sd->right_weapon.sp_drain[RC_NONBOSS].value += val;
				sd->right_weapon.sp_drain[RC_BOSS].value += val;
			}
			else if(sd->state.lr_flag == 1) {
				sd->left_weapon.sp_drain[RC_NONBOSS].value += val;
				sd->left_weapon.sp_drain[RC_BOSS].value += val;
			}
			break;
		case SP_SP_GAIN_VALUE:
			if(!sd->state.lr_flag)
				sd->bonus.sp_gain_value += val;
			break;
		case SP_HP_GAIN_VALUE:
			if(!sd->state.lr_flag)
				sd->bonus.hp_gain_value += val;
			break;
		case SP_MAGIC_SP_GAIN_VALUE:
			if(!sd->state.lr_flag)
				sd->bonus.magic_sp_gain_value += val;
			break;
		case SP_MAGIC_HP_GAIN_VALUE:
			if(!sd->state.lr_flag)
				sd->bonus.magic_hp_gain_value += val;
			break;
		case SP_ADD_HEAL_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.add_heal_rate += val;
			break;
		case SP_ADD_HEAL2_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.add_heal2_rate += val;
			break;
		case SP_ADD_ITEM_HEAL_RATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.itemhealrate2 += val;
			break;
		case SP_EMATK:
			   if(sd->state.lr_flag != 2)
				   sd->bonus.ematk += val;
			   break;
		case SP_FIXCASTRATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.fixcastrate -= val;
			break;
		case SP_ADD_FIXEDCAST:
			if(sd->state.lr_flag != 2)
				sd->bonus.add_fixcast += val;

			break;
	#ifdef RENEWAL_CAST
		case SP_VARCASTRATE:
			if(sd->state.lr_flag != 2)
				sd->bonus.varcastrate -= val;
			break;
		case SP_ADD_VARIABLECAST:
			if(sd->state.lr_flag != 2)
				sd->bonus.add_varcast += val;
			break;
	#endif
		case SP_ADD_MONSTER_DROP_CHAINITEM:
			if (sd->state.lr_flag != 2)
				pc->bonus_item_drop(sd->add_drop, ARRAYLENGTH(sd->add_drop), 0, val, (1<<RC_BOSS)|(1<<RC_NONBOSS), 10000);
		break;
		default:
			ShowWarning("pc_bonus: unknown type %d %d !\n",type,val);
			break;
	}
