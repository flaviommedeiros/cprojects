if (
#ifndef RENEWAL
		skill_id == PA_SHIELDCHAIN || skill_id == CR_SHIELDBOOMERANG ||
#endif
		skill_id == RK_DRAGONBREATH || skill_id == RK_DRAGONBREATH_WATER || skill_id == NC_SELFDESTRUCTION ||
		skill_id == LG_SHIELDPRESS || skill_id == LG_EARTHDRIVE)
			return false;
