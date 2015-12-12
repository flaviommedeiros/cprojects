if (
#if !__MACOSSEVENORLATER
		 (!FSHasFSSpecCalls() && !QTHasFSSpecCalls()) ||
#endif	/* !__MACOSSEVENORLATER */
		 !HasFSpCreateScriptSupportFix() )
	{
		/*	If FSpCreate isn't called, this code will be executed */
		pb.hPB.fileParam.ioVRefNum = spec->vRefNum;
		pb.hPB.fileParam.ioDirID = spec->parID;
		pb.hPB.fileParam.ioNamePtr = (StringPtr) &(spec->name);
		pb.hPB.fileParam.ioFVersNum = 0;
		result = PBHCreateSync(&(pb.hPB));
		if ( result == noErr )
		{
			/* get info on created item */
			pb.ciPB.hFileInfo.ioFDirIndex = 0;
			result = PBGetCatInfoSync(&(pb.ciPB));
			if ( result == noErr )
			{
				/* Set fdScript in FXInfo */
				/* The negative script constants (smSystemScript, smCurrentScript, and smAllScripts) */
				/* don't make sense on disk, so only use scriptTag if scriptTag >= smRoman */
				/* (smRoman is 0). fdScript is valid if high bit is set (see IM-6, page 9-38) */
				pb.ciPB.hFileInfo.ioFlXFndrInfo.fdScript = (scriptTag >= smRoman) ?
															((char)scriptTag | (char)0x80) :
															(smRoman);
				/* Set creator/fileType */
				pb.ciPB.hFileInfo.ioFlFndrInfo.fdCreator = creator;
				pb.ciPB.hFileInfo.ioFlFndrInfo.fdType = fileType;
				/* Restore ioDirID field in pb which was changed by PBGetCatInfo */
				pb.ciPB.hFileInfo.ioDirID = spec->parID;
				result = PBSetCatInfoSync(&(pb.ciPB));
			}
		}
		return ( result );
	}
	else
#endif	/* !__MACOSSEVENFIVEONEORLATER */
	{
		return ( FSpCreate(spec, creator, fileType, scriptTag) );
	}
