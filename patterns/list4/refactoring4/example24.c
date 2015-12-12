#ifdef RT2860
if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_WMM_INUSED))
#endif
#ifdef RT2870
	if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_WMM_INUSED) &&
		CLIENT_STATUS_TEST_FLAG(pEntry, fCLIENT_STATUS_WMM_CAPABLE))
#endif
	{
		USHORT Protocol;
		UCHAR  LlcSnapLen = 0, Byte0, Byte1;
		do
		{
			// get Ethernet protocol field
			Protocol = (USHORT)((pSrcBufVA[12] << 8) + pSrcBufVA[13]);
			if (Protocol <= 1500)
			{
				// get Ethernet protocol field from LLC/SNAP
				if (Sniff2BytesFromNdisBuffer(PacketInfo.pFirstBuffer, LENGTH_802_3 + 6, &Byte0, &Byte1) != NDIS_STATUS_SUCCESS)
					break;

				Protocol = (USHORT)((Byte0 << 8) + Byte1);
				LlcSnapLen = 8;
			}

			// always AC_BE for non-IP packet
			if (Protocol != 0x0800)
				break;

			// get IP header
			if (Sniff2BytesFromNdisBuffer(PacketInfo.pFirstBuffer, LENGTH_802_3 + LlcSnapLen, &Byte0, &Byte1) != NDIS_STATUS_SUCCESS)
				break;

			// return AC_BE if packet is not IPv4
			if ((Byte0 & 0xf0) != 0x40)
				break;

			FlgIsIP = 1;
			UserPriority = (Byte1 & 0xe0) >> 5;
			QueIdx = MapUserPriorityToAccessCategory[UserPriority];

			// TODO: have to check ACM bit. apply TSPEC if ACM is ON
			// TODO: downgrade UP & QueIdx before passing ACM
			if (pAd->CommonCfg.APEdcaParm.bACM[QueIdx])
			{
				UserPriority = 0;
				QueIdx		 = QID_AC_BE;
			}
		} while (FALSE);
	}
