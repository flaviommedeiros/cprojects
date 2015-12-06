#ifdef FEATURE_SERVERMDX
if (g_realHead.integer & REALHEAD_HEAD)
	{
		// zinx - realistic hitboxes
		if (newRefent)
		{
			mdx_gentity_to_grefEntity(ent, refent, ent->timeShiftTime ? ent->timeShiftTime : level.time);
		}
		mdx_legs_position(ent, refent, org);

		org[2] += ent->client->pmext.proneLegsOffset;
		org[2] -= (playerlegsProneMins[2] + playerlegsProneMaxs[2]) * 0.5;

	}
	else
#endif
	{
		vec3_t flatforward;
		AngleVectors(ent->client->ps.viewangles, flatforward, NULL, NULL);
		flatforward[2] = 0;
		VectorNormalizeFast(flatforward);
		if (ent->client->ps.eFlags & EF_PRONE)
		{
			org[0] = ent->r.currentOrigin[0] + flatforward[0] * -32;
			org[1] = ent->r.currentOrigin[1] + flatforward[1] * -32;
		}
		else
		{
			org[0] = ent->r.currentOrigin[0] + flatforward[0] * 32;
			org[1] = ent->r.currentOrigin[1] + flatforward[1] * 32;
		}
		org[2] = ent->r.currentOrigin[2] + ent->client->pmext.proneLegsOffset;
	}
