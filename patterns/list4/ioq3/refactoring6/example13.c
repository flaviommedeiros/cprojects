if(prot != com_protocol->integer
#ifdef LEGACY_PROTOCOL
	   && prot != com_legacyprotocol->integer
#endif
	  )
	{
		Com_DPrintf( "Different protocol info packet: %s\n", infoString );
		return;
	}
