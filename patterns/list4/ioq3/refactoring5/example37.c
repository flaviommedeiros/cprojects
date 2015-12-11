#ifdef LEGACY_PROTOCOL
if(cl->compat)
		cl->hasVoip = qfalse;
	else
#endif
	{
		val = Info_ValueForKey(cl->userinfo, "cl_voip");
		cl->hasVoip = atoi(val);
	}
