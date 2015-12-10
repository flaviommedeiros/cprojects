#ifdef RENEWAL
if (skill_id != ASC_BREAKER)
#endif
				wd.damage = battle->calc_damage(src, target, &wd, wd.damage, skill_id, skill_lv);
