switch(type) {
		case SP_SKILLPOINT:      val = sd->status.skill_point; break;
		case SP_STATUSPOINT:     val = sd->status.status_point; break;
		case SP_ZENY:            val = sd->status.zeny; break;
		case SP_BASELEVEL:       val = sd->status.base_level; break;
		case SP_JOBLEVEL:        val = sd->status.job_level; break;
		case SP_CLASS:           val = sd->status.class_; break;
		case SP_BASEJOB:         val = pc->mapid2jobid(sd->class_&MAPID_UPPERMASK, sd->status.sex); break; //Base job, extracting upper type.
		case SP_UPPER:           val = (sd->class_&JOBL_UPPER) ? 1 : ((sd->class_&JOBL_BABY) ? 2 : 0); break;
		case SP_BASECLASS:       val = pc->mapid2jobid(sd->class_&MAPID_BASEMASK, sd->status.sex); break; //Extract base class tree. [Skotlex]
		case SP_SEX:             val = sd->status.sex; break;
		case SP_WEIGHT:          val = sd->weight; break;
		case SP_MAXWEIGHT:       val = sd->max_weight; break;
		case SP_BASEEXP:         val = sd->status.base_exp; break;
		case SP_JOBEXP:          val = sd->status.job_exp; break;
		case SP_NEXTBASEEXP:     val = pc->nextbaseexp(sd); break;
		case SP_NEXTJOBEXP:      val = pc->nextjobexp(sd); break;
		case SP_HP:              val = sd->battle_status.hp; break;
		case SP_MAXHP:           val = sd->battle_status.max_hp; break;
		case SP_SP:              val = sd->battle_status.sp; break;
		case SP_MAXSP:           val = sd->battle_status.max_sp; break;
		case SP_STR:             val = sd->status.str; break;
		case SP_AGI:             val = sd->status.agi; break;
		case SP_VIT:             val = sd->status.vit; break;
		case SP_INT:             val = sd->status.int_; break;
		case SP_DEX:             val = sd->status.dex; break;
		case SP_LUK:             val = sd->status.luk; break;
		case SP_KARMA:           val = sd->status.karma; break;
		case SP_MANNER:          val = sd->status.manner; break;
		case SP_FAME:            val = sd->status.fame; break;
		case SP_KILLERRID:       val = sd->killerrid; break;
		case SP_KILLEDRID:       val = sd->killedrid; break;
		case SP_SLOTCHANGE:      val = sd->status.slotchange; break;
		case SP_CHARRENAME:      val = sd->status.rename; break;
		case SP_MOD_EXP:         val = sd->status.mod_exp; break;
		case SP_MOD_DROP:        val = sd->status.mod_drop; break;
		case SP_MOD_DEATH:       val = sd->status.mod_death; break;
		case SP_CRITICAL:        val = sd->battle_status.cri/10; break;
		case SP_ASPD:            val = (2000-sd->battle_status.amotion)/10; break;
		case SP_BASE_ATK:        val = sd->battle_status.batk; break;
		case SP_DEF1:            val = sd->battle_status.def; break;
		case SP_DEF2:            val = sd->battle_status.def2; break;
		case SP_MDEF1:           val = sd->battle_status.mdef; break;
		case SP_MDEF2:           val = sd->battle_status.mdef2; break;
		case SP_HIT:             val = sd->battle_status.hit; break;
		case SP_FLEE1:           val = sd->battle_status.flee; break;
		case SP_FLEE2:           val = sd->battle_status.flee2; break;
		case SP_DEFELE:          val = sd->battle_status.def_ele; break;
#ifndef RENEWAL_CAST
		case SP_VARCASTRATE:
#endif
		case SP_CASTRATE:
				val = sd->castrate+=val;
			break;
		case SP_MAXHPRATE:       val = sd->hprate; break;
		case SP_MAXSPRATE:       val = sd->sprate; break;
		case SP_SPRATE:          val = sd->dsprate; break;
		case SP_SPEED_RATE:      val = sd->bonus.speed_rate; break;
		case SP_SPEED_ADDRATE:   val = sd->bonus.speed_add_rate; break;
		case SP_ASPD_RATE:
#ifndef RENEWAL_ASPD
			val = sd->battle_status.aspd_rate;
#else
			val = sd->battle_status.aspd_rate2;
#endif
			break;
		case SP_HP_RECOV_RATE:   val = sd->hprecov_rate; break;
		case SP_SP_RECOV_RATE:   val = sd->sprecov_rate; break;
		case SP_CRITICAL_DEF:    val = sd->bonus.critical_def; break;
		case SP_NEAR_ATK_DEF:    val = sd->bonus.near_attack_def_rate; break;
		case SP_LONG_ATK_DEF:    val = sd->bonus.long_attack_def_rate; break;
		case SP_DOUBLE_RATE:     val = sd->bonus.double_rate; break;
		case SP_DOUBLE_ADD_RATE: val = sd->bonus.double_add_rate; break;
		case SP_MATK_RATE:       val = sd->matk_rate; break;
		case SP_ATK_RATE:        val = sd->bonus.atk_rate; break;
		case SP_MAGIC_ATK_DEF:   val = sd->bonus.magic_def_rate; break;
		case SP_MISC_ATK_DEF:    val = sd->bonus.misc_def_rate; break;
		case SP_PERFECT_HIT_RATE:val = sd->bonus.perfect_hit; break;
		case SP_PERFECT_HIT_ADD_RATE: val = sd->bonus.perfect_hit_add; break;
		case SP_CRITICAL_RATE:   val = sd->critical_rate; break;
		case SP_HIT_RATE:        val = sd->hit_rate; break;
		case SP_FLEE_RATE:       val = sd->flee_rate; break;
		case SP_FLEE2_RATE:      val = sd->flee2_rate; break;
		case SP_DEF_RATE:        val = sd->def_rate; break;
		case SP_DEF2_RATE:       val = sd->def2_rate; break;
		case SP_MDEF_RATE:       val = sd->mdef_rate; break;
		case SP_MDEF2_RATE:      val = sd->mdef2_rate; break;
		case SP_RESTART_FULL_RECOVER: val = sd->special_state.restart_full_recover?1:0; break;
		case SP_NO_CASTCANCEL:   val = sd->special_state.no_castcancel?1:0; break;
		case SP_NO_CASTCANCEL2:  val = sd->special_state.no_castcancel2?1:0; break;
		case SP_NO_SIZEFIX:      val = sd->special_state.no_sizefix?1:0; break;
		case SP_NO_MAGIC_DAMAGE: val = sd->special_state.no_magic_damage; break;
		case SP_NO_WEAPON_DAMAGE:val = sd->special_state.no_weapon_damage; break;
		case SP_NO_MISC_DAMAGE:  val = sd->special_state.no_misc_damage; break;
		case SP_NO_GEMSTONE:     val = sd->special_state.no_gemstone?1:0; break;
		case SP_INTRAVISION:     val = sd->special_state.intravision?1:0; break;
		case SP_NO_KNOCKBACK:    val = sd->special_state.no_knockback?1:0; break;
		case SP_SPLASH_RANGE:    val = sd->bonus.splash_range; break;
		case SP_SPLASH_ADD_RANGE:val = sd->bonus.splash_add_range; break;
		case SP_SHORT_WEAPON_DAMAGE_RETURN: val = sd->bonus.short_weapon_damage_return; break;
		case SP_LONG_WEAPON_DAMAGE_RETURN: val = sd->bonus.long_weapon_damage_return; break;
		case SP_MAGIC_DAMAGE_RETURN: val = sd->bonus.magic_damage_return; break;
		case SP_PERFECT_HIDE:    val = sd->special_state.perfect_hiding?1:0; break;
		case SP_UNBREAKABLE:     val = sd->bonus.unbreakable; break;
		case SP_UNBREAKABLE_WEAPON: val = (sd->bonus.unbreakable_equip&EQP_WEAPON)?1:0; break;
		case SP_UNBREAKABLE_ARMOR: val = (sd->bonus.unbreakable_equip&EQP_ARMOR)?1:0; break;
		case SP_UNBREAKABLE_HELM: val = (sd->bonus.unbreakable_equip&EQP_HELM)?1:0; break;
		case SP_UNBREAKABLE_SHIELD: val = (sd->bonus.unbreakable_equip&EQP_SHIELD)?1:0; break;
		case SP_UNBREAKABLE_GARMENT: val = (sd->bonus.unbreakable_equip&EQP_GARMENT)?1:0; break;
		case SP_UNBREAKABLE_SHOES: val = (sd->bonus.unbreakable_equip&EQP_SHOES)?1:0; break;
		case SP_CLASSCHANGE:     val = sd->bonus.classchange; break;
		case SP_LONG_ATK_RATE:   val = sd->bonus.long_attack_atk_rate; break;
		case SP_BREAK_WEAPON_RATE: val = sd->bonus.break_weapon_rate; break;
		case SP_BREAK_ARMOR_RATE: val = sd->bonus.break_armor_rate; break;
		case SP_ADD_STEAL_RATE:  val = sd->bonus.add_steal_rate; break;
		case SP_DELAYRATE:       val = sd->delayrate; break;
		case SP_CRIT_ATK_RATE:   val = sd->bonus.crit_atk_rate; break;
		case SP_UNSTRIPABLE_WEAPON: val = (sd->bonus.unstripable_equip&EQP_WEAPON)?1:0; break;
		case SP_UNSTRIPABLE:
		case SP_UNSTRIPABLE_ARMOR:
			val = (sd->bonus.unstripable_equip&EQP_ARMOR)?1:0;
			break;
		case SP_UNSTRIPABLE_HELM: val = (sd->bonus.unstripable_equip&EQP_HELM)?1:0; break;
		case SP_UNSTRIPABLE_SHIELD: val = (sd->bonus.unstripable_equip&EQP_SHIELD)?1:0; break;
		case SP_SP_GAIN_VALUE:   val = sd->bonus.sp_gain_value; break;
		case SP_HP_GAIN_VALUE:   val = sd->bonus.hp_gain_value; break;
		case SP_MAGIC_SP_GAIN_VALUE: val = sd->bonus.magic_sp_gain_value; break;
		case SP_MAGIC_HP_GAIN_VALUE: val = sd->bonus.magic_hp_gain_value; break;
		case SP_ADD_HEAL_RATE:   val = sd->bonus.add_heal_rate; break;
		case SP_ADD_HEAL2_RATE:  val = sd->bonus.add_heal2_rate; break;
		case SP_ADD_ITEM_HEAL_RATE: val = sd->bonus.itemhealrate2; break;
		case SP_EMATK:           val = sd->bonus.ematk; break;
		case SP_FIXCASTRATE:     val = sd->bonus.fixcastrate; break;
		case SP_ADD_FIXEDCAST:   val = sd->bonus.add_fixcast; break;
#ifdef RENEWAL_CAST
		case SP_VARCASTRATE:     val = sd->bonus.varcastrate; break;
		case SP_ADD_VARIABLECAST:val = sd->bonus.add_varcast; break;
#endif
	}
