#ifdef HAVE_QUEUE
if (msgfp->type == (u_int32_t)DB_QUEUE && msgfp->pgno != 0)
		ret = __qam_fput(rep->queue_dbc,
		     msgfp->pgno, dst, rep->queue_dbc->priority);
	else
#endif
		ret = __memp_fput(rep->file_mpf,
		    ip, dst, rep->file_dbp->priority);
