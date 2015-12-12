#ifdef RALINK_ATE
if (ATE_ON(pAdapter))
					{
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAdapter, bbpId, bbpValue);
						/* read it back for showing */
						ATE_BBP_IO_READ8_BY_REG_ID(pAdapter, bbpId, &regBBP);
					}
					else
#endif // RALINK_ATE //
					{
					    RTMP_BBP_IO_WRITE8_BY_REG_ID(pAdapter, bbpId, bbpValue);
					/* read it back for showing */
					RTMP_BBP_IO_READ8_BY_REG_ID(pAdapter, bbpId, &regBBP);
			}
