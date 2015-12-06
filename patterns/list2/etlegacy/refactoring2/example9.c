#ifdef FEATURE_TRACKER
if (!Tracker_catchServerCommand(args[1], VMA(2)))
#endif
		{
			SV_GameSendServerCommand(args[1], VMA(2));
		}
