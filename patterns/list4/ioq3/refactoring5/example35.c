#ifdef LEGACY_PROTOCOL
if(version > 0 && com_legacyprotocol->integer == version)
		compat = qtrue;
	else
#endif
	{
		if(version != com_protocol->integer)
		{
			NET_OutOfBandPrint(NS_SERVER, from, "print\nServer uses protocol version %i "
					   "(yours is %i).\n", com_protocol->integer, version);
			Com_DPrintf("    rejected connect from version %i\n", version);
			return;
		}
	}
