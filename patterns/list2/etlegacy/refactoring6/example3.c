if ((cl->pers.autoaction & AA_STATSALL)
#ifdef FEATURE_MULTIVIEW
				    || cl->pers.mvCount > 0
#endif
				    )
				{
					G_statsall_cmd(ent, 0, qfalse);
				}
				else if (cl->sess.sessionTeam != TEAM_SPECTATOR)
				{
					if (cl->pers.autoaction & AA_STATSTEAM)
					{
						G_statsall_cmd(ent, cl->sess.sessionTeam, qfalse);                // Currently broken.. need to support the overloading of dwCommandID
					}
					else
					{
						CP(va("ws %s\n", G_createStats(ent)));
					}

				}
				else if (cl->sess.spectatorState != SPECTATOR_FREE)
				{
					int pid = cl->sess.spectatorClient;

					if ((cl->pers.autoaction & AA_STATSTEAM))
					{
						G_statsall_cmd(ent, level.clients[pid].sess.sessionTeam, qfalse); // Currently broken.. need to support the overloading of dwCommandID
					}
					else
					{
						CP(va("ws %s\n", G_createStats(g_entities + pid)));
					}
				}
