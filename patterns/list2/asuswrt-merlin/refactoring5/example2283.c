#ifdef KTHREAD_SUPPORT
if (pTask->kthread_task == NULL)
#else
	CHECK_PID_LEGALITY(pTask->taskPID) {
	}
	else
#endif
	return NDIS_STATUS_RESOURCES;
