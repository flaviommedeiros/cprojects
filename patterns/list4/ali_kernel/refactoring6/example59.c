if (pEntry && (pEntry->ValidAsCLI || pEntry->ValidAsApCli || pEntry->ValidAsWDS || pEntry->ValidAsMesh
#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
		|| pEntry->ValidAsDls
#endif // QOS_DLS_SUPPORT //
#endif // CONFIG_STA_SUPPORT //
		))
	{
		if (MAC_ADDR_EQUAL(pEntry->Addr, pAddr))
		{

			// Delete this entry from ASIC on-chip WCID Table
			RTMP_STA_ENTRY_MAC_RESET(pAd, wcid);

#ifdef DOT11_N_SUPPORT
			// free resources of BA
			BASessionTearDownALL(pAd, pEntry->Aid);
#endif // DOT11_N_SUPPORT //


			pPrevEntry = NULL;
			pProbeEntry = pAd->MacTab.Hash[HashIdx];
			ASSERT(pProbeEntry);

			// update Hash list
			do
			{
				if (pProbeEntry == pEntry)
				{
					if (pPrevEntry == NULL)
					{
						pAd->MacTab.Hash[HashIdx] = pEntry->pNext;
					}
					else
					{
						pPrevEntry->pNext = pEntry->pNext;
					}
					break;
				}

				pPrevEntry = pProbeEntry;
				pProbeEntry = pProbeEntry->pNext;
			} while (pProbeEntry);

			// not found !!!
			ASSERT(pProbeEntry != NULL);

			RTMP_STA_ENTRY_KEY_DEL(pAd, BSS0, wcid);


		if (pEntry->EnqueueEapolStartTimerRunning != EAPOL_START_DISABLE)
		{
            RTMPCancelTimer(&pEntry->EnqueueStartForPSKTimer, &Cancelled);
			pEntry->EnqueueEapolStartTimerRunning = EAPOL_START_DISABLE;
        }


			NdisZeroMemory(pEntry, sizeof(MAC_TABLE_ENTRY));
			pAd->MacTab.Size --;
			DBGPRINT(RT_DEBUG_TRACE, ("MacTableDeleteEntry1 - Total= %d\n", pAd->MacTab.Size));
		}
		else
		{
			DBGPRINT(RT_DEBUG_OFF, ("\n%s: Impossible Wcid = %d !!!!!\n", __FUNCTION__, wcid));
		}
	}
