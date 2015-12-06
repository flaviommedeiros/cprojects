if (
#if FEATURE_MULTIVIEW
			    cg.mvTotalClients < 1 ||
#endif
			    cg.snap->ps.stats[STAT_HEALTH] > 0)
			{
				CG_DrawWeapReticle();
			}
