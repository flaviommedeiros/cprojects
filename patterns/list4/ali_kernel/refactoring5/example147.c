#ifdef RALINK_ATE
if (pAd->ate.bFWLoading == TRUE)
		{
			/* reloading firmware when received iwpriv cmd "ATE=ATESTOP" */
			if (j > 0)
			{
				if (j % 64 != 0)
				{
					ATEDBGPRINT(RT_DEBUG_ERROR, ("#"));
				}
				else
				{
					ATEDBGPRINT(RT_DEBUG_ERROR, ("\n"));
				}
				++j;
			}
			else if (j == 0)
			{
				ATEDBGPRINT(RT_DEBUG_ERROR, ("Loading firmware. Please wait for a moment...\n"));
				++j;
			}
		}
		else
#endif // RALINK_ATE //
#endif // RTMP_MAC_PCI //
		{
		DBGPRINT_ERR(("H2M_MAILBOX still hold by MCU. command fail\n"));
		}
