#ifdef LEGACY_PROTOCOL
if(clc.compat)
		clc.voipEnabled = qfalse;
	else
#endif
	{
		s = Info_ValueForKey( systemInfo, "sv_voip" );
		clc.voipEnabled = atoi(s);
	}
