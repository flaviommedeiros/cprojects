if (cg_nopredict.integer || cg.predictedPlayerState.pm_type == PM_INTERMISSION
#ifdef ALLOW_GSYNC
	    || cg_synchronousClients.integer
#endif // ALLOW_GSYNC
	    )
	{
		cg_pmove.ps    = &cg.predictedPlayerState;
		cg_pmove.pmext = &cg.pmext;

		cg.pmext.airleft = (cg.waterundertime - cg.time);

		// are we using an mg42?
		if ((cg_pmove.ps->eFlags & EF_MG42_ACTIVE) || (cg_pmove.ps->eFlags & EF_AAGUN_ACTIVE))
		{
			cg.pmext.harc = cg_entities[cg_pmove.ps->viewlocked_entNum].currentState.origin2[0];
			cg.pmext.varc = cg_entities[cg_pmove.ps->viewlocked_entNum].currentState.origin2[1];

			VectorCopy(cg_entities[cg_pmove.ps->viewlocked_entNum].currentState.angles2, cg.pmext.centerangles);

			cg.pmext.centerangles[PITCH] = AngleNormalize180(cg.pmext.centerangles[PITCH]);
			cg.pmext.centerangles[YAW]   = AngleNormalize180(cg.pmext.centerangles[YAW]);
			cg.pmext.centerangles[ROLL]  = AngleNormalize180(cg.pmext.centerangles[ROLL]);
		}

		CG_InterpolatePlayerState(qtrue);
		return;
	}
