if ( 
#if !__MACOSSEVENORLATER
		 !FSHasFSSpecCalls() ||
#endif	/* !__MACOSSEVENORLATER */
		 !HasFSpExchangeFilesCompatibilityFix() )
	{
		HParamBlockRec			pb;
		CInfoPBRec				catInfoSource, catInfoDest;
		OSErr					result, result2;
		Str31					unique1, unique2;
		StringPtr				unique1Ptr, unique2Ptr, swapola;
		GetVolParmsInfoBuffer	volInfo;
		long					theSeed, temp;
		
		/* Make sure the source and destination are on the same volume */
		if ( source->vRefNum != dest->vRefNum )
		{
			result = diffVolErr;
			goto errorExit3;
		}
		
		/* Try PBExchangeFiles first since it preserves the file ID reference */
		pb.fidParam.ioNamePtr = (StringPtr) &(source->name);
		pb.fidParam.ioVRefNum = source->vRefNum;
		pb.fidParam.ioDestNamePtr = (StringPtr) &(dest->name);
		pb.fidParam.ioDestDirID = dest->parID;
		pb.fidParam.ioSrcDirID = source->parID;
	
		result = PBExchangeFilesSync(&pb);
	
		/* Note: The compatibility case won't work for files with *Btree control blocks. */
		/* Right now the only *Btree files are created by the system. */
		if ( result != noErr )
		{
			pb.ioParam.ioNamePtr = NULL;
			pb.ioParam.ioBuffer = (Ptr) &volInfo;
			pb.ioParam.ioReqCount = sizeof(volInfo);
			result2 = PBHGetVolParmsSync(&pb);
			
			/* continue if volume has no fileID support (or no GetVolParms support) */
			if ( (result2 == noErr) && hasFileIDs(volInfo) )
			{
				goto errorExit3;
			}
	
			/* Get the catalog information for each file */
			/* and make sure both files are *really* files */
			catInfoSource.hFileInfo.ioVRefNum = source->vRefNum;
			catInfoSource.hFileInfo.ioFDirIndex = 0;
			catInfoSource.hFileInfo.ioNamePtr = (StringPtr) &(source->name);
			catInfoSource.hFileInfo.ioDirID = source->parID;
			catInfoSource.hFileInfo.ioACUser = 0; /* ioACUser used to be filler2 */
			result = PBGetCatInfoSync(&catInfoSource);
			if ( result != noErr )
			{
				goto errorExit3;
			}
			if ( (catInfoSource.hFileInfo.ioFlAttrib & kioFlAttribDirMask) != 0 )
			{
				result = notAFileErr;
				goto errorExit3;
			}
			
			catInfoDest.hFileInfo.ioVRefNum = dest->vRefNum;
			catInfoDest.hFileInfo.ioFDirIndex = 0;
			catInfoDest.hFileInfo.ioNamePtr = (StringPtr) &(dest->name);
			catInfoDest.hFileInfo.ioDirID = dest->parID;
			catInfoDest.hFileInfo.ioACUser = 0; /* ioACUser used to be filler2 */
			result = PBGetCatInfoSync(&catInfoDest);
			if ( result != noErr )
			{
				goto errorExit3;
			}
			if ( (catInfoDest.hFileInfo.ioFlAttrib & kioFlAttribDirMask) != 0 )
			{
				result = notAFileErr;
				goto errorExit3;
			}
			
			/* generate 2 filenames that are unique in both directories */
			theSeed = 0x64666A6C;	/* a fine unlikely filename */
			unique1Ptr = (StringPtr)&unique1;
			unique2Ptr = (StringPtr)&unique2;
			
			result = GenerateUniqueName(source->vRefNum, &theSeed, source->parID, dest->parID, unique1Ptr);
			if ( result != noErr )
			{
				goto errorExit3;
			}
	
			GenerateUniqueName(source->vRefNum, &theSeed, source->parID, dest->parID, unique2Ptr);
			if ( result != noErr )
			{
				goto errorExit3;
			}
	
			/* rename source to unique1 */
			pb.fileParam.ioNamePtr = (StringPtr) &(source->name);
			pb.ioParam.ioMisc = (Ptr) unique1Ptr;
			pb.ioParam.ioVersNum = 0;
			result = PBHRenameSync(&pb);
			if ( result != noErr )
			{
				goto errorExit3;
			}
			
			/* rename dest to unique2 */
			pb.ioParam.ioMisc = (Ptr) unique2Ptr;
			pb.ioParam.ioVersNum = 0;
			pb.fileParam.ioNamePtr = (StringPtr) &(dest->name);
			pb.fileParam.ioDirID = dest->parID;
			result = PBHRenameSync(&pb);
			if ( result != noErr )
			{
				goto errorExit2;	/* back out gracefully by renaming unique1 back to source */
			}
				
			/* If files are not in same directory, swap their locations */
			if ( source->parID != dest->parID )
			{
				/* move source file to dest directory */
				pb.copyParam.ioNamePtr = unique1Ptr;
				pb.copyParam.ioNewName = NULL;
				pb.copyParam.ioNewDirID = dest->parID;
				pb.copyParam.ioDirID = source->parID;
				result = PBCatMoveSync((CMovePBPtr) &pb);
				if ( result != noErr )
				{
					goto errorExit1;	/* back out gracefully by renaming both files to original names */
				}
				
				/* move dest file to source directory */
				pb.copyParam.ioNamePtr = unique2Ptr;
				pb.copyParam.ioNewDirID = source->parID;
				pb.copyParam.ioDirID = dest->parID;
				result = PBCatMoveSync((CMovePBPtr) &pb);
				if ( result != noErr)
				{
					/* life is very bad.  We'll at least try to move source back */
					pb.copyParam.ioNamePtr = unique1Ptr;
					pb.copyParam.ioNewName = NULL;
					pb.copyParam.ioNewDirID = source->parID;
					pb.copyParam.ioDirID = dest->parID;
					(void) PBCatMoveSync((CMovePBPtr) &pb);	/* ignore errors */
					goto errorExit1;	/* back out gracefully by renaming both files to original names */
				}
			}
			
			/* Make unique1Ptr point to file in source->parID */
			/* and unique2Ptr point to file in dest->parID */
			/* This lets us fall through to the rename code below */
			swapola = unique1Ptr;
			unique1Ptr = unique2Ptr;
			unique2Ptr = swapola;
	
			/* At this point, the files are in their new locations (if they were moved) */
			/* Source is named Unique1 (name pointed to by unique2Ptr) and is in dest->parID */
			/* Dest is named Unique2 (name pointed to by unique1Ptr) and is in source->parID */
			/* Need to swap attributes except mod date and swap names */
	
			/* swap the catalog info by re-aiming the CInfoPB's */
			catInfoSource.hFileInfo.ioNamePtr = unique1Ptr;
			catInfoDest.hFileInfo.ioNamePtr = unique2Ptr;
			
			catInfoSource.hFileInfo.ioDirID = source->parID;
			catInfoDest.hFileInfo.ioDirID = dest->parID;
			
			/* Swap the original mod dates with each file */
			temp = catInfoSource.hFileInfo.ioFlMdDat;
			catInfoSource.hFileInfo.ioFlMdDat = catInfoDest.hFileInfo.ioFlMdDat;
			catInfoDest.hFileInfo.ioFlMdDat = temp;
			
			/* Here's the swap (ignore errors) */
			(void) PBSetCatInfoSync(&catInfoSource); 
			(void) PBSetCatInfoSync(&catInfoDest);
			
			/* rename unique2 back to dest */
errorExit1:
			pb.ioParam.ioMisc = (Ptr) &(dest->name);
			pb.ioParam.ioVersNum = 0;
			pb.fileParam.ioNamePtr = unique2Ptr;
			pb.fileParam.ioDirID = dest->parID;
			(void) PBHRenameSync(&pb);	/* ignore errors */
	
			/* rename unique1 back to source */
errorExit2:
			pb.ioParam.ioMisc = (Ptr) &(source->name);
			pb.ioParam.ioVersNum = 0;
			pb.fileParam.ioNamePtr = unique1Ptr;
			pb.fileParam.ioDirID = source->parID;
			(void) PBHRenameSync(&pb); /* ignore errors */
		}
errorExit3: { /* null statement */ }
		return ( result );
	}
	else
#endif	/* !__MACOSSEVENFIVEORLATER */
	{
		return ( FSpExchangeFiles(source, dest) );
	}
