#ifdef DOT11_N_SUPPORT
if (pAdapter->CommonCfg.PhyMode >= PHY_11ABGN_MIXED &&
                pAdapter->CommonCfg.RegTransmitSetting.field.BW == BW_40 &&
                pAdapter->CommonCfg.RegTransmitSetting.field.EXTCHA == EXTCHA_ABOVE)
			{
				// 40MHz ,control channel at lower
				RTMP_BBP_IO_READ8_BY_REG_ID(pAdapter, BBP_R4, &bbpValue);
				bbpValue &= (~0x18);
				bbpValue |= 0x10;
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R4, bbpValue);
				pAdapter->CommonCfg.BBPCurrentBW = BW_40;
				//  RX : control channel at lower
				RTMP_BBP_IO_READ8_BY_REG_ID(pAdapter, BBP_R3, &bbpValue);
				bbpValue &= (~0x20);
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R3, bbpValue);

				RTMP_IO_READ32(pAdapter, TX_BAND_CFG, &Value);
				Value &= 0xfffffffe;
				RTMP_IO_WRITE32(pAdapter, TX_BAND_CFG, Value);
				pAdapter->CommonCfg.CentralChannel = pAdapter->CommonCfg.Channel + 2;
                AsicSwitchChannel(pAdapter, pAdapter->CommonCfg.CentralChannel, FALSE);
			    AsicLockChannel(pAdapter, pAdapter->CommonCfg.CentralChannel);
                DBGPRINT(RT_DEBUG_TRACE, ("BW_40 ,control_channel(%d), CentralChannel(%d) \n",
                                           pAdapter->CommonCfg.Channel,
                                           pAdapter->CommonCfg.CentralChannel));
			}
			else if (pAdapter->CommonCfg.PhyMode >= PHY_11ABGN_MIXED &&
                     pAdapter->CommonCfg.RegTransmitSetting.field.BW == BW_40 &&
                     pAdapter->CommonCfg.RegTransmitSetting.field.EXTCHA == EXTCHA_BELOW)
			{
				// 40MHz ,control channel at upper
				RTMP_BBP_IO_READ8_BY_REG_ID(pAdapter, BBP_R4, &bbpValue);
				bbpValue &= (~0x18);
				bbpValue |= 0x10;
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R4, bbpValue);
				pAdapter->CommonCfg.BBPCurrentBW = BW_40;
				RTMP_IO_READ32(pAdapter, TX_BAND_CFG, &Value);
				Value |= 0x1;
				RTMP_IO_WRITE32(pAdapter, TX_BAND_CFG, Value);

				RTMP_BBP_IO_READ8_BY_REG_ID(pAdapter, BBP_R3, &bbpValue);
				bbpValue |= (0x20);
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R3, bbpValue);
				pAdapter->CommonCfg.CentralChannel = pAdapter->CommonCfg.Channel - 2;
                AsicSwitchChannel(pAdapter, pAdapter->CommonCfg.CentralChannel, FALSE);
			    AsicLockChannel(pAdapter, pAdapter->CommonCfg.CentralChannel);
                DBGPRINT(RT_DEBUG_TRACE, ("BW_40 ,control_channel(%d), CentralChannel(%d) \n",
                                           pAdapter->CommonCfg.Channel,
                                           pAdapter->CommonCfg.CentralChannel));
			}
			else
#endif // DOT11_N_SUPPORT //
			{
				// 20MHz
				RTMP_BBP_IO_READ8_BY_REG_ID(pAdapter, BBP_R4, &bbpValue);
				bbpValue &= (~0x18);
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R4, bbpValue);
				pAdapter->CommonCfg.BBPCurrentBW = BW_20;
                AsicSwitchChannel(pAdapter, pAdapter->CommonCfg.Channel, FALSE);
			    AsicLockChannel(pAdapter, pAdapter->CommonCfg.Channel);
				DBGPRINT(RT_DEBUG_TRACE, ("BW_20, Channel(%d)\n", pAdapter->CommonCfg.Channel));
			}
