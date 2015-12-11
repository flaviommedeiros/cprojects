switch(bs->ltgtype) {
		case LTG_TEAMHELP:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna help a team mate for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_TEAMACCOMPANY:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna accompany a team mate for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_GETFLAG:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna get the flag for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_RUSHBASE:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna rush to the base for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_RETURNFLAG:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna try to return the flag for %1.0f secs\n", netname, t);
			break;
		}
#ifdef MISSIONPACK
		case LTG_ATTACKENEMYBASE:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna attack the enemy base for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_HARVEST:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna harvest for %1.0f secs\n", netname, t);
			break;
		}
#endif
		case LTG_DEFENDKEYAREA:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna defend a key area for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_GETITEM:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna get an item for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_KILL:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna kill someone for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_CAMP:
		case LTG_CAMPORDER:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna camp for %1.0f secs\n", netname, t);
			break;
		}
		case LTG_PATROL:
		{
			BotAI_Print(PRT_MESSAGE, "%s: I'm gonna patrol for %1.0f secs\n", netname, t);
			break;
		}
		default:
		{
			if (bs->ctfroam_time > FloatTime()) {
				t = bs->ctfroam_time - FloatTime();
				BotAI_Print(PRT_MESSAGE, "%s: I'm gonna roam for %1.0f secs\n", netname, t);
			}
			else {
				BotAI_Print(PRT_MESSAGE, "%s: I've got a regular goal\n", netname);
			}
		}
	}
