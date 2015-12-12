#ifdef QOS_DLS_SUPPORT
if (apidx >= MIN_NET_DEVICE_FOR_DLS)
			{
				pEntry->ValidAsCLI = FALSE;
				pEntry->ValidAsWDS = FALSE;
				pEntry->ValidAsApCli = FALSE;
				pEntry->ValidAsMesh = FALSE;
				pEntry->ValidAsDls = TRUE;
				pEntry->isCached = FALSE;
			}
			else
#endif // QOS_DLS_SUPPORT //
#endif // CONFIG_STA_SUPPORT //
			{

#ifdef CONFIG_STA_SUPPORT
				IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
				{
					pEntry->ValidAsCLI = TRUE;
					pEntry->ValidAsWDS = FALSE;
					pEntry->ValidAsApCli = FALSE;
					pEntry->ValidAsMesh = FALSE;
					pEntry->ValidAsDls = FALSE;
				}
#endif // CONFIG_STA_SUPPORT //
			}
