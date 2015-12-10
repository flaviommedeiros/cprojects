#ifdef RENEWAL
if (skill_id != ASC_BREAKER)
#endif
				wd.damage2 = battle->calc_damage(src, target, &wd, wd.damage2, skill_id, skill_lv);
