switch(gametype) {
		case GT_TEAM:
		{
			if (bs->numteammates != numteammates || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->forceorders = qfalse;
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 5) {
				BotTeamOrders(bs);
				//give orders again after 120 seconds
				bs->teamgiveorders_time = FloatTime() + 120;
			}
			break;
		}
		case GT_CTF:
		{
			//if the number of team mates changed or the flag status changed
			//or someone wants to know what to do
			if (bs->numteammates != numteammates || bs->flagstatuschanged || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->flagstatuschanged = qfalse;
				bs->forceorders = qfalse;
			}
			//if there were no flag captures the last 3 minutes
			if (bs->lastflagcapture_time < FloatTime() - 240) {
				bs->lastflagcapture_time = FloatTime();
				//randomly change the CTF strategy
				if (random() < 0.4) {
					bs->ctfstrategy ^= CTFS_AGRESSIVE;
					bs->teamgiveorders_time = FloatTime();
				}
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 3) {
				BotCTFOrders(bs);
				//
				bs->teamgiveorders_time = 0;
			}
			break;
		}
#ifdef MISSIONPACK
		case GT_1FCTF:
		{
			if (bs->numteammates != numteammates || bs->flagstatuschanged || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->flagstatuschanged = qfalse;
				bs->forceorders = qfalse;
			}
			//if there were no flag captures the last 4 minutes
			if (bs->lastflagcapture_time < FloatTime() - 240) {
				bs->lastflagcapture_time = FloatTime();
				//randomly change the CTF strategy
				if (random() < 0.4) {
					bs->ctfstrategy ^= CTFS_AGRESSIVE;
					bs->teamgiveorders_time = FloatTime();
				}
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 2) {
				Bot1FCTFOrders(bs);
				//
				bs->teamgiveorders_time = 0;
			}
			break;
		}
		case GT_OBELISK:
		{
			if (bs->numteammates != numteammates || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->forceorders = qfalse;
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 5) {
				BotObeliskOrders(bs);
				//give orders again after 30 seconds
				bs->teamgiveorders_time = FloatTime() + 30;
			}
			break;
		}
		case GT_HARVESTER:
		{
			if (bs->numteammates != numteammates || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->forceorders = qfalse;
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 5) {
				BotHarvesterOrders(bs);
				//give orders again after 30 seconds
				bs->teamgiveorders_time = FloatTime() + 30;
			}
			break;
		}
#endif
	}
