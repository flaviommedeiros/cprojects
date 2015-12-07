if( status_isdead(src) || status_isdead(target) ||
			battle_check_target(src,target,BCT_ENEMY) <= 0 || !status_check_skilluse(src, target, 0, 0)
#ifdef OFFICIAL_WALKPATH
	   || !path_search_long(NULL, src->m, src->x, src->y, target->x, target->y, CELL_CHKWALL)
#endif
	   || (sd && !pc_can_attack(sd, target->id)) )
		return 0;
