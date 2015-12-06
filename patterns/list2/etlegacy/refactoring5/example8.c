#ifdef ALLOW_GSYNC
if (!g_synchronousClients.integer)
#endif // ALLOW_GSYNC
	{
		if (G_DoAntiwarp(ent))
		{
			// zinx etpro antiwarp
			etpro_AddUsercmd(clientNum, &newcmd);
			DoClientThinks(ent);
		}
		else
		{
			ClientThink_cmd(ent, &newcmd);
		}
	}
