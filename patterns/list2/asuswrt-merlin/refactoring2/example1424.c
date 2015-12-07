#ifdef RTMP_MAC_PCI
if (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)
			    && (pAd->bPCIclkOff == FALSE))
#endif /* RTMP_MAC_PCI // */
			{
				/* When Adhoc beacon is enabled and RTS/CTS is enabled, there is a chance that hardware MAC FSM will run into a deadlock */
				/* and sending CTS-to-self over and over. */
				/* Software Patch Solution: */
				/* 1. Polling debug state register 0x10F4 every one second. */
				/* 2. If in 0x10F4 the ((bit29==1) && (bit7==1)) OR ((bit29==1) && (bit5==1)), it means the deadlock has occurred. */
				/* 3. If the deadlock occurred, reset MAC/BBP by setting 0x1004 to 0x0001 for a while then setting it back to 0x000C again. */

				u32 MacReg = 0;

				RTMP_IO_READ32(pAd, 0x10F4, &MacReg);
				if (((MacReg & 0x20000000) && (MacReg & 0x80))
				    || ((MacReg & 0x20000000)
					&& (MacReg & 0x20))) {
					RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x1);
					RTMPusecDelay(1);
					RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0xC);

					DBGPRINT(RT_DEBUG_WARN,
						 ("Warning, MAC specific condition occurs \n"));
				}
			}
