if ((pAd->OpMode == OPMODE_STA)
		&& (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_MEDIA_STATE_CONNECTED)
			)
		&& !(OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE))
#ifdef RTMP_MAC_PCI
		&& (pAd->bPCIclkOff == FALSE)
#endif // RTMP_MAC_PCI //
		)
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R66, &OrigR66Value);
		R66 = OrigR66Value;

		if (pAd->Antenna.field.RxPath > 1)
			Rssi = (pAd->StaCfg.RssiSample.AvgRssi0 + pAd->StaCfg.RssiSample.AvgRssi1) >> 1;
		else
			Rssi = pAd->StaCfg.RssiSample.AvgRssi0;

		if (pAd->LatchRfRegs.Channel <= 14)
		{	//BG band
#ifdef RT30xx
			// RT3070 is a no LNA solution, it should have different control regarding to AGC gain control
			// Otherwise, it will have some throughput side effect when low RSSI

			if (IS_RT3070(pAd)||IS_RT3090(pAd) || IS_RT3572(pAd) || IS_RT3390(pAd))
			{
				if (Rssi > RSSI_FOR_MID_LOW_SENSIBILITY)
				{
					R66 = 0x1C + 2*GET_LNA_GAIN(pAd) + 0x20;
					if (OrigR66Value != R66)
					{
							RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
					}
				}
				else
				{
					R66 = 0x1C + 2*GET_LNA_GAIN(pAd);
					if (OrigR66Value != R66)
					{
							RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
					}
				}
			}
			else
#endif // RT30xx //
			{
				if (Rssi > RSSI_FOR_MID_LOW_SENSIBILITY)
				{
					R66 = (0x2E + GET_LNA_GAIN(pAd)) + 0x10;
					if (OrigR66Value != R66)
					{
						RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
					}
				}
				else
				{
					R66 = 0x2E + GET_LNA_GAIN(pAd);
					if (OrigR66Value != R66)
					{
						RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
					}
				}
			}
		}
		else
		{	//A band
			if (pAd->CommonCfg.BBPCurrentBW == BW_20)
			{
				if (Rssi > RSSI_FOR_MID_LOW_SENSIBILITY)
				{
					R66 = 0x32 + (GET_LNA_GAIN(pAd)*5)/3 + 0x10;
					if (OrigR66Value != R66)
					{
							RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
					}
				}
				else
				{
					R66 = 0x32 + (GET_LNA_GAIN(pAd)*5)/3;
					if (OrigR66Value != R66)
					{
							RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
					}
				}
			}
			else
			{
				if (Rssi > RSSI_FOR_MID_LOW_SENSIBILITY)
				{
					R66 = 0x3A + (GET_LNA_GAIN(pAd)*5)/3 + 0x10;
					if (OrigR66Value != R66)
					{
							RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
					}
				}
				else
				{
					R66 = 0x3A + (GET_LNA_GAIN(pAd)*5)/3;
					if (OrigR66Value != R66)
					{
							RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
					}
				}
			}
		}


	}
