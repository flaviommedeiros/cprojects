if ((pAd->CommonCfg.RadarDetect.RDMode != RD_NORMAL_MODE)
#ifdef CARRIER_DETECTION_SUPPORT
#endif // CARRIER_DETECTION_SUPPORT //
		)
	{
		return NDIS_STATUS_FAILURE;
	}
