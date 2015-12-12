#ifdef DHDTHREAD
if (dhd->threads_only)
		up(&dhd->sdsem);
	else
#endif /* DHDTHREAD */
	spin_unlock_bh(&dhd->sdlock);
