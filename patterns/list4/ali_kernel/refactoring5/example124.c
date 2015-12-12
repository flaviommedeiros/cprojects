#ifdef RALINK_ATE
if (ATE_ON(pAdapter))
						{
							ATE_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R66, (0x26 + GET_LNA_GAIN(pAdapter)));
						}
						else
#endif // RALINK_ATE //

							RTMP_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R66, (0x26 + GET_LNA_GAIN(pAdapter)));
