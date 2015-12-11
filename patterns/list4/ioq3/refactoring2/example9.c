#ifndef STANDALONE
if(Q_stricmp(key, "g_synchronousClients") && Q_stricmp(key, "pmove_fixed") &&
				   Q_stricmp(key, "pmove_msec"))
#endif
				{
					Com_Printf(S_COLOR_YELLOW "WARNING: server is not allowed to set %s=%s\n", key, value);
					continue;
				}
