#ifdef RALINK_28xx_QA
if (pAd->ate.bQATxStart == TRUE)
	{
		// copy pattern
		if ((pAd->ate.PLen != 0))
		{
			int j;

			for (j = 0; j < pAd->ate.DLen; j+=pAd->ate.PLen)
			{
				memcpy(RTPKT_TO_OSPKT(pPacket)->data + j, pAd->ate.Pattern, pAd->ate.PLen);
			}
		}
	}
	else
#endif // RALINK_28xx_QA //
	{
		for (j = 0; j < RTPKT_TO_OSPKT(pPacket)->len; j++)
		{
			pDest[j] = 0xA5;
		}
	}
