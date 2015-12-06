#ifndef DEDICATED
if (cls.state != CA_CONNECTED && cls.state != CA_ACTIVE)
#endif
	{
		Com_Printf("%s\n", vstr ? text : Cmd_Args());
		return;
	}
