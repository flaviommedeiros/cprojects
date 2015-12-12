#if !TARGET_API_MAC_CARBON
if ( ( Gestalt(gestaltFSAttr, &response) == noErr ) && ((response & (1L << gestaltFSSupports2TBVols)) != 0) )
	
#endif	//	!TARGET_API_MAC_CARBON
	
	{
		/* Large volume support is available */
		result = CallPBXGetVolInfoSync(&pb);
		if ( result == noErr )
		{
			/* The volume name was returned in volName (if not NULL) and */
			/* we have the volume's vRefNum and allocation block size */
			*vRefNum = pb.ioVRefNum;
			
			/* return the freeBytes and totalBytes */
			*totalBytes = pb.ioVTotalBytes;
			*freeBytes = pb.ioVFreeBytes;
		}
	}
	
#if !TARGET_API_MAC_CARBON
	
	else
	{
		/* No large volume support */
		/* Use PBHGetVInfoSync to get the results */
		result = PBHGetVInfoSync((HParmBlkPtr)&pb);
		if ( result == noErr )
		{
			VCB				*theVCB;
		
			/* The volume name was returned in volName (if not NULL) and */
			/* we have the volume's vRefNum */
			*vRefNum = pb.ioVRefNum;
			
			/* System 7.5 (and beyond) pins the number of allocation blocks and */
			/* the number of free allocation blocks returned by PBHGetVInfo to */
			/* a value so that when multiplied by the allocation block size, */
			/* the volume will look like it has $7fffffff bytes or less. This */
			/* was done so older applications that use signed math or that use */
			/* the GetVInfo function (which uses signed math) will continue to work. */
			/* However, the unpinned numbers (which we want) are always available */
			/* in the volume's VCB so we'll get those values from the VCB. */
			/* Note: Carbon doesn't support the VCB queue, so this code cannot be */
			/* used (and is conditionalized out) by Carbon applications. */
			
			/* Find the volume's VCB */
			theVCB = (VCB *)(GetVCBQHdr()->qHead);
			while ( theVCB != NULL )
			{
				if ( theVCB->vcbVRefNum == *vRefNum )
				{
					break;
				}
				
				theVCB = (VCB *)(theVCB->qLink);	/* next VCB */
			}
			
			if ( theVCB != NULL )
			{
				/* Found a VCB we can use. Get the un-pinned number of allocation blocks */
				/* and the number of free blocks from the VCB. */
				*freeBytes = U64Multiply(U64SetU((unsigned short)theVCB->vcbFreeBks), U64SetU((unsigned long)pb.ioVAlBlkSiz));
				*totalBytes = U64Multiply(U64SetU((unsigned short)theVCB->vcbNmAlBlks), U64SetU((unsigned long)pb.ioVAlBlkSiz));
			}
			else
			{
				/* Didn't find a VCB we can use. Return the number of allocation blocks */
				/* and the number of free blocks returned by PBHGetVInfoSync. */
				*freeBytes = U64Multiply(U64SetU((unsigned short)pb.ioVFrBlk), U64SetU((unsigned long)pb.ioVAlBlkSiz));
				*totalBytes = U64Multiply(U64SetU((unsigned short)pb.ioVNmAlBlks), U64SetU((unsigned long)pb.ioVAlBlkSiz));
			}
			
		}
	}
