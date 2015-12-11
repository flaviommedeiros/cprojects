#ifdef MISSIONPACK
if (gametype == GT_HARVESTER) {
		//
		bs->decisionmaker = client;
		bs->ordered = qtrue;
		bs->order_time = FloatTime();
		//set the time to send a message to the team mates
		bs->teammessage_time = FloatTime() + 2 * random();
		//set the ltg type
		bs->ltgtype = LTG_HARVEST;
		//set the team goal time
		bs->teamgoal_time = FloatTime() + TEAM_HARVEST_TIME;
		bs->harvestaway_time = 0;
		//
		BotSetTeamStatus(bs);
		// remember last ordered task
		BotRememberLastOrderedTask(bs);
	}
	else
#endif
	{
		//
		bs->decisionmaker = client;
		bs->ordered = qtrue;
		bs->order_time = FloatTime();
		//set the time to send a message to the team mates
		bs->teammessage_time = FloatTime() + 2 * random();
		//set the ltg type
		bs->ltgtype = LTG_ATTACKENEMYBASE;
		//set the team goal time
		bs->teamgoal_time = FloatTime() + TEAM_ATTACKENEMYBASE_TIME;
		bs->attackaway_time = 0;
		//
		BotSetTeamStatus(bs);
		// remember last ordered task
		BotRememberLastOrderedTask(bs);
	}
