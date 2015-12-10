switch(type){
		case SP_ADDELE:
			if( (type2 >= ELE_MAX && type2 != ELE_ALL) || (type2 < ELE_NEUTRAL) ) {
				ShowError("pc_bonus2: SP_ADDELE: Invalid element %d\n", type2);
				break;
			}
			if ( type2 == ELE_ALL ) {
				for ( i = ELE_NEUTRAL; i < ELE_MAX; i++ ) {
					if ( !sd->state.lr_flag )
						sd->right_weapon.addele[i] += val;
					else if ( sd->state.lr_flag == 1 )
						sd->left_weapon.addele[i] += val;
					else if ( sd->state.lr_flag == 2 )
						sd->arrow_addele[i] += val;
				}
			} else {
				if(!sd->state.lr_flag)
					sd->right_weapon.addele[type2] += val;
				else if(sd->state.lr_flag == 1)
					sd->left_weapon.addele[type2] += val;
				else if(sd->state.lr_flag == 2)
					sd->arrow_addele[type2] += val;
			}
			break;
		case SP_ADDRACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_ADDRACE: Invalid Race(%d)\n",type2);
				break;
			}
			if ( type2 >= RC_MAX ) {
				for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
					if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
						 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
						 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
						 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
						)
						continue;
					if ( !sd->state.lr_flag )
						sd->right_weapon.addrace[i] += val;
					else if ( sd->state.lr_flag == 1 )
						sd->left_weapon.addrace[i] += val;
					else if ( sd->state.lr_flag == 2 )
						sd->arrow_addrace[i] += val;
				}
			} else {
				if(!sd->state.lr_flag)
					sd->right_weapon.addrace[type2] += val;
				else if(sd->state.lr_flag == 1)
					sd->left_weapon.addrace[type2] += val;
				else if(sd->state.lr_flag == 2)
					sd->arrow_addrace[type2] += val;
			}
			break;
		case SP_ADDSIZE:
			if(!sd->state.lr_flag)
				sd->right_weapon.addsize[type2]+=val;
			else if(sd->state.lr_flag == 1)
				sd->left_weapon.addsize[type2]+=val;
			else if(sd->state.lr_flag == 2)
				sd->arrow_addsize[type2]+=val;
			break;
		case SP_SUBELE:
			if( (type2 >= ELE_MAX && type2 != ELE_ALL) || (type2 < ELE_NEUTRAL) ) {
				ShowError("pc_bonus2: SP_SUBELE: Invalid element %d\n", type2);
				break;
			}
			if(sd->state.lr_flag != 2) {
				if ( type2 == ELE_ALL ) {
					for ( i = ELE_NEUTRAL; i < ELE_MAX; i++ ){
						sd->subele[i] += val;
					}
				} else {
					sd->subele[type2] += val;
				}
			}
			break;
		case SP_SUBRACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_SUBRACE: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag != 2) {
				if (type2 >= RC_MAX ) {
					for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
						if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
							 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
							 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
							 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
							)
							continue;
						sd->subrace[i] += val;
					}
				} else {
					sd->subrace[type2]+=val;
				}
			}
			break;
		case SP_ADDEFF:
			if (type2 > SC_MAX) {
				ShowWarning("pc_bonus2 (Add Effect): %d is not supported.\n", type2);
				break;
			}
			pc->bonus_addeff(sd->addeff, ARRAYLENGTH(sd->addeff), (sc_type)type2,
			                 sd->state.lr_flag!=2?val:0, sd->state.lr_flag==2?val:0, 0, 0);
			break;
		case SP_ADDEFF2:
			if (type2 > SC_MAX) {
				ShowWarning("pc_bonus2 (Add Effect2): %d is not supported.\n", type2);
				break;
			}
			pc->bonus_addeff(sd->addeff, ARRAYLENGTH(sd->addeff), (sc_type)type2,
			                 sd->state.lr_flag!=2?val:0, sd->state.lr_flag==2?val:0, ATF_SELF, 0);
			break;
		case SP_RESEFF:
			if (type2 < SC_COMMON_MIN || type2 > SC_COMMON_MAX) {
				ShowWarning("pc_bonus2 (Resist Effect): %d is not supported.\n", type2);
				break;
			}
			if(sd->state.lr_flag == 2)
				break;
			i = sd->reseff[type2-SC_COMMON_MIN]+val;
			sd->reseff[type2-SC_COMMON_MIN]= cap_value(i, 0, 10000);
			break;
		case SP_MAGIC_ADDELE:
			if( (type2 >= ELE_MAX && type2 != ELE_ALL) || (type2 < ELE_NEUTRAL) ) {
				ShowError("pc_bonus2: SP_MAGIC_ADDELE: Invalid element %d\n", type2);
				break;
			}
			if ( sd->state.lr_flag != 2 ) {
				if ( type2 == ELE_ALL ) {
					for ( i = ELE_NEUTRAL; i < ELE_MAX; i++ )
						sd->magic_addele[i] += val;
				} else {
					sd->magic_addele[type2] += val;
				}
			}
			break;
		case SP_MAGIC_ADDRACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_MAGIC_ADDRACE: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag != 2){
				if ( type2 >= RC_MAX ){
					for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
						if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
							 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
							 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
							 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
							)
							continue;
						sd->magic_addrace[i] += val;
					}
				} else {
					sd->magic_addrace[type2]+=val;
				}
			}
			break;
		case SP_MAGIC_ADDSIZE:
			if(sd->state.lr_flag != 2)
				sd->magic_addsize[type2]+=val;
			break;
		case SP_MAGIC_ATK_ELE:
			if( (type2 >= ELE_MAX && type2 != ELE_ALL) || (type2 < ELE_NEUTRAL) ) {
				ShowError("pc_bonus2: SP_MAGIC_ATK_ELE: Invalid element %d\n", type2);
				break;
			}
			if ( sd->state.lr_flag != 2 ) {
				if ( type2 == ELE_ALL ) {
					for ( i = ELE_NEUTRAL; i < ELE_MAX; i++ )
						sd->magic_atk_ele[i] += val;
				} else {
					sd->magic_atk_ele[type2] += val;
				}
			}
			break;
		case SP_ADD_DAMAGE_CLASS:
			switch (sd->state.lr_flag) {
				case 0: //Right hand
					ARR_FIND(0, ARRAYLENGTH(sd->right_weapon.add_dmg), i, sd->right_weapon.add_dmg[i].rate == 0 || sd->right_weapon.add_dmg[i].class_ == type2);
					if (i == ARRAYLENGTH(sd->right_weapon.add_dmg)) {
						ShowWarning("pc_bonus2: Reached max (%d) number of add Class dmg bonuses per character!\n",
									ARRAYLENGTH(sd->right_weapon.add_dmg));
						break;
					}
					sd->right_weapon.add_dmg[i].class_ = type2;
					sd->right_weapon.add_dmg[i].rate += val;
					if (!sd->right_weapon.add_dmg[i].rate) { //Shift the rest of elements up.
						if( i != ARRAYLENGTH(sd->right_weapon.add_dmg) - 1 )
							memmove(&sd->right_weapon.add_dmg[i], &sd->right_weapon.add_dmg[i+1], sizeof(sd->right_weapon.add_dmg) - (i+1)*sizeof(sd->right_weapon.add_dmg[0]));
					}
					break;
				case 1: //Left hand
					ARR_FIND(0, ARRAYLENGTH(sd->left_weapon.add_dmg), i, sd->left_weapon.add_dmg[i].rate == 0 || sd->left_weapon.add_dmg[i].class_ == type2);
					if (i == ARRAYLENGTH(sd->left_weapon.add_dmg)) {
						ShowWarning("pc_bonus2: Reached max (%d) number of add Class dmg bonuses per character!\n",
									ARRAYLENGTH(sd->left_weapon.add_dmg));
						break;
					}
					sd->left_weapon.add_dmg[i].class_ = type2;
					sd->left_weapon.add_dmg[i].rate += val;
					if (!sd->left_weapon.add_dmg[i].rate) { //Shift the rest of elements up.
						if( i != ARRAYLENGTH(sd->left_weapon.add_dmg) - 1 )
							memmove(&sd->left_weapon.add_dmg[i], &sd->left_weapon.add_dmg[i+1], sizeof(sd->left_weapon.add_dmg) - (i+1)*sizeof(sd->left_weapon.add_dmg[0]));
					}
					break;
			}
			break;
		case SP_ADD_MAGIC_DAMAGE_CLASS:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->add_mdmg), i, sd->add_mdmg[i].rate == 0 || sd->add_mdmg[i].class_ == type2);
			if (i == ARRAYLENGTH(sd->add_mdmg)) {
				ShowWarning("pc_bonus2: Reached max (%d) number of add Class magic dmg bonuses per character!\n", ARRAYLENGTH(sd->add_mdmg));
				break;
			}
			sd->add_mdmg[i].class_ = type2;
			sd->add_mdmg[i].rate += val;
			if (!sd->add_mdmg[i].rate && i != ARRAYLENGTH(sd->add_mdmg) - 1) //Shift the rest of elements up.
				memmove(&sd->add_mdmg[i], &sd->add_mdmg[i+1], sizeof(sd->add_mdmg) - (i+1)*sizeof(sd->add_mdmg[0]));
			break;
		case SP_ADD_DEF_CLASS:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->add_def), i, sd->add_def[i].rate == 0 || sd->add_def[i].class_ == type2);
			if (i == ARRAYLENGTH(sd->add_def)) {
				ShowWarning("pc_bonus2: Reached max (%d) number of add Class def bonuses per character!\n", ARRAYLENGTH(sd->add_def));
				break;
			}
			sd->add_def[i].class_ = type2;
			sd->add_def[i].rate += val;
			if ( !sd->add_def[i].rate && i != ARRAYLENGTH(sd->add_def) - 1) //Shift the rest of elements up.
				memmove(&sd->add_def[i], &sd->add_def[i+1], sizeof(sd->add_def) - (i+1)*sizeof(sd->add_def[0]));
			break;
		case SP_ADD_MDEF_CLASS:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->add_mdef), i, sd->add_mdef[i].rate == 0 || sd->add_mdef[i].class_ == type2);
			if (i == ARRAYLENGTH(sd->add_mdef)) {
				ShowWarning("pc_bonus2: Reached max (%d) number of add Class mdef bonuses per character!\n", ARRAYLENGTH(sd->add_mdef));
				break;
			}
			sd->add_mdef[i].class_ = type2;
			sd->add_mdef[i].rate += val;
			if (!sd->add_mdef[i].rate && i != ARRAYLENGTH(sd->add_mdef) - 1) //Shift the rest of elements up.
				memmove(&sd->add_mdef[i], &sd->add_mdef[i+1], sizeof(sd->add_mdef) - (i+1)*sizeof(sd->add_mdef[0]));
			break;
		case SP_HP_DRAIN_RATE:
			if(!sd->state.lr_flag) {
				sd->right_weapon.hp_drain[RC_NONBOSS].rate += type2;
				sd->right_weapon.hp_drain[RC_NONBOSS].per += val;
				sd->right_weapon.hp_drain[RC_BOSS].rate += type2;
				sd->right_weapon.hp_drain[RC_BOSS].per += val;
			}
			else if(sd->state.lr_flag == 1) {
				sd->left_weapon.hp_drain[RC_NONBOSS].rate += type2;
				sd->left_weapon.hp_drain[RC_NONBOSS].per += val;
				sd->left_weapon.hp_drain[RC_BOSS].rate += type2;
				sd->left_weapon.hp_drain[RC_BOSS].per += val;
			}
			break;
		case SP_HP_DRAIN_VALUE:
			if(!sd->state.lr_flag) {
				sd->right_weapon.hp_drain[RC_NONBOSS].value += type2;
				sd->right_weapon.hp_drain[RC_NONBOSS].type = val;
				sd->right_weapon.hp_drain[RC_BOSS].value += type2;
				sd->right_weapon.hp_drain[RC_BOSS].type = val;
			}
			else if(sd->state.lr_flag == 1) {
				sd->left_weapon.hp_drain[RC_NONBOSS].value += type2;
				sd->left_weapon.hp_drain[RC_NONBOSS].type = val;
				sd->left_weapon.hp_drain[RC_BOSS].value += type2;
				sd->left_weapon.hp_drain[RC_BOSS].type = val;
			}
			break;
		case SP_SP_DRAIN_RATE:
			if(!sd->state.lr_flag) {
				sd->right_weapon.sp_drain[RC_NONBOSS].rate += type2;
				sd->right_weapon.sp_drain[RC_NONBOSS].per += val;
				sd->right_weapon.sp_drain[RC_BOSS].rate += type2;
				sd->right_weapon.sp_drain[RC_BOSS].per += val;
			}
			else if(sd->state.lr_flag == 1) {
				sd->left_weapon.sp_drain[RC_NONBOSS].rate += type2;
				sd->left_weapon.sp_drain[RC_NONBOSS].per += val;
				sd->left_weapon.sp_drain[RC_BOSS].rate += type2;
				sd->left_weapon.sp_drain[RC_BOSS].per += val;
			}
			break;
		case SP_SP_DRAIN_VALUE:
			if(!sd->state.lr_flag) {
				sd->right_weapon.sp_drain[RC_NONBOSS].value += type2;
				sd->right_weapon.sp_drain[RC_NONBOSS].type = val;
				sd->right_weapon.sp_drain[RC_BOSS].value += type2;
				sd->right_weapon.sp_drain[RC_BOSS].type = val;
			}
			else if(sd->state.lr_flag == 1) {
				sd->left_weapon.sp_drain[RC_NONBOSS].value += type2;
				sd->left_weapon.sp_drain[RC_NONBOSS].type = val;
				sd->left_weapon.sp_drain[RC_BOSS].value += type2;
				sd->left_weapon.sp_drain[RC_BOSS].type = val;
			}
			break;
		case SP_SP_VANISH_RATE:
			if(sd->state.lr_flag != 2) {
				sd->bonus.sp_vanish_rate += type2;
				sd->bonus.sp_vanish_per = max(sd->bonus.sp_vanish_per,val);
				sd->bonus.sp_vanish_trigger=0;
			}
			break;
		case SP_GET_ZENY_NUM:
			if(sd->state.lr_flag != 2 && sd->bonus.get_zeny_rate < val) {
				sd->bonus.get_zeny_rate = val;
				sd->bonus.get_zeny_num = type2;
			}
			break;
		case SP_ADD_GET_ZENY_NUM:
			if(sd->state.lr_flag != 2) {
				sd->bonus.get_zeny_rate += val;
				sd->bonus.get_zeny_num += type2;
			}
			break;
		case SP_WEAPON_COMA_ELE:
			if( (type2 >= ELE_MAX && type2 != ELE_ALL) || (type2 < ELE_NEUTRAL) ) {
				ShowError("pc_bonus2: SP_WEAPON_COMA_ELE: Invalid element %d\n", type2);
				break;
			}
			if(sd->state.lr_flag == 2)
				break;
			if ( type2 == ELE_ALL ) {
				for ( i = ELE_NEUTRAL; i < ELE_MAX; i++ )
					sd->weapon_coma_ele[i] += val;
			} else {
				sd->weapon_coma_ele[type2] += val;
			}
			sd->special_state.bonus_coma = 1;
			break;
		case SP_WEAPON_COMA_RACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_WEAPON_COMA_RACE: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag == 2)
				break;
			if ( type2 >= RC_MAX ) {
				for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
					if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
						 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
						 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
						 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
						)
							continue;
					sd->weapon_coma_race[i] += val;
				}
			} else {
				sd->weapon_coma_race[type2] += val;
			}
			sd->special_state.bonus_coma = 1;
			break;
		case SP_WEAPON_ATK:
			if(sd->state.lr_flag != 2)
				sd->weapon_atk[type2]+=val;
			break;
		case SP_WEAPON_ATK_RATE:
			if(sd->state.lr_flag != 2)
				sd->weapon_atk_rate[type2]+=val;
			break;
		case SP_CRITICAL_ADDRACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_CRITICAL_ADDRACE: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag != 2){
				if ( type2 >= RC_MAX ){
					for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
						if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
							 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
							 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
							 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
							)
							continue;
						sd->critaddrace[i] += val*10;
					}
				} else {
					sd->critaddrace[type2] += val*10;
				}
			}
			break;
		case SP_ADDEFF_WHENHIT:
			if (type2 > SC_MAX) {
				ShowWarning("pc_bonus2 (Add Effect when hit): %d is not supported.\n", type2);
				break;
			}
			if(sd->state.lr_flag != 2)
				pc->bonus_addeff(sd->addeff2, ARRAYLENGTH(sd->addeff2), (sc_type)type2, val, 0, 0, 0);
			break;
		case SP_SKILL_ATK:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillatk), i, sd->skillatk[i].id == 0 || sd->skillatk[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillatk)) {
				//Better mention this so the array length can be updated. [Skotlex]
				ShowDebug("script->run: bonus2 bSkillAtk reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillatk), type2, val);
				break;
			}
			if (sd->skillatk[i].id == type2)
				sd->skillatk[i].val += val;
			else {
				sd->skillatk[i].id = type2;
				sd->skillatk[i].val = val;
			}
			break;
		case SP_SKILL_HEAL:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillheal), i, sd->skillheal[i].id == 0 || sd->skillheal[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillheal)) {
				// Better mention this so the array length can be updated. [Skotlex]
				ShowDebug("script->run: bonus2 bSkillHeal reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillheal), type2, val);
				break;
			}
			if (sd->skillheal[i].id == type2)
				sd->skillheal[i].val += val;
			else {
				sd->skillheal[i].id = type2;
				sd->skillheal[i].val = val;
			}
			break;
		case SP_SKILL_HEAL2:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillheal2), i, sd->skillheal2[i].id == 0 || sd->skillheal2[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillheal2)) {
				// Better mention this so the array length can be updated. [Skotlex]
				ShowDebug("script->run: bonus2 bSkillHeal2 reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillheal2), type2, val);
				break;
			}
			if (sd->skillheal2[i].id == type2)
				sd->skillheal2[i].val += val;
			else {
				sd->skillheal2[i].id = type2;
				sd->skillheal2[i].val = val;
			}
			break;
		case SP_ADD_SKILL_BLOW:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillblown), i, sd->skillblown[i].id == 0 || sd->skillblown[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillblown)) {
				//Better mention this so the array length can be updated. [Skotlex]
				ShowDebug("script->run: bonus2 bSkillBlown reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillblown), type2, val);
				break;
			}
			if(sd->skillblown[i].id == type2)
				sd->skillblown[i].val += val;
			else {
				sd->skillblown[i].id = type2;
				sd->skillblown[i].val = val;
			}
			break;
#ifndef RENEWAL_CAST
		case SP_VARCASTRATE:
#endif
		case SP_CASTRATE:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillcast), i, sd->skillcast[i].id == 0 || sd->skillcast[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillcast)) {
				//Better mention this so the array length can be updated. [Skotlex]
				ShowDebug("script->run: bonus2 %s reached its limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
					type == SP_CASTRATE ? "bCastRate" : "bVariableCastrate",
					ARRAYLENGTH(sd->skillcast), type2, val);
				break;
			}
			if(sd->skillcast[i].id == type2)
				sd->skillcast[i].val += val;
			else {
				sd->skillcast[i].id = type2;
				sd->skillcast[i].val = val;
			}
			break;

		case SP_FIXCASTRATE:
			if(sd->state.lr_flag == 2)
				break;

			ARR_FIND(0, ARRAYLENGTH(sd->skillfixcastrate), i, sd->skillfixcastrate[i].id == 0 || sd->skillfixcastrate[i].id == type2);

			if (i == ARRAYLENGTH(sd->skillfixcastrate)) {
				ShowDebug("script->run: bonus2 bFixedCastrate reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillfixcastrate), type2, val);
				break;
			}

			if(sd->skillfixcastrate[i].id == type2)
				sd->skillfixcastrate[i].val -= val;

			else {
				sd->skillfixcastrate[i].id = type2;
				sd->skillfixcastrate[i].val -= val;
			}

			break;

		case SP_HP_LOSS_RATE:
			if(sd->state.lr_flag != 2) {
				sd->hp_loss.value = type2;
				sd->hp_loss.rate = val;
			}
			break;
		case SP_HP_REGEN_RATE:
			if(sd->state.lr_flag != 2) {
				sd->hp_regen.value = type2;
				sd->hp_regen.rate = val;
			}
			break;
		case SP_ADDRACE2:
			if (!(type2 > RC2_NONE && type2 < RC2_MAX))
				break;
			if(sd->state.lr_flag != 2)
				sd->right_weapon.addrace2[type2] += val;
			else
				sd->left_weapon.addrace2[type2] += val;
			break;
		case SP_SUBSIZE:
			if(sd->state.lr_flag != 2)
				sd->subsize[type2]+=val;
			break;
		case SP_SUBRACE2:
			if (!(type2 > RC2_NONE && type2 < RC2_MAX))
				break;
			if(sd->state.lr_flag != 2)
				sd->subrace2[type2]+=val;
			break;
		case SP_ADD_ITEM_HEAL_RATE:
			if(sd->state.lr_flag == 2)
				break;
			//Standard item bonus.
			for(i=0; i < ARRAYLENGTH(sd->itemhealrate) && sd->itemhealrate[i].nameid && sd->itemhealrate[i].nameid != type2; i++);
			if (i == ARRAYLENGTH(sd->itemhealrate)) {
				ShowWarning("pc_bonus2: Reached max (%d) number of item heal bonuses per character!\n", ARRAYLENGTH(sd->itemhealrate));
				break;
			}
			sd->itemhealrate[i].nameid = type2;
			sd->itemhealrate[i].rate += val;
			break;
		case SP_EXP_ADDRACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_EXP_ADDRACE: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag != 2) {
				if ( type2 >= RC_MAX ){
					for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
						if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
							 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
							 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
							 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
							)
							continue;
						sd->expaddrace[i] += val;
					}
				} else {
					sd->expaddrace[type2] += val;
				}
			}
			break;
		case SP_SP_GAIN_RACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_SP_GAIN_RACE: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag != 2) {
				if ( type2 >= RC_MAX ){
					for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
						if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
							 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
							 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
							 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
							)
							continue;
						sd->sp_gain_race[i] += val;
					}
				} else {
					sd->sp_gain_race[type2] += val;
				}
			}
			break;
		case SP_ADD_MONSTER_DROP_ITEM:
			if (sd->state.lr_flag != 2)
				pc->bonus_item_drop(sd->add_drop, ARRAYLENGTH(sd->add_drop), type2, 0, (1<<RC_BOSS)|(1<<RC_NONBOSS), val);
			break;
		case SP_SP_LOSS_RATE:
			if(sd->state.lr_flag != 2) {
				sd->sp_loss.value = type2;
				sd->sp_loss.rate = val;
			}
			break;
		case SP_SP_REGEN_RATE:
			if(sd->state.lr_flag != 2) {
				sd->sp_regen.value = type2;
				sd->sp_regen.rate = val;
			}
			break;
		case SP_HP_DRAIN_VALUE_RACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_HP_DRAIN_VALUE_RACE: Invalid Race(%d)\n",type2);
				break;
			}
			if ( type2 >= RC_MAX ){
				for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
					if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
						 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
						 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
						 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
						)
						continue;
					if(!sd->state.lr_flag) {
						sd->right_weapon.hp_drain[i].value += val;
					}
					else if(sd->state.lr_flag == 1) {
						sd->left_weapon.hp_drain[i].value += val;
					}
				}
			} else {
				if(!sd->state.lr_flag) {
					sd->right_weapon.hp_drain[type2].value += val;
				}
				else if(sd->state.lr_flag == 1) {
					sd->left_weapon.hp_drain[type2].value += val;
				}
			}
			break;
		case SP_SP_DRAIN_VALUE_RACE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_SP_DRAIN_VALUE_RACE: Invalid Race(%d)\n",type2);
				break;
			}
			if ( type2 >= RC_MAX ){
				for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
					if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
						 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
						 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
						 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
						)
						continue;
					if(!sd->state.lr_flag) {
						sd->right_weapon.sp_drain[i].value += val;
					}
					else if(sd->state.lr_flag == 1) {
						sd->left_weapon.sp_drain[i].value += val;
					}
				}
			} else {
				if(!sd->state.lr_flag) {
					sd->right_weapon.sp_drain[type2].value += val;
				}
				else if(sd->state.lr_flag == 1) {
					sd->left_weapon.sp_drain[type2].value += val;
				}
			}
			break;
		case SP_IGNORE_MDEF_RATE:
			if(sd->state.lr_flag != 2)
				sd->ignore_mdef[type2] += val;
			break;
		case SP_IGNORE_DEF_RATE:
			if(sd->state.lr_flag != 2)
				sd->ignore_def[type2] += val;
			break;
		case SP_SP_GAIN_RACE_ATTACK:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_SP_GAIN_RACE_ATTACK: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag != 2) {
				if ( type2 >= RC_MAX ) {
					for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
						if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
							 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
							 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
							 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
							)
							continue;
						sd->sp_gain_race_attack[i] = cap_value(sd->sp_gain_race_attack[i] + val, 0, INT16_MAX);
					}
				} else {
						sd->sp_gain_race_attack[type2] = cap_value(sd->sp_gain_race_attack[type2] + val, 0, INT16_MAX);
				}
			}
			break;
		case SP_HP_GAIN_RACE_ATTACK:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_HP_GAIN_RACE_ATTACK: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag != 2) {
				if ( type2 >= RC_MAX ) {
					for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
						if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
							 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
							 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
							 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
							)
							continue;
						sd->hp_gain_race_attack[i] = cap_value(sd->hp_gain_race_attack[i] + val, 0, INT16_MAX);
					}
				} else {
						sd->hp_gain_race_attack[type2] = cap_value(sd->hp_gain_race_attack[type2] + val, 0, INT16_MAX);
				}
			}
			break;
		case SP_SKILL_USE_SP_RATE: //bonus2 bSkillUseSPrate,n,x;
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillusesprate), i, sd->skillusesprate[i].id == 0 || sd->skillusesprate[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillusesprate)) {
				ShowDebug("script->run: bonus2 bSkillUseSPrate reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillusesprate), type2, val);
				break;
			}
			if (sd->skillusesprate[i].id == type2)
				sd->skillusesprate[i].val += val;
			else {
				sd->skillusesprate[i].id = type2;
				sd->skillusesprate[i].val = val;
			}
			break;
		case SP_SKILL_COOLDOWN:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillcooldown), i, sd->skillcooldown[i].id == 0 || sd->skillcooldown[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillcooldown)) {
				ShowDebug("script->run: bonus2 bSkillCoolDown reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillcooldown), type2, val);
				break;
			}
			if (sd->skillcooldown[i].id == type2)
				sd->skillcooldown[i].val += val;
			else {
				sd->skillcooldown[i].id = type2;
				sd->skillcooldown[i].val = val;
			}
			break;
		case SP_SKILL_FIXEDCAST:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillfixcast), i, sd->skillfixcast[i].id == 0 || sd->skillfixcast[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillfixcast)) {
				ShowDebug("script->run: bonus2 bSkillFixedCast reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillfixcast), type2, val);
				break;
			}
			if (sd->skillfixcast[i].id == type2)
				sd->skillfixcast[i].val += val;
			else {
				sd->skillfixcast[i].id = type2;
				sd->skillfixcast[i].val = val;
			}
			break;
		case SP_SKILL_VARIABLECAST:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillvarcast), i, sd->skillvarcast[i].id == 0 || sd->skillvarcast[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillvarcast)) {
				ShowDebug("script->run: bonus2 bSkillVariableCast reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillvarcast), type2, val);
				break;
			}
			if (sd->skillvarcast[i].id == type2)
				sd->skillvarcast[i].val += val;
			else {
				sd->skillvarcast[i].id = type2;
				sd->skillvarcast[i].val = val;
			}
			break;
	#ifdef RENEWAL_CAST
		case SP_VARCASTRATE:
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillcast), i, sd->skillcast[i].id == 0 || sd->skillcast[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillcast)) {
				ShowDebug("script->run: bonus2 bVariableCastrate reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillcast), type2, val);
				break;
			}
			if(sd->skillcast[i].id == type2)
				sd->skillcast[i].val -= val;
			else {
				sd->skillcast[i].id = type2;
				sd->skillcast[i].val -= val;
			}
			break;
	#endif
		case SP_SKILL_USE_SP: //bonus2 bSkillUseSP,n,x;
			if(sd->state.lr_flag == 2)
				break;
			ARR_FIND(0, ARRAYLENGTH(sd->skillusesp), i, sd->skillusesp[i].id == 0 || sd->skillusesp[i].id == type2);
			if (i == ARRAYLENGTH(sd->skillusesp)) {
				ShowDebug("script->run: bonus2 bSkillUseSP reached it's limit (%d skills per character), bonus skill %d (+%d%%) lost.\n",
				          ARRAYLENGTH(sd->skillusesp), type2, val);
				break;
			}
			if (sd->skillusesp[i].id == type2)
				sd->skillusesp[i].val += val;
			else {
				sd->skillusesp[i].id = type2;
				sd->skillusesp[i].val = val;
			}
			break;
		case SP_ADD_MONSTER_DROP_CHAINITEM:
			if (sd->state.lr_flag != 2)
				pc->bonus_item_drop(sd->add_drop, ARRAYLENGTH(sd->add_drop), 0, val, 1<<type2, 10000);
			break;
#ifdef RENEWAL
		case SP_RACE_TOLERANCE:
			if (type2 == RC_MAX || (type2 > RC_NONDEMIPLAYER && type2 != RC_ALL) || type2 < RC_FORMLESS ){
				ShowWarning("pc_bonus2: SP_RACE_TOLERANCE: Invalid Race(%d)\n",type2);
				break;
			}
			if(sd->state.lr_flag != 2) {
				if ( type2 >= RC_MAX ) {
					for ( i = RC_FORMLESS; i < RC_BOSS; i++ ) {
						if ( (type2 == RC_NONPLAYER && i == RC_PLAYER) ||
							 (type2 == RC_NONDEMIHUMAN && i == RC_DEMIHUMAN) ||
							 (type2 == RC_DEMIPLAYER && (i != RC_PLAYER && i != RC_DEMIHUMAN)) ||
							 (type2 == RC_NONDEMIPLAYER && (i == RC_PLAYER || i == RC_DEMIHUMAN))
							)
							continue;
						sd->race_tolerance[i] += val;
					}
				} else {
						sd->race_tolerance[type2] += val;
				}
			}
			break;
#endif
		default:
			ShowWarning("pc_bonus2: unknown type %d %d %d!\n",type,type2,val);
			break;
	}
