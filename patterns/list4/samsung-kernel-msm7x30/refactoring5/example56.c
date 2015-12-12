#ifdef DHDTHREAD
if (dhd->threads_only)
		down(&dhd->sdsem);
	else
#endif /* DHDTHREAD */
	spin_lock_bh(&dhd->sdlock);
