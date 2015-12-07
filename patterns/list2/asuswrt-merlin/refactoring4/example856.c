#ifdef KTHREAD_SUPPORT
if (pTask->kthread_task)
#else
	CHECK_PID_LEGALITY(pTask->taskPID)
#endif
	{
		mb();
		NdisAcquireSpinLock(&pAd->CmdQLock);
		pAd->CmdQ.CmdQState = RTMP_TASK_STAT_STOPED;
		NdisReleaseSpinLock(&pAd->CmdQLock);
		mb();
		/*RTUSBCMDUp(pAd); */
		ret = RtmpOSTaskKill(pTask);
		if (ret == NDIS_STATUS_FAILURE) {
			DBGPRINT(RT_DEBUG_ERROR, ("%s: kill task(%s) failed!\n",
						  RTMP_OS_NETDEV_GET_DEVNAME
						  (pAd->net_dev),
						  pTask->taskName));
		}
		pAd->CmdQ.CmdQState = RTMP_TASK_STAT_UNKNOWN;
	}
