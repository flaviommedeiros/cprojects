if (cg.demoPlayback || (cg.snap->ps.pm_flags & PMF_FOLLOW) ||
			    cg_nopredict.integer
#ifdef ALLOW_GSYNC
			    || cg_synchronousClients.integer
#endif // ALLOW_GSYNC
			    )
			{
				break;
			}
