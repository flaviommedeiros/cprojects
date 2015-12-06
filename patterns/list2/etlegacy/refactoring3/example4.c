switch (cgs.eventHandling)
	{
	// Demos get their own keys
	case CGAME_EVENT_DEMO:
		CG_DemoClick(key, down);
		return;
	case CGAME_EVENT_CAMPAIGNBREIFING:
		CG_LoadPanel_KeyHandling(key, down);
		break;
	case CGAME_EVENT_FIRETEAMMSG:
		CG_Fireteams_KeyHandling(key, down);
		break;
	case CGAME_EVENT_GAMEVIEW:
		CG_LimboPanel_KeyHandling(key, down);
		break;
	case CGAME_EVENT_SPEAKEREDITOR:
		CG_SpeakerEditor_KeyHandling(key, down);
		break;
#ifdef FEATURE_MULTIVIEW
	case CGAME_EVENT_MULTIVIEW:
		CG_mv_KeyHandling(key, down);
		break;
#endif
	default:
		if (cg.snap->ps.pm_type == PM_INTERMISSION)
		{
			CG_Debriefing_KeyEvent(key, down);
			return;
		}

		// default handling
		if (!down)
		{
			return;
		}

		if ((cg.predictedPlayerState.pm_type == PM_NORMAL ||
		     (cg.predictedPlayerState.pm_type == PM_SPECTATOR && cg.showScores == qfalse)))
		{

			CG_EventHandling(CGAME_EVENT_NONE, qfalse);
			return;
		}
		break;
	}
