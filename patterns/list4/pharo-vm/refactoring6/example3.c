if (
#if !__MACOSSEVENORLATER
		 (!FSHasFSSpecCalls() && !QTHasFSSpecCalls()) ||
#endif	/* !__MACOSSEVENORLATER */
		 !HasFSpCreateScriptSupportFix() )
	{
		OSErr			result;
		CInfoPBRec		pb;
		
		HCreateResFile(spec->vRefNum, spec->parID, spec->name);
		if ( ResError() == noErr )
		{
			/* get info on created item */
			pb.hFileInfo.ioVRefNum = spec->vRefNum;
			pb.hFileInfo.ioDirID = spec->parID;
			pb.hFileInfo.ioNamePtr = (StringPtr) &(spec->name);
			pb.hFileInfo.ioFDirIndex = 0;
			result = PBGetCatInfoSync(&pb);
			if ( result == noErr )
			{
				/* Set fdScript in FXInfo */
				/* The negative script constants (smSystemScript, smCurrentScript, and smAllScripts) */
				/* don't make sense on disk, so only use scriptTag if scriptTag >= smRoman */
				/* (smRoman is 0). fdScript is valid if high bit is set (see IM-6, page 9-38) */
				pb.hFileInfo.ioFlXFndrInfo.fdScript = (scriptTag >= smRoman) ?
														((char)scriptTag | (char)0x80) :
														(smRoman);
				/* Set creator/fileType */
				pb.hFileInfo.ioFlFndrInfo.fdCreator = creator;
				pb.hFileInfo.ioFlFndrInfo.fdType = fileType;
				
				/* Restore ioDirID field in pb which was changed by PBGetCatInfo */
				pb.hFileInfo.ioDirID = spec->parID;
				result = PBSetCatInfoSync(&pb);
			}
			/* Set ResErr low memory global to result */
			LMSetResErr(result);
		}
		return;
	}
	else
#endif	/* !__MACOSSEVENFIVEONEORLATER */
	{
		FSpCreateResFile(spec, creator, fileType, scriptTag);
		return;
	}
