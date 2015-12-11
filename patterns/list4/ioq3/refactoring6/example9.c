if (gametype == GT_CTF
#ifdef MISSIONPACK
			|| gametype == GT_1FCTF
#endif
			) {
			redtt = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, ctf_redflag.areanum, TFL_DEFAULT);
			bluett = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, ctf_blueflag.areanum, TFL_DEFAULT);
			if (redtt < (redtt + bluett) * 0.4) {
				BotAI_BotInitialChat(bs, "teamlocation", nearbyitems[bestitem], "red", NULL);
			}
			else if (bluett < (redtt + bluett) * 0.4) {
				BotAI_BotInitialChat(bs, "teamlocation", nearbyitems[bestitem], "blue", NULL);
			}
			else {
				BotAI_BotInitialChat(bs, "location", nearbyitems[bestitem], NULL);
			}
		}
#ifdef MISSIONPACK
		else if (gametype == GT_OBELISK || gametype == GT_HARVESTER) {
			redtt = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, redobelisk.areanum, TFL_DEFAULT);
			bluett = trap_AAS_AreaTravelTimeToGoalArea(bs->areanum, bs->origin, blueobelisk.areanum, TFL_DEFAULT);
			if (redtt < (redtt + bluett) * 0.4) {
				BotAI_BotInitialChat(bs, "teamlocation", nearbyitems[bestitem], "red", NULL);
			}
			else if (bluett < (redtt + bluett) * 0.4) {
				BotAI_BotInitialChat(bs, "teamlocation", nearbyitems[bestitem], "blue", NULL);
			}
			else {
				BotAI_BotInitialChat(bs, "location", nearbyitems[bestitem], NULL);
			}
		}
#endif
		else {
			BotAI_BotInitialChat(bs, "location", nearbyitems[bestitem], NULL);
		}
