#ifdef LEGACY_PROTOCOL
if(!chan->compat)
#endif
	{
		int checksum = MSG_ReadLong(msg);

		// UDP spoofing protection
		if(NETCHAN_GENCHECKSUM(chan->challenge, sequence) != checksum)
			return qfalse;
	}
