#ifdef WDS_SUPPORT
if (RTMP_GET_PACKET_NET_DEVICE(pPacket) >= MIN_NET_DEVICE_FOR_WDS)
	{
		IfIdx = (RTMP_GET_PACKET_NET_DEVICE(pPacket) - MIN_NET_DEVICE_FOR_WDS) % MAX_WDS_ENTRY;
		NetDev = pAd->WdsTab.WdsEntry[IfIdx].dev;
	}
	else
#endif // WDS_SUPPORT //
	{
#ifdef MBSS_SUPPORT
		if (pAd->OpMode == OPMODE_AP)
		{
			IfIdx = (RTMP_GET_PACKET_NET_DEVICE(pPacket) - MIN_NET_DEVICE_FOR_MBSSID) % MAX_MBSSID_NUM;
			NetDev = pAd->ApCfg.MBSSID[IfIdx].MSSIDDev;
		}
		else
		{
			IfIdx = MAIN_MBSSID;
			NetDev = pAd->net_dev;
		}
#else
		IfIdx = MAIN_MBSSID;
		NetDev = pAd->net_dev;
#endif
	}
