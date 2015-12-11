switch(bs->ltgtype) {
		case LTG_TEAMHELP:
		{
			EasyClientName(bs->teammate, netname, sizeof(netname));
			BotAI_BotInitialChat(bs, "helping", netname, NULL);
			break;
		}
		case LTG_TEAMACCOMPANY:
		{
			EasyClientName(bs->teammate, netname, sizeof(netname));
			BotAI_BotInitialChat(bs, "accompanying", netname, NULL);
			break;
		}
		case LTG_DEFENDKEYAREA:
		{
			trap_BotGoalName(bs->teamgoal.number, goalname, sizeof(goalname));
			BotAI_BotInitialChat(bs, "defending", goalname, NULL);
			break;
		}
		case LTG_GETITEM:
		{
			trap_BotGoalName(bs->teamgoal.number, goalname, sizeof(goalname));
			BotAI_BotInitialChat(bs, "gettingitem", goalname, NULL);
			break;
		}
		case LTG_KILL:
		{
			ClientName(bs->teamgoal.entitynum, netname, sizeof(netname));
			BotAI_BotInitialChat(bs, "killing", netname, NULL);
			break;
		}
		case LTG_CAMP:
		case LTG_CAMPORDER:
		{
			BotAI_BotInitialChat(bs, "camping", NULL);
			break;
		}
		case LTG_PATROL:
		{
			BotAI_BotInitialChat(bs, "patrolling", NULL);
			break;
		}
		case LTG_GETFLAG:
		{
			BotAI_BotInitialChat(bs, "capturingflag", NULL);
			break;
		}
		case LTG_RUSHBASE:
		{
			BotAI_BotInitialChat(bs, "rushingbase", NULL);
			break;
		}
		case LTG_RETURNFLAG:
		{
			BotAI_BotInitialChat(bs, "returningflag", NULL);
			break;
		}
#ifdef MISSIONPACK
		case LTG_ATTACKENEMYBASE:
		{
			BotAI_BotInitialChat(bs, "attackingenemybase", NULL);
			break;
		}
		case LTG_HARVEST:
		{
			BotAI_BotInitialChat(bs, "harvesting", NULL);
			break;
		}
#endif
		default:
		{
			BotAI_BotInitialChat(bs, "roaming", NULL);
			break;
		}
	}
