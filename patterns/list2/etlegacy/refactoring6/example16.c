if (!cg.demoPlayback
#ifdef FEATURE_MULTIVIEW
			    && cg.mvTotalClients < 1
#endif
			    )
			{
				cg.numScores = 0;
			}
