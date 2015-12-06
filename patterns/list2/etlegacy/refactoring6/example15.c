if (!cg.demoPlayback
#ifdef FEATURE_MULTIVIEW
		    && cg.mvTotalClients < 1
#endif
		    )
		{
			trap_SendClientCommand("score");
		}
