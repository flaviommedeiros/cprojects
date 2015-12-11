if (BotCTFCarryingFlag(bs)
#ifdef MISSIONPACK
		|| Bot1FCTFCarryingFlag(bs) || BotHarvesterCarryingCubes(bs)
#endif
		) {
		//if the bot is just a few secs away from the base 
		if (trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin,
				bs->teamgoal.areanum, TFL_DEFAULT) < 300) {
			//make the range really small
			range = 50;
		}
	}
