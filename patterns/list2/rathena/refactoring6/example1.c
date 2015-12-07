if(tstatus->mode&MD_BOSS
		// Renewal dropped the 3/4 hp requirement
#ifndef RENEWAL
			|| tstatus-> hp > tstatus->max_hp*3/4
#endif
				) {
			if (sd) clif_skill_fail(sd,skill_id,USESKILL_FAIL_LEVEL,0);
			map_freeblock_unlock();
			return 1;
		}
