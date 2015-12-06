#ifdef FEATURE_MULTIVIEW
if (ent->client->pers.mvCount > 0)
		{
			G_smvRemoveInvalidClients(ent, nTeam);
		}
		else
#endif
		if (ent->client->sess.spectatorState == SPECTATOR_FOLLOW)
		{
			StopFollowing(ent);
			ent->client->sess.spec_team &= ~nTeam;
		}
