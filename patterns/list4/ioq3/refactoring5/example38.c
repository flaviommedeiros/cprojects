#ifdef LEGACY_PROTOCOL
if(com_legacyprotocol->integer > 0)
		Info_SetValueForKey(infostring, "protocol", va("%i", com_legacyprotocol->integer));
	else
#endif
		Info_SetValueForKey(infostring, "protocol", va("%i", com_protocol->integer));
