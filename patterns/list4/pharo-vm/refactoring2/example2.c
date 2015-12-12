#if !__MACOSSEVENORLATER
if ( hasFullExtFSDispatching )
#endif
	{
		infoSize = sizeof(GetVolParmsInfoBuffer);
		result = HGetVolParms(paramBlock->ioNamePtr, paramBlock->ioVRefNum,
							&volParmsInfo, &infoSize);
		if ( result == noErr )
		{
			supportsCatSearch = hasCatSearch(volParmsInfo);
		}
	}
