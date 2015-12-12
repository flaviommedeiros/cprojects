#if(DM_ODM_SUPPORT_TYPE & (ODM_WIN|ODM_CE))
if(pPktinfo->bPacketMatchBSSID)
#else
	if(pPktinfo->StationID != 0)
#endif
	{				
		//3 Update CFO report for path-A & path-B
		// Only paht-A and path-B have CFO tail and short CFO
		for(i = ODM_RF_PATH_A; i <= ODM_RF_PATH_B; i++)   
		{
			pCfoTrack->CFO_tail[i] = (int)pcfotail[i];
	 	}

		//3 Update packet counter
		if(pCfoTrack->packetCount == 0xffffffff)
			pCfoTrack->packetCount = 0;
		else
	 		pCfoTrack->packetCount++;
	}
