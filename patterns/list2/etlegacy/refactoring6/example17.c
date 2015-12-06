if (ent->eType == ET_CONSTRUCTIBLE ||
		    ent->eType == ET_OID_TRIGGER
#ifdef VISIBLE_TRIGGERS
		    || ent->eType == ET_TRIGGER_MULTIPLE
		    || ent->eType == ET_TRIGGER_FLAGONLY
		    || ent->eType == ET_TRIGGER_FLAGONLY_MULTIPLE
#endif // VISIBLE_TRIGGERS
		    )
		{
			vec3_t mins, maxs, pmins, pmaxs;

			if (ent->eType == ET_CONSTRUCTIBLE && ent->aiState)
			{
				continue;
			}

			if (ent->solid != SOLID_BMODEL)
			{
				int x  = (ent->solid & 255);
				int zd = ((ent->solid >> 8) & 255);
				int zu = ((ent->solid >> 16) & 255) - 32;

				mins[0] = mins[1] = -x;
				mins[2] = -zd;
				maxs[0] = maxs[1] = x;
				maxs[2] = zu;
			}
			else
			{
				trap_R_ModelBounds(cmodel, mins, maxs);
			}

			VectorAdd(cent->lerpOrigin, mins, mins);
			VectorAdd(cent->lerpOrigin, maxs, maxs);

#ifdef VISIBLE_TRIGGERS
			if (ent->eType == ET_TRIGGER_MULTIPLE || ent->eType == ET_TRIGGER_FLAGONLY || ent->eType == ET_TRIGGER_FLAGONLY_MULTIPLE)
			{
			}
			else
#endif // VISIBLE_TRIGGERS
			{
				// expand the bbox a bit
				VectorSet(mins, mins[0] - 48, mins[1] - 48, mins[2] - 48);
				VectorSet(maxs, maxs[0] + 48, maxs[1] + 48, maxs[2] + 48);
			}

			VectorAdd(cg.predictedPlayerState.origin, cg_pmove.mins, pmins);
			VectorAdd(cg.predictedPlayerState.origin, cg_pmove.maxs, pmaxs);

#ifdef VISIBLE_TRIGGERS
			CG_RailTrail(NULL, mins, maxs, 1);
#endif // VISIBLE_TRIGGERS

			if (!BG_BBoxCollision(pmins, pmaxs, mins, maxs))
			{
				continue;
			}

			cs = NULL;
			if (ent->eType == ET_OID_TRIGGER)
			{
				cs = CG_ConfigString(CS_OID_TRIGGERS + ent->teamNum);
			}
			else if (ent->eType == ET_CONSTRUCTIBLE)
			{
				cs = CG_ConfigString(CS_OID_TRIGGERS + ent->otherEntityNum2);
			}

			if (cs)
			{
				CG_ObjectivePrint(va("%s %s\n", CG_TranslateString("You are near"), cs), cg_fontScaleCP.value);
			}

			continue;
		}
