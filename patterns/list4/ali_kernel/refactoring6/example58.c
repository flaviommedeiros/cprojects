if ((pAd->MacTab.Content[i].ValidAsCLI == FALSE) &&
			(pAd->MacTab.Content[i].ValidAsWDS == FALSE) &&
			(pAd->MacTab.Content[i].ValidAsApCli== FALSE) &&
			(pAd->MacTab.Content[i].ValidAsMesh == FALSE)
#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
			&& (pAd->MacTab.Content[i].ValidAsDls == FALSE)
#endif // QOS_DLS_SUPPORT //
#endif // CONFIG_STA_SUPPORT //
			)
		{
			pEntry = &pAd->MacTab.Content[i];
			if (CleanAll == TRUE)
			{
				pEntry->MaxSupportedRate = RATE_11;
				pEntry->CurrTxRate = RATE_11;
				NdisZeroMemory(pEntry, sizeof(MAC_TABLE_ENTRY));
				pEntry->PairwiseKey.KeyLen = 0;
				pEntry->PairwiseKey.CipherAlg = CIPHER_NONE;
			}
#ifdef CONFIG_STA_SUPPORT
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

			pEntry->bIAmBadAtheros = FALSE;
			pEntry->pAd = pAd;
			pEntry->CMTimerRunning = FALSE;
			pEntry->EnqueueEapolStartTimerRunning = EAPOL_START_DISABLE;
			pEntry->RSNIE_Len = 0;
			NdisZeroMemory(pEntry->R_Counter, sizeof(pEntry->R_Counter));
			pEntry->ReTryCounter = PEER_MSG1_RETRY_TIMER_CTR;

			if (pEntry->ValidAsMesh)
				pEntry->apidx = (apidx - MIN_NET_DEVICE_FOR_MESH);
			else if (pEntry->ValidAsApCli)
				pEntry->apidx = (apidx - MIN_NET_DEVICE_FOR_APCLI);
			else if (pEntry->ValidAsWDS)
				pEntry->apidx = (apidx - MIN_NET_DEVICE_FOR_WDS);
#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
			else if (pEntry->ValidAsDls)
				pEntry->apidx = (apidx - MIN_NET_DEVICE_FOR_DLS);
#endif // QOS_DLS_SUPPORT //
#endif // CONFIG_STA_SUPPORT //
			else
				pEntry->apidx = apidx;


			{

#ifdef CONFIG_STA_SUPPORT
				IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
				{
					pEntry->AuthMode = pAd->StaCfg.AuthMode;
					pEntry->WepStatus = pAd->StaCfg.WepStatus;
					pEntry->PrivacyFilter = Ndis802_11PrivFilterAcceptAll;
#ifdef RTMP_MAC_PCI
					AsicRemovePairwiseKeyEntry(pAd, pEntry->apidx, (UCHAR)i);
#endif // RTMP_MAC_PCI //
				}
#endif // CONFIG_STA_SUPPORT //
			}

			pEntry->GTKState = REKEY_NEGOTIATING;
			pEntry->PairwiseKey.KeyLen = 0;
			pEntry->PairwiseKey.CipherAlg = CIPHER_NONE;
#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
			if (pEntry->ValidAsDls == TRUE)
				pEntry->PortSecured = WPA_802_1X_PORT_SECURED;
			else
#endif //QOS_DLS_SUPPORT
#endif // CONFIG_STA_SUPPORT //
				pEntry->PortSecured = WPA_802_1X_PORT_NOT_SECURED;

			pEntry->PMKID_CacheIdx = ENTRY_NOT_FOUND;
			COPY_MAC_ADDR(pEntry->Addr, pAddr);
			pEntry->Sst = SST_NOT_AUTH;
			pEntry->AuthState = AS_NOT_AUTH;
			pEntry->Aid = (USHORT)i;  //0;
			pEntry->CapabilityInfo = 0;
			pEntry->PsMode = PWR_ACTIVE;
			pEntry->PsQIdleCount = 0;
			pEntry->NoDataIdleCount = 0;
			pEntry->AssocDeadLine = MAC_TABLE_ASSOC_TIMEOUT;
			pEntry->ContinueTxFailCnt = 0;
#ifdef WDS_SUPPORT
			pEntry->LockEntryTx = FALSE;
			pEntry->TimeStamp_toTxRing = 0;
#endif // WDS_SUPPORT //
			InitializeQueueHeader(&pEntry->PsQueue);


			pAd->MacTab.Size ++;
			// Add this entry into ASIC RX WCID search table
			RTMP_STA_ENTRY_ADD(pAd, pEntry);



			DBGPRINT(RT_DEBUG_TRACE, ("MacTableInsertEntry - allocate entry #%d, Total= %d\n",i, pAd->MacTab.Size));
			break;
		}
